#include "methods.h"

namespace
{
  using v8::FunctionTemplate;

  NAN_MODULE_INIT(InitAll)
  {
    Nan::Set(target, Nan::New("aNumber").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(aNumber)).ToLocalChecked());
    Nan::Set(target, Nan::New("recursiveFibonacci").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(recursiveFibonacci)).ToLocalChecked());
    Nan::Set(target, Nan::New("iterativeFibonacci").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(iterativeFibonacci)).ToLocalChecked());
    Nan::Set(target, Nan::New("Rule110").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(Rule110)).ToLocalChecked());
    Nan::Set(target, Nan::New("printRule110").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(printRule110)).ToLocalChecked());

    Map::Init(target);
  }
  NODE_MODULE(NativeModule, InitAll)
}
