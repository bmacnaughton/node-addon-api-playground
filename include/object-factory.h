#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <napi.h>

class ObjectThing : public Napi::ObjectWrap<ObjectThing> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
  ObjectThing(const Napi::CallbackInfo& info);
  static Napi::Value isObjectThing(const Napi::CallbackInfo& info);
  Napi::Value Value(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;
  Napi::Value PlusOne(const Napi::CallbackInfo& info);
  double counter_;
};

#endif
