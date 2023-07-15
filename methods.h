#pragma once

#include <map>
#include <bitset>
#include <iostream>
#include <nan.h>

NAN_METHOD(aNumber);
NAN_METHOD(recursiveFibonacci);
NAN_METHOD(iterativeFibonacci);
NAN_METHOD(Rule110);
NAN_METHOD(printRule110);

class Map : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
  
  private:
    explicit Map();
    ~Map();

    static NAN_METHOD(New);
    static Nan::Persistent<v8::Function> constructor;

    std::unordered_map<std::string, std::string> map_;
    static NAN_METHOD(Set);
    static NAN_METHOD(Get);
    static NAN_METHOD(Has);
    static NAN_METHOD(Delete);
};
