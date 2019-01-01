#include <napi.h>
#include <uv.h>
#include "addable.h"

Addable::Addable(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Addable>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->val_ = info[0].As<Napi::Number>().DoubleValue();
};

Napi::FunctionReference Addable::constructor;

Napi::Object Addable::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Addable", {});

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Addable", func);

  return exports;
}

Napi::Object Addable::NewInstance(Napi::Value arg) {
  Napi::Object obj = constructor.New({ arg });
  return obj;
}
