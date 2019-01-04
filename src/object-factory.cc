#include <napi.h>
#include <uv.h>
#include "object-factory.h"
#include <iostream>

using namespace Napi;

Napi::FunctionReference ObjectThing::constructor;

Napi::Object ObjectThing::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "ObjectThing", {
      InstanceMethod("plusOne", &ObjectThing::PlusOne),
      InstanceMethod("value", &ObjectThing::Value),
      StaticMethod("isObjectThing", &ObjectThing::isObjectThing)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("ObjectThing", func);
  return exports;
}


ObjectThing::ObjectThing(const Napi::CallbackInfo& info) : Napi::ObjectWrap<ObjectThing>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  std::cout << "in ObjectThing::ObjectThing\n";

  this->counter_ = info[0].As<Napi::Number>().DoubleValue();
};

Napi::Object ObjectThing::NewInstance(Napi::Env env, Napi::Value arg) {
  Napi::EscapableHandleScope scope(env);
  Napi::Object obj = constructor.New({ arg });
  return scope.Escape(napi_value(obj)).ToObject();
}

Napi::Value ObjectThing::Value(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->counter_);
}

Napi::Value ObjectThing::PlusOne(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->counter_ = this->counter_ + 1;

  return Napi::Number::New(env, this->counter_);
}

Napi::Value ObjectThing::isObjectThing (const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  bool is = false;

  if (info.Length()) {
      is = info[0].ToObject().InstanceOf(constructor.Value());
  }

  return Napi::Boolean::New(env, is);
}
