#ifndef ADDABLE_H
#define ADDABLE_H

#include <napi.h>

class Addable : public Napi::ObjectWrap<Addable> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Value arg);
  double Val() const { return val_; }
  Addable(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;
  double val_;
};

#endif
