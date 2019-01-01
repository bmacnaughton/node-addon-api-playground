#include <napi.h>
#include <uv.h>
#include "object-factory.h"

using namespace Napi;

Napi::FunctionReference ObjectThing::constructor;

Napi::Object ObjectThing::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "ObjectThing", {
      InstanceMethod("plusOne", &ObjectThing::PlusOne),
      StaticMethod("instanceOf", &ObjectThing::instanceOf)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("ObjectThing", func);
  return exports;
}

ObjectThing::ObjectThing(const Napi::CallbackInfo& info) : Napi::ObjectWrap<ObjectThing>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->counter_ = info[0].As<Napi::Number>().DoubleValue();
};

Napi::Object ObjectThing::NewInstance(Napi::Env env, Napi::Value arg) {
  Napi::EscapableHandleScope scope(env);
  Napi::Object obj = constructor.New({ arg });
  return scope.Escape(napi_value(obj)).ToObject();
}

Napi::Value ObjectThing::PlusOne(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->counter_ = this->counter_ + 1;

  return Napi::Number::New(env, this->counter_);
}

Napi::Value ObjectThing::instanceOf (const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Object o = info[0].ToObject();

  return Napi::Boolean::New(env, o.InstanceOf(constructor.Value()));
}
