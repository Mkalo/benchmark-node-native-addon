#include "methods.h"

NAN_METHOD(aNumber) {
    info.GetReturnValue().Set(1.75);
}

int fibonacci(int n) {
    if (n < 2) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

NAN_METHOD(recursiveFibonacci) {
    int n = info[0]->NumberValue(info.GetIsolate()->GetCurrentContext()).FromJust();
    info.GetReturnValue().Set(fibonacci(n));
}

NAN_METHOD(iterativeFibonacci) {
    int n = info[0]->NumberValue(info.GetIsolate()->GetCurrentContext()).FromJust();
    int a = 0;
    int b = 1;
    int c;
    for (int i = 0; i < n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    info.GetReturnValue().Set(c);
}

const int RULE110_RULES[8] = {0, 1, 1, 1, 0, 1, 1, 0};

NAN_METHOD(Rule110) {
    auto isolate = info.GetIsolate();
    auto context = isolate->GetCurrentContext();

    int iterations = info[0]->NumberValue(context).FromJust();

    auto states = Nan::New<v8::Array>(iterations);
    
    auto currentState = Nan::New<v8::Array>(iterations);
    Nan::Set(currentState, iterations - 1, Nan::New(1));
    Nan::Set(states, 0, currentState);

    auto statesVector = std::vector<std::vector<bool>>(iterations, std::vector<bool>(iterations, false));
    statesVector[0][iterations - 1] = true;

    for (int i = 1; i < iterations; i++) {
        auto nextState = Nan::New<v8::Array>(iterations);
        Nan::Set(states, i, nextState);
        const auto& lastStateVector = statesVector[i - 1];
        auto& nextStateVector = statesVector[i];
        for (int j = 0; j < iterations; j++) {
            bool left = j == 0 ? false : lastStateVector[j - 1];
            bool center = lastStateVector[j];
            bool right = j == iterations - 1 ? false : lastStateVector[j + 1];
            int ruleValue = RULE110_RULES[(left << 2) | (center << 1) | right];
            nextStateVector[j] = ruleValue;
            Nan::Set(nextState, j, Nan::New(ruleValue));
        }
    }
    
    info.GetReturnValue().Set(states);
}

NAN_METHOD(printRule110) {
    auto isolate = info.GetIsolate();
    auto context = isolate->GetCurrentContext();
    int iterations = info[0]->NumberValue(context).FromJust();

    auto statesVector = std::vector<std::vector<bool>>(iterations, std::vector<bool>(iterations, false));
    statesVector[0][iterations - 1] = true;

    for (int i = 1; i < iterations; i++) {
        const auto& lastStateVector = statesVector[i - 1];
        auto& nextStateVector = statesVector[i];
        for (int j = 0; j < iterations; j++) {
            bool left = j == 0 ? false : lastStateVector[j - 1];
            bool center = lastStateVector[j];
            bool right = j == iterations - 1 ? false : lastStateVector[j + 1];
            int ruleValue = RULE110_RULES[(left << 2) | (center << 1) | right];
            nextStateVector[j] = ruleValue;
        }
    }

    for (const auto& stateVector : statesVector) {
        std::string line;
        for (bool state : stateVector) {
            line += state ? "█" : " ";
        }
        std::cout << line << std::endl;
    }
}

Nan::Persistent<v8::Function> Map::constructor;

NAN_MODULE_INIT(Map::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Map").ToLocalChecked());

    tpl->InstanceTemplate()->SetInternalFieldCount(4);

    Nan::SetPrototypeMethod(tpl, "set", Set);
    Nan::SetPrototypeMethod(tpl, "get", Get);
    Nan::SetPrototypeMethod(tpl, "has", Has);
    Nan::SetPrototypeMethod(tpl, "delete", Delete);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Map").ToLocalChecked(),
        Nan::GetFunction(tpl).ToLocalChecked());
}

Map::Map() {}

Map::~Map() {}

NAN_METHOD(Map::New) {
  if (info.IsConstructCall()) {
    Map *obj = new Map();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    info.GetIsolate()->ThrowException(
        Nan::New("Must be called as a constructor").ToLocalChecked());
  }
}

NAN_METHOD(Map::Set) {
    Map* obj = Nan::ObjectWrap::Unwrap<Map>(info.Holder());
    Nan::Utf8String key(info[0]->ToString(info.GetIsolate()->GetCurrentContext()).ToLocalChecked());
    Nan::Utf8String value(info[1]->ToString(info.GetIsolate()->GetCurrentContext()).ToLocalChecked());
    obj->map_[std::string(*key)] = std::string(*value);
}

NAN_METHOD(Map::Get) {
    Map* obj = Nan::ObjectWrap::Unwrap<Map>(info.Holder());
    Nan::Utf8String key(info[0]->ToString(info.GetIsolate()->GetCurrentContext()).ToLocalChecked());
    std::string value = obj->map_[std::string(*key)];
    info.GetReturnValue().Set(Nan::New(value).ToLocalChecked());
}

NAN_METHOD(Map::Has) {
    Map* obj = Nan::ObjectWrap::Unwrap<Map>(info.Holder());
    Nan::Utf8String key(info[0]->ToString(info.GetIsolate()->GetCurrentContext()).ToLocalChecked());
    bool has = obj->map_.find(std::string(*key)) != obj->map_.end();
    info.GetReturnValue().Set(has);
}

NAN_METHOD(Map::Delete) {
    Map* obj = Nan::ObjectWrap::Unwrap<Map>(info.Holder());
    Nan::Utf8String key(info[0]->ToString(info.GetIsolate()->GetCurrentContext()).ToLocalChecked());
    obj->map_.erase(std::string(*key));
}
