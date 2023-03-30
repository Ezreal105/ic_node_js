#ifdef _WIN32
#include <napi.h>
#include <node_api.h>
// #include <Windows.h>
// #include <libloaderapi.h>

// bool loadLibrary(const char* dllPath, HMODULE& module) {
//     module = LoadLibraryA(dllPath);
//     if (module == NULL) {
//         return false;
//     }
//     return true;
// }

// bool freeLibrary(HMODULE& module) {
//     if (module != NULL) {
//         FreeLibrary(module);
//         module = NULL;
//         return true;
//     }
//     return false;
// }

// typedef int(*GetDeviceCountFunction)();

// Napi::Value IC_GetDeviceCount(const Napi::CallbackInfo& info) {
//     Napi::Env env = info.Env();

//     HMODULE module;
//     if (!loadLibrary("tisgrabber_x64.dll", module)) {
//         Napi::TypeError::New(env, "Failed to load dll").ThrowAsJavaScriptException();
//         return env.Null();
//     }

//     GetDeviceCountFunction getDeviceCountFunction = (GetDeviceCountFunction)GetProcAddress(module, "IC_GetDeviceCount");
//     if (getDeviceCountFunction == NULL) {
//         Napi::TypeError::New(env, "Failed to get function").ThrowAsJavaScriptException();
//         freeLibrary(module);
//         return env.Null();
//     }

//     int result = getDeviceCountFunction();

//     freeLibrary(module);

//     return Napi::Number::New(env, result);
// }

Napi::Value IC_GetDeviceCount(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    return Napi::Number::New(env, -1);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("IC_GetDeviceCount", Napi::Function::New(env, IC_GetDeviceCount));
    return exports;
}

NODE_API_MODULE(test, Init);
#else
#include <napi.h>
#include <node_api.h>

Napi::Value IC_GetDeviceCount(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    return Napi::Number::New(env, -1);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("IC_GetDeviceCount", Napi::Function::New(env, IC_GetDeviceCount));
    return exports;
}

NODE_API_MODULE(test, Init);
#endif

