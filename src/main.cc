#include <string>
#include <napi.h>
#include "core.h"

Napi::String Prompt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string str = info[0].As<Napi::String>().Utf8Value().c_str();
  std::string cLine = ModuleCore::Lines::prompt(str);
  return Napi::String::New(env, cLine);
}

Napi::String ForcePrompt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string str = info[0].As<Napi::String>().Utf8Value().c_str();
  std::string cLine = ModuleCore::Lines::forcePrompt(str);
  return Napi::String::New(env, cLine);
}

Napi::Value LoopPrompt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  std::string str = info[0].As<Napi::String>().Utf8Value().c_str();
  
  Napi::Function fn = info[1].As<Napi::Function>();
  Napi::Boolean force = info[2].ToBoolean();
  
  if (force.Value() == true) {
    Napi::String line = Napi::String::New(env, ModuleCore::Lines::forcePrompt(str));
    bool result = fn.Call({line}).ToBoolean().Value();
    
    while (result == true) {
      Napi::String line = Napi::String::New(env, ModuleCore::Lines::forcePrompt(str));
      result = fn.Call({line}).ToBoolean().Value();
    }
    
    return env.Null();
  } else {
    Napi::String line = Napi::String::New(env, ModuleCore::Lines::prompt(str));
    bool result = fn.Call({line}).ToBoolean().Value();
    
    while (result == true) {
      Napi::String line = Napi::String::New(env, ModuleCore::Lines::prompt(str));
      result = fn.Call({line}).ToBoolean().Value();
    }
    
    return env.Null();
  }
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "prompt"), Napi::Function::New(env, Prompt));
  exports.Set(Napi::String::New(env, "forcePrompt"), Napi::Function::New(env, ForcePrompt));
  exports.Set(Napi::String::New(env, "loopPrompt"), Napi::Function::New(env, LoopPrompt));
  
  return exports;
}

NODE_API_MODULE(native, Init)