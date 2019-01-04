#include "napi.h"
#include <iostream>
#include "object-wrap.h"
#include "object-factory.h"
#include "addable.h"

//
// return world when hello is called
//
Napi::String HelloWorld (const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, "world");
}

//
// add two numbers!
//
Napi::Value Add (const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    double arg0 = info[0].As<Napi::Number>().DoubleValue();
    double arg1 = info[1].As<Napi::Number>().DoubleValue();
    Napi::Number num = Napi::Number::New(env, arg0 + arg1);

    return num;
}

//
// execute supplied callback
//
void RunCallback(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Function cb = info[0].As<Napi::Function>();
    cb.Call(env.Global(), { Napi::String::New(env, "hello world") });
}

//
// object factory
//
Napi::Object CreateObject(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Object obj = Napi::Object::New(env);
    obj.Set(Napi::String::New(env, "msg"), info[0].ToString());

    return obj;
}

//
// function factory
//
Napi::String MyFunction(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, "hello world");
}

Napi::Function CreateFunction(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Function fn = Napi::Function::New(env, MyFunction, "theFunction");
    return fn;
}

//
// ObjectWrap is handled via the MyObject::Init() call in Init()
//

//
// object-factory
//
Napi::Object CreateThing (const Napi::CallbackInfo& info) {
    return ObjectThing::NewInstance(info.Env(), info[0]);
}

//
// addables
//
Napi::Object CreateAddable(const Napi::CallbackInfo& info) {
    return Addable::NewInstance(info[0]);
}

Napi::Number AddAddables(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    Addable* addable1 = Napi::ObjectWrap<Addable>::Unwrap(info[0].As<Napi::Object>());
    Addable* addable2 = Napi::ObjectWrap<Addable>::Unwrap(info[1].As<Napi::Object>());
    double sum = addable1->Val() + addable2->Val();
    return Napi::Number::New(env, sum);
}

//
// return undefined
//
Napi::Value Undef(const Napi::CallbackInfo& info) {
    return info.Env().Undefined();
}

//
// bam test function
//
Napi::Value Test(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Value v = info[2];

    if (info.Length() < 2 || !info[0].IsObject() || !info[1].IsString()) {
        Napi::TypeError::New(env, "invalid arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    if (info.Length() > 2) {
        if (info[2].IsExternal()) {
            std::cout << "it's external!\n";
        }
        if (info[2].IsNumber()) {
            std::cout << "It's a number, duh\n";
        }
        // make an object
        Napi::Object o = info[2].As<Napi::Object>();
        int t = o.Type();
        // make it a string
        std::string str = o.ToString();
        std::cout << "object2string is: " << str << " type " << t << std::endl;
    }

    //std::string s = info[1].As<Napi::String>();
    //std::cout << s << std::endl;

    Napi::Object o = info[0].ToObject();
    if (o.Has(info[1])) {
        return o.Get(info[1]);
    }

    // 0 undefined
    // 1 null
    // 2 boolean
    // 3 number
    // 4 string
    // 5 symbol
    // 6 object
    // 7 function
    std::cout << "v's type is " << v.Type() << std::endl;
    // if it's boolean show the value
    if (v.Type() == 2) {
        std::cout << "and the boolean's value is: " << v.As<Napi::Boolean>().Value() << std::endl;
    }

    return o.Get(info[1]);
    //return env.Undefined();
}

//
// set up exports
//
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("hello", Napi::Function::New(env, HelloWorld));
    exports.Set("add", Napi::Function::New(env, Add));
    exports.Set("runCallback", Napi::Function::New(env, RunCallback));
    exports.Set("createObject", Napi::Function::New(env, CreateObject));
    exports.Set("createFunction", Napi::Function::New(env, CreateFunction));

    //
    // the Object constructor modifies and returns exports
    //
    exports = MyObject::Init(env, exports);

    // object-factory
    exports.Set("CreateThing", Napi::Function::New(env, CreateThing));
    exports = ObjectThing::Init(env, exports);

    // addables
    exports = Addable::Init(env, exports);
    exports.Set("createAddable", Napi::Function::New(env, CreateAddable));
    exports.Set("addAddables", Napi::Function::New(env, AddAddables));

    // undef
    exports.Set("undef", Napi::Function::New(env, Undef));

    // test
    exports.Set("test", Napi::Function::New(env, Test));

    // try creating a simple object.
    Napi::Object o = Napi::Object::New(env);
    o.Set("xyzzy", Napi::String::New(env, "plover"));
    exports.Set("o", o);

    //
    // return the exports object
    //
    return exports;
}

NODE_API_MODULE(hello, Init)

