#ifdef _WIN32

#include <unordered_map>
#include <napi.h>
#include <Windows.h>
#include <functional>
#include "./binding.h"

#define INIT_STATIC_METHOD(method) \
    ic_static.Set(#method, Napi::Function::New<f_##method>(env));

#define BOOL_RETURN()                                           \
    if (ret == IC_SUCCESS)                                      \
    {                                                           \
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS)); \
        retObj.Set("data", Napi::Boolean::New(env, true));      \
    }                                                           \
    else if (ret == IC_ERROR)                                   \
    {                                                           \
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS)); \
        retObj.Set("data", Napi::Boolean::New(env, false));     \
    }                                                           \
    else                                                        \
    {                                                           \
        retObj.Set("code", Napi::Number::New(env, ret));        \
    }

#define STRING_RETURN()                                         \
    if (ret == nullptr)                                         \
    {                                                           \
        retObj.Set("code", Napi::Number::New(env, IC_ERROR));   \
    }                                                           \
    else                                                        \
    {                                                           \
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS)); \
        retObj.Set("data", Napi::String::New(env, ret));        \
    }

#define COUNT_RETURN()                                          \
    if (ret < 0)                                                \
    {                                                           \
        retObj.Set("code", Napi::Number::New(env, ret));        \
    }                                                           \
    else                                                        \
    {                                                           \
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS)); \
        retObj.Set("data", Napi::Number::New(env, ret));        \
    }

struct EnumCbData
{
    Napi::FunctionReference &jsFunc;
};

static Napi::FunctionReference *g_frameReadyCb = nullptr;
static Napi::FunctionReference *g_deviceLostCb = nullptr;
static HMODULE tisgrabber;

Napi::Array FloatVectorToJsArray(const Napi::Env &env, const std::vector<float> &vec)
{
    Napi::Array array = Napi::Array::New(env, vec.size());
    for (size_t i = 0; i < vec.size(); i++)
    {
        array[i] = vec[i];
    }
    return array;
}

void frameReadyCb(HGRABBER hGrabber, HMEMBUFFER hBuffer, unsigned long frameNumber, void *data = nullptr)
{
    if (g_frameReadyCb != nullptr)
    {
        auto env = g_frameReadyCb->Env();
        g_frameReadyCb->Call({Napi::External<HGRABBER_t>::New(env, hGrabber), Napi::External<ImageBuffer>::New(env, hBuffer), Napi::Number::New(env, frameNumber)});
    }
}

void deviceLostCb(HGRABBER hGrabber, void *data = nullptr)
{
    if (g_deviceLostCb != nullptr)
    {
        auto env = g_deviceLostCb->Env();
        g_deviceLostCb->Call({Napi::External<HGRABBER_t>::New(env, hGrabber)});
    }
}

int _cdecl EnumCb(char *Name, void *data)
{
    // convert data to EnumCbData
    EnumCbData *cbData = (EnumCbData *)data;
    // call all js function
    Napi::Function func = cbData->jsFunc.Value();
    auto env = func.Env();
    func.Call({Napi::String::New(env, Name)});
    return 0; // Do not terminate the enumeration
}

// generate start
Napi::Value f_IC_InitLibrary(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto szLicenseKeyStr = info[0].As<Napi::String>().Utf8Value();
    char *szLicenseKey = (char *)szLicenseKeyStr.c_str();

    IC_InitLibrary *fPtr = (IC_InitLibrary *)GetProcAddress(tisgrabber, "IC_InitLibrary");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_InitLibrary in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(szLicenseKey);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_CreateGrabber(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 0)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    IC_CreateGrabber *fPtr = (IC_CreateGrabber *)GetProcAddress(tisgrabber, "IC_CreateGrabber");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_CreateGrabber in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    HGRABBER ret = f();
    Napi::Object retObj = Napi::Object::New(env);
    if (ret)
    {
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
        retObj.Set("data", Napi::External<HGRABBER_t>::New(env, ret));
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, IC_ERROR));
    }
    return retObj;
}
Napi::Value f_IC_TidyUP(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 0)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    IC_TidyUP *fPtr = (IC_TidyUP *)GetProcAddress(tisgrabber, "IC_TidyUP");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_TidyUP in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    f();
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    return retObj;
}
Napi::Value f_IC_CloseLibrary(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 0)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    IC_CloseLibrary *fPtr = (IC_CloseLibrary *)GetProcAddress(tisgrabber, "IC_CloseLibrary");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_CloseLibrary in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    f();
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    return retObj;
}
Napi::Value f_IC_OpenVideoCaptureDevice(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };

    IC_OpenVideoCaptureDevice *fPtr = (IC_OpenVideoCaptureDevice *)GetProcAddress(tisgrabber, "IC_OpenVideoCaptureDevice");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_OpenVideoCaptureDevice in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szDeviceNameStr = info[1].As<Napi::String>().Utf8Value();
    char *szDeviceName = (char *)szDeviceNameStr.c_str();
    int ret = f(hGrabber, szDeviceName);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_CloseVideoCaptureDevice(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_CloseVideoCaptureDevice *fPtr = (IC_CloseVideoCaptureDevice *)GetProcAddress(tisgrabber, "IC_CloseVideoCaptureDevice");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_CloseVideoCaptureDevice in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    return retObj;
}
Napi::Value f_IC_GetDeviceName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetDeviceName *fPtr = (IC_GetDeviceName *)GetProcAddress(tisgrabber, "IC_GetDeviceName");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetDeviceName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    char *ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    if (ret == nullptr)
    {
        retObj.Set("code", Napi::Number::New(env, IC_ERROR));
        retObj.Set("message", Napi::String::New(env, "Device is invalid"));
        return retObj;
    }
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    retObj.Set("data", Napi::String::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetVideoFormatWidth(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetVideoFormatWidth *fPtr = (IC_GetVideoFormatWidth *)GetProcAddress(tisgrabber, "IC_GetVideoFormatWidth");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoFormatWidth in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    retObj.Set("data", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetVideoFormatHeight(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetVideoFormatHeight *fPtr = (IC_GetVideoFormatHeight *)GetProcAddress(tisgrabber, "IC_GetVideoFormatHeight");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoFormatHeight in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    retObj.Set("data", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetFormat(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    COLORFORMAT format = (COLORFORMAT)info[1].As<Napi::Number>().Int32Value();

    IC_SetFormat *fPtr = (IC_SetFormat *)GetProcAddress(tisgrabber, "IC_SetFormat");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetFormat in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, format);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetFormat(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetFormat *fPtr = (IC_GetFormat *)GetProcAddress(tisgrabber, "IC_GetFormat");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetFormat in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    COLORFORMAT ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetVideoFormat(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szFormatStr = info[1].As<Napi::String>().Utf8Value();
    char *szFormat = (char *)szFormatStr.c_str();

    IC_SetVideoFormat *fPtr = (IC_SetVideoFormat *)GetProcAddress(tisgrabber, "IC_SetVideoFormat");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetVideoFormat in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szFormat);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetVideoNorm(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szNormStr = info[1].As<Napi::String>().Utf8Value();
    char *szNorm = (char *)szNormStr.c_str();

    IC_SetVideoNorm *fPtr = (IC_SetVideoNorm *)GetProcAddress(tisgrabber, "IC_SetVideoNorm");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetVideoNorm in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szNorm);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetInputChannel(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szChannelStr = info[1].As<Napi::String>().Utf8Value();
    char *szChannel = (char *)szChannelStr.c_str();

    IC_SetInputChannel *fPtr = (IC_SetInputChannel *)GetProcAddress(tisgrabber, "IC_SetInputChannel");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetInputChannel in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szChannel);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_StartLive(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iShow = (int)info[1].As<Napi::Number>().Int64Value();

    IC_StartLive *fPtr = (IC_StartLive *)GetProcAddress(tisgrabber, "IC_StartLive");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_StartLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iShow);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_PrepareLive(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iShow = (int)info[1].As<Napi::Number>().Int64Value();

    IC_PrepareLive *fPtr = (IC_PrepareLive *)GetProcAddress(tisgrabber, "IC_PrepareLive");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_PrepareLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iShow);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SuspendLive(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_SuspendLive *fPtr = (IC_SuspendLive *)GetProcAddress(tisgrabber, "IC_SuspendLive");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SuspendLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_IsLive(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_IsLive *fPtr = (IC_IsLive *)GetProcAddress(tisgrabber, "IC_IsLive");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    BOOL_RETURN()
    return retObj;
}
Napi::Value f_IC_StopLive(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_StopLive *fPtr = (IC_StopLive *)GetProcAddress(tisgrabber, "IC_StopLive");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_StopLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    return retObj;
}
Napi::Value f_IC_IsCameraPropertyAvailable(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    CAMERA_PROPERTY eProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();

    IC_IsCameraPropertyAvailable *fPtr = (IC_IsCameraPropertyAvailable *)GetProcAddress(tisgrabber, "IC_IsCameraPropertyAvailable");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsCameraPropertyAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, eProperty);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetCameraProperty(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    CAMERA_PROPERTY eProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long lValue = (long)info[2].As<Napi::Number>().Int64Value();

    IC_SetCameraProperty *fPtr = (IC_SetCameraProperty *)GetProcAddress(tisgrabber, "IC_SetCameraProperty");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetCameraProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, eProperty, lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_CameraPropertyGetRange(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    CAMERA_PROPERTY eProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long lMin = 0;
    long lMax = 0;

    IC_CameraPropertyGetRange *fPtr = (IC_CameraPropertyGetRange *)GetProcAddress(tisgrabber, "IC_CameraPropertyGetRange");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_CameraPropertyGetRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, eProperty, &lMin, &lMax);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    if (ret != IC_SUCCESS)
    {
        return retObj;
    }
    Napi::Object data = Napi::Object::New(env);
    data.Set("min", Napi::Number::New(env, lMin));
    data.Set("max", Napi::Number::New(env, lMax));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_GetCameraProperty(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    CAMERA_PROPERTY eProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long lValue = 0;

    IC_GetCameraProperty *fPtr = (IC_GetCameraProperty *)GetProcAddress(tisgrabber, "IC_GetCameraProperty");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetCameraProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, eProperty, &lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    if (ret != IC_SUCCESS)
    {
        return retObj;
    }
    Napi::Object data = Napi::Object::New(env);
    data.Set("lValue", Napi::Number::New(env, lValue));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_EnableAutoCameraProperty(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    CAMERA_PROPERTY iProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    int iOnOff = (int)info[2].As<Napi::Number>().Int32Value();

    IC_EnableAutoCameraProperty *fPtr = (IC_EnableAutoCameraProperty *)GetProcAddress(tisgrabber, "IC_EnableAutoCameraProperty");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EnableAutoCameraProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iProperty, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_IsCameraPropertyAutoAvailable(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    CAMERA_PROPERTY iProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();

    IC_IsCameraPropertyAutoAvailable *fPtr = (IC_IsCameraPropertyAutoAvailable *)GetProcAddress(tisgrabber, "IC_IsCameraPropertyAutoAvailable");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsCameraPropertyAutoAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iProperty);
    Napi::Object retObj = Napi::Object::New(env);
    BOOL_RETURN()
    return retObj;
}
Napi::Value f_IC_GetAutoCameraProperty(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iProperty = (int)info[1].As<Napi::Number>().Int64Value();
    int iOnOff = 0;

    IC_GetAutoCameraProperty *fPtr = (IC_GetAutoCameraProperty *)GetProcAddress(tisgrabber, "IC_GetAutoCameraProperty");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetAutoCameraProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iProperty, &iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Boolean::New(env, (bool)iOnOff));
    return retObj;
}
Napi::Value f_IC_IsVideoPropertyAvailable(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();

    IC_IsVideoPropertyAvailable *fPtr = (IC_IsVideoPropertyAvailable *)GetProcAddress(tisgrabber, "IC_IsVideoPropertyAvailable");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsVideoPropertyAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, eProperty);
    Napi::Object retObj = Napi::Object::New(env);
    BOOL_RETURN()
    return retObj;
}
Napi::Value f_IC_VideoPropertyGetRange(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long lMin = 0;
    long lMax = 0;

    IC_VideoPropertyGetRange *fPtr = (IC_VideoPropertyGetRange *)GetProcAddress(tisgrabber, "IC_VideoPropertyGetRange");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_VideoPropertyGetRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, eProperty, &lMin, &lMax);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    Napi::Object data = Napi::Object::New(env);
    data.Set("min", Napi::Number::New(env, lMin));
    data.Set("max", Napi::Number::New(env, lMax));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_GetVideoProperty(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long lValue = 0;

    IC_GetVideoProperty *fPtr = (IC_GetVideoProperty *)GetProcAddress(tisgrabber, "IC_GetVideoProperty");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, eProperty, &lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    Napi::Object data = Napi::Object::New(env);
    data.Set("lValue", Napi::Number::New(env, lValue));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_IsVideoPropertyAutoAvailable(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();

    IC_IsVideoPropertyAutoAvailable *fPtr = (IC_IsVideoPropertyAutoAvailable *)GetProcAddress(tisgrabber, "IC_IsVideoPropertyAutoAvailable");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsVideoPropertyAutoAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, eProperty);
    Napi::Object retObj = Napi::Object::New(env);
    BOOL_RETURN()
    return retObj;
}
Napi::Value f_IC_GetAutoVideoProperty(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iProperty = (int)info[1].As<Napi::Number>().Int64Value();
    int iOnOff = 0;

    IC_GetAutoVideoProperty *fPtr = (IC_GetAutoVideoProperty *)GetProcAddress(tisgrabber, "IC_GetAutoVideoProperty");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetAutoVideoProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iProperty, &iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Boolean::New(env, (bool)iOnOff));
    return retObj;
}
Napi::Value f_IC_SetVideoProperty(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long lValue = (long)info[2].As<Napi::Number>().Int64Value();

    IC_SetVideoProperty *fPtr = (IC_SetVideoProperty *)GetProcAddress(tisgrabber, "IC_SetVideoProperty");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetVideoProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, eProperty, lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_EnableAutoVideoProperty(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iProperty = (int)info[1].As<Napi::Number>().Int32Value();
    int iOnOff = (int)info[2].As<Napi::Number>().Int32Value();

    IC_EnableAutoVideoProperty *fPtr = (IC_EnableAutoVideoProperty *)GetProcAddress(tisgrabber, "IC_EnableAutoVideoProperty");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EnableAutoVideoProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iProperty, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetImageDescription(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    long lWidth = 0;
    long lHeight = 0;
    int iBitsPerPixel = 0;
    COLORFORMAT format = NONE;

    IC_GetImageDescription *fPtr = (IC_GetImageDescription *)GetProcAddress(tisgrabber, "IC_GetImageDescription");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetImageDescription in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, &lWidth, &lHeight, &iBitsPerPixel, &format);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("data", Napi::Number::New(env, ret));
    Napi::Object data = Napi::Object::New(env);
    data.Set("width", Napi::Number::New(env, lWidth));
    data.Set("height", Napi::Number::New(env, lHeight));
    data.Set("bitsPerPixel", Napi::Number::New(env, iBitsPerPixel));
    data.Set("format", Napi::Number::New(env, format));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_SnapImage(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iTimeOutMillisek = (int)info[1].As<Napi::Number>().Int64Value();

    IC_SnapImage *fPtr = (IC_SnapImage *)GetProcAddress(tisgrabber, "IC_SnapImage");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SnapImage in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iTimeOutMillisek);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SaveImage(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 4)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[3].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 3").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szFileNameStr = info[1].As<Napi::String>().Utf8Value();
    char *szFileName = (char *)szFileNameStr.c_str();

    IMG_FILETYPE ft = (IMG_FILETYPE)info[2].As<Napi::Number>().Int32Value();
    long quality = (long)info[3].As<Napi::Number>().Int64Value();

    IC_SaveImage *fPtr = (IC_SaveImage *)GetProcAddress(tisgrabber, "IC_SaveImage");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SaveImage in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szFileName, ft, quality);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}

Napi::Value f_IC_SetHWnd(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    __HWND hWnd = *info[1].As<Napi::Buffer<__HWND>>().Data();

    IC_SetHWnd *fPtr = (IC_SetHWnd *)GetProcAddress(tisgrabber, "IC_SetHWnd");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetHWnd in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, hWnd);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetSerialNumber(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    char szSerial[20];

    IC_GetSerialNumber *fPtr = (IC_GetSerialNumber *)GetProcAddress(tisgrabber, "IC_GetSerialNumber");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetSerialNumber in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szSerial);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    // 这里 dll 的实现有 bug，实测成功获取到 szSerial 但是会返回 IC_ERROR，因此如下判断
    if (ret == IC_SUCCESS || ret == IC_ERROR)
    {
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
        retObj.Set("data", Napi::String::New(env, szSerial));
    }
    return retObj;
}

Napi::Value f_IC_GetDeviceCount(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 0)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    IC_GetDeviceCount *fPtr = (IC_GetDeviceCount *)GetProcAddress(tisgrabber, "IC_GetDeviceCount");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetDeviceCount in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f();
    Napi::Object retObj = Napi::Object::New(env);
    if (ret < 0)
    {
        retObj.Set("code", Napi::Number::New(env, IC_ERROR));
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
        retObj.Set("data", Napi::Number::New(env, ret));
    }

    return retObj;
}
Napi::Value f_IC_GetDevice(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    int iIndex = (int)info[0].As<Napi::Number>().Int64Value();

    IC_GetDevice *fPtr = (IC_GetDevice *)GetProcAddress(tisgrabber, "IC_GetDevice");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetDevice in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    char *ret = f(iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    STRING_RETURN()
    return retObj;
}
Napi::Value f_IC_GetUniqueNamefromList(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    int iIndex = (int)info[0].As<Napi::Number>().Int64Value();

    IC_GetUniqueNamefromList *fPtr = (IC_GetUniqueNamefromList *)GetProcAddress(tisgrabber, "IC_GetUniqueNamefromList");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetUniqueNamefromList in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    char *ret = f(iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    STRING_RETURN()
    return retObj;
}
Napi::Value f_IC_GetInputChannelCount(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetInputChannelCount *fPtr = (IC_GetInputChannelCount *)GetProcAddress(tisgrabber, "IC_GetInputChannelCount");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetInputChannelCount in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    COUNT_RETURN()
    return retObj;
}
Napi::Value f_IC_GetInputChannel(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iIndex = (int)info[1].As<Napi::Number>().Int64Value();

    IC_GetInputChannel *fPtr = (IC_GetInputChannel *)GetProcAddress(tisgrabber, "IC_GetInputChannel");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetInputChannel in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    char *ret = f(hGrabber, iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    STRING_RETURN()
    return retObj;
}
Napi::Value f_IC_GetVideoNormCount(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetVideoNormCount *fPtr = (IC_GetVideoNormCount *)GetProcAddress(tisgrabber, "IC_GetVideoNormCount");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoNormCount in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    COUNT_RETURN()
    return retObj;
}
Napi::Value f_IC_GetVideoNorm(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iIndex = (int)info[1].As<Napi::Number>().Int64Value();

    IC_GetVideoNorm *fPtr = (IC_GetVideoNorm *)GetProcAddress(tisgrabber, "IC_GetVideoNorm");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoNorm in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    char *ret = f(hGrabber, iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    STRING_RETURN()
    return retObj;
}
Napi::Value f_IC_GetVideoFormatCount(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetVideoFormatCount *fPtr = (IC_GetVideoFormatCount *)GetProcAddress(tisgrabber, "IC_GetVideoFormatCount");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoFormatCount in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    COUNT_RETURN()
    return retObj;
}
Napi::Value f_IC_GetVideoFormat(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iIndex = (int)info[1].As<Napi::Number>().Int64Value();

    IC_GetVideoFormat *fPtr = (IC_GetVideoFormat *)GetProcAddress(tisgrabber, "IC_GetVideoFormat");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoFormat in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    char *ret = f(hGrabber, iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    STRING_RETURN()
    return retObj;
}
Napi::Value f_IC_SaveDeviceStateToFile(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szFileNameStr = info[1].As<Napi::String>().Utf8Value();
    char *szFileName = (char *)szFileNameStr.c_str();

    IC_SaveDeviceStateToFile *fPtr = (IC_SaveDeviceStateToFile *)GetProcAddress(tisgrabber, "IC_SaveDeviceStateToFile");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SaveDeviceStateToFile in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szFileName);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_LoadDeviceStateFromFileEx(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szFileNameStr = info[1].As<Napi::String>().Utf8Value();
    char *szFileName = (char *)szFileNameStr.c_str();

    int OpenDevice = (int)info[2].As<Napi::Number>().Int32Value();

    IC_LoadDeviceStateFromFileEx *fPtr = (IC_LoadDeviceStateFromFileEx *)GetProcAddress(tisgrabber, "IC_LoadDeviceStateFromFileEx");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_LoadDeviceStateFromFileEx in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szFileName, OpenDevice);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SaveDeviceSettings(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szFilenameStr = info[1].As<Napi::String>().Utf8Value();
    char *szFilename = (char *)szFilenameStr.c_str();

    IC_SaveDeviceSettings *fPtr = (IC_SaveDeviceSettings *)GetProcAddress(tisgrabber, "IC_SaveDeviceSettings");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SaveDeviceSettings in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szFilename);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_OpenDeviceBySettings(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szFilenameStr = info[1].As<Napi::String>().Utf8Value();
    char *szFilename = (char *)szFilenameStr.c_str();

    IC_OpenDeviceBySettings *fPtr = (IC_OpenDeviceBySettings *)GetProcAddress(tisgrabber, "IC_OpenDeviceBySettings");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_OpenDeviceBySettings in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szFilename);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("data", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_LoadDeviceSettings(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szFilenameStr = info[1].As<Napi::String>().Utf8Value();
    char *szFilename = (char *)szFilenameStr.c_str();

    IC_LoadDeviceSettings *fPtr = (IC_LoadDeviceSettings *)GetProcAddress(tisgrabber, "IC_LoadDeviceSettings");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_LoadDeviceSettings in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szFilename);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_OpenDevByDisplayName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szDisplaynameStr = info[1].As<Napi::String>().Utf8Value();
    char *szDisplayname = (char *)szDisplaynameStr.c_str();

    IC_OpenDevByDisplayName *fPtr = (IC_OpenDevByDisplayName *)GetProcAddress(tisgrabber, "IC_OpenDevByDisplayName");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_OpenDevByDisplayName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szDisplayname);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetDisplayName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetDisplayName *fPtr = (IC_GetDisplayName *)GetProcAddress(tisgrabber, "IC_GetDisplayName");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetDisplayName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int len = f(hGrabber, nullptr, 0);
    if (len <= 1)
    {
        Napi::Error::New(env, "Cannot get display name lenght").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    char *szDisplayname = (char *)malloc(len * sizeof(char));
    if (szDisplayname == nullptr)
    {
        Napi::Error::New(env, "Cannot allocate memory for display name").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    int ret = f(hGrabber, szDisplayname, len);
    Napi::Object retObj = Napi::Object::New(env);
    if (ret == IC_SUCCESS)
    {
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
        retObj.Set("data", Napi::String::New(env, szDisplayname));
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, ret));
    }
    retObj.Set("data", Napi::Number::New(env, ret));
    free(szDisplayname);
    return retObj;
}
Napi::Value f_IC_OpenDevByUniqueName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[0].IsExternal())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szUniqueNameStr = info[1].As<Napi::String>().Utf8Value();
    char *szUniqueName = (char *)szUniqueNameStr.c_str();

    IC_OpenDevByUniqueName *fPtr = (IC_OpenDevByUniqueName *)GetProcAddress(tisgrabber, "IC_OpenDevByUniqueName");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_OpenDevByUniqueName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szUniqueName);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}

Napi::Value f_IC_GetUniqueName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetUniqueName *fPtr = (IC_GetUniqueName *)GetProcAddress(tisgrabber, "IC_GetUniqueName");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetUniqueName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int len = f(hGrabber, nullptr, 0);
    if (len <= 1)
    {
        Napi::Error::New(env, "Cannot get unique name lenght").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    int lenWithNull = len + 1;
    char *szUniqueName = new char[lenWithNull];
    memset(szUniqueName, 0, lenWithNull);
    int ret = f(hGrabber, szUniqueName, len);
    Napi::Object retObj = Napi::Object::New(env);
    if (ret == IC_SUCCESS)
    {
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
        retObj.Set("data", Napi::String::New(env, szUniqueName));
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, ret));
    }
    delete szUniqueName;
    return retObj;
}
Napi::Value f_IC_IsDevValid(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_IsDevValid *fPtr = (IC_IsDevValid *)GetProcAddress(tisgrabber, "IC_IsDevValid");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsDevValid in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    BOOL_RETURN()
    return retObj;
}
Napi::Value f_IC_ShowPropertyDialog(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_ShowPropertyDialog *fPtr = (IC_ShowPropertyDialog *)GetProcAddress(tisgrabber, "IC_ShowPropertyDialog");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ShowPropertyDialog in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_ShowDeviceSelectionDialog(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_ShowDeviceSelectionDialog *fPtr = (IC_ShowDeviceSelectionDialog *)GetProcAddress(tisgrabber, "IC_ShowDeviceSelectionDialog");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ShowDeviceSelectionDialog in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    HGRABBER ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::External<HGRABBER>::New(env, &ret));
    return retObj;
}
Napi::Value f_IC_IsTriggerAvailable(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_IsTriggerAvailable *fPtr = (IC_IsTriggerAvailable *)GetProcAddress(tisgrabber, "IC_IsTriggerAvailable");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsTriggerAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    BOOL_RETURN()
    return retObj;
}
Napi::Value f_IC_EnableTrigger(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsBoolean())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iEnable = (int)info[1].As<Napi::Boolean>().Value();

    IC_EnableTrigger *fPtr = (IC_EnableTrigger *)GetProcAddress(tisgrabber, "IC_EnableTrigger");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EnableTrigger in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iEnable);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}

Napi::Value f_IC_MsgBox(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto szTextStr = info[0].As<Napi::String>().Utf8Value();
    char *szText = (char *)szTextStr.c_str();

    auto szTitleStr = info[1].As<Napi::String>().Utf8Value();
    char *szTitle = (char *)szTitleStr.c_str();

    IC_MsgBox *fPtr = (IC_MsgBox *)GetProcAddress(tisgrabber, "IC_MsgBox");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_MsgBox in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    f(szText, szTitle);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    return retObj;
}
Napi::Value f_IC_SetContinuousMode(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int cont = (int)info[1].As<Napi::Number>().Int32Value();

    IC_SetContinuousMode *fPtr = (IC_SetContinuousMode *)GetProcAddress(tisgrabber, "IC_SetContinuousMode");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetContinuousMode in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, cont);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetFrameRate(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    float FrameRate = (float)info[1].As<Napi::Number>().FloatValue();

    IC_SetFrameRate *fPtr = (IC_SetFrameRate *)GetProcAddress(tisgrabber, "IC_SetFrameRate");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetFrameRate in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, FrameRate);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetFrameRate(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetFrameRate *fPtr = (IC_GetFrameRate *)GetProcAddress(tisgrabber, "IC_GetFrameRate");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetFrameRate in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    float ret = f(hGrabber);
    bool supported = ret > 0;
    Napi::Object retObj = Napi::Object::New(env);
    if (supported)
    {
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
        retObj.Set("data", Napi::Number::New(env, ret));
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, IC_ERROR));
        retObj.Set("message", "Frame rate not supported");
    }

    return retObj;
}
Napi::Value f_IC_GetAvailableFrameRates(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetAvailableFrameRates *fPtr = (IC_GetAvailableFrameRates *)GetProcAddress(tisgrabber, "IC_GetAvailableFrameRates");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetAvailableFrameRates in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;

    std::vector<float> fpsList;
    int Index = 0;
    float fps = 0.0f;
    while (f(hGrabber, Index, &fps) == IC_SUCCESS)
    {
        fpsList.push_back(fps);
        Index++;
    }
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    retObj.Set("data", FloatVectorToJsArray(env, fpsList));
    return retObj;
}
Napi::Value f_IC_SetDefaultWindowPosition(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int Default = (int)info[1].As<Napi::Number>().Int32Value();

    IC_SetDefaultWindowPosition *fPtr = (IC_SetDefaultWindowPosition *)GetProcAddress(tisgrabber, "IC_SetDefaultWindowPosition");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetDefaultWindowPosition in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Default);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetWindowPosition(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 5)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[3].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 3").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[4].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 4").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int PosX = (int)info[1].As<Napi::Number>().Int64Value();
    int PosY = (int)info[2].As<Napi::Number>().Int64Value();
    int Width = (int)info[3].As<Napi::Number>().Int64Value();
    int Height = (int)info[4].As<Napi::Number>().Int64Value();

    IC_SetWindowPosition *fPtr = (IC_SetWindowPosition *)GetProcAddress(tisgrabber, "IC_SetWindowPosition");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWindowPosition in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, PosX, PosY, Width, Height);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetWindowPosition(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int PosX = 0;
    int PosY = 0;
    int Width = 0;
    int Height = 0;

    IC_GetWindowPosition *fPtr = (IC_GetWindowPosition *)GetProcAddress(tisgrabber, "IC_GetWindowPosition");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetWindowPosition in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, &PosX, &PosY, &Width, &Height);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    Napi::Object data = Napi::Object::New(env);
    data.Set("PosX", Napi::Number::New(env, PosX));
    data.Set("PosY", Napi::Number::New(env, PosY));
    data.Set("Width", Napi::Number::New(env, Width));
    data.Set("Height", Napi::Number::New(env, Height));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_SetWhiteBalanceAuto(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iOnOff = (int)info[1].As<Napi::Number>().Int32Value();

    IC_SetWhiteBalanceAuto *fPtr = (IC_SetWhiteBalanceAuto *)GetProcAddress(tisgrabber, "IC_SetWhiteBalanceAuto");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWhiteBalanceAuto in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SignalDetected(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_SignalDetected *fPtr = (IC_SignalDetected *)GetProcAddress(tisgrabber, "IC_SignalDetected");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SignalDetected in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    BOOL_RETURN()
    return retObj;
}
Napi::Value f_IC_GetTriggerModes(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_GetTriggerModes *fPtr = (IC_GetTriggerModes *)GetProcAddress(tisgrabber, "IC_GetTriggerModes");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetTriggerModes in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    Napi::Object retObj = Napi::Object::New(env);
    Napi::Array modesArr = Napi::Array::New(env);
    retObj.Set("data", modesArr);
    auto f = *fPtr;
    const int SIZE = 20;
    char szModes[SIZE][10];
    int iModeCount;
    iModeCount = f(hGrabber, (char *)szModes, SIZE);
    if (iModeCount < 0)
    {
        Napi::Error::New(env, "IC_GetTriggerModes error").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    else
    {
        for (size_t i = 0; i < min(iModeCount, SIZE); i++)
        {
            modesArr.Set(i, Napi::String::New(env, szModes[i]));
        }
    }

    int ret = f(hGrabber, (char *)szModes, SIZE);

    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    retObj.Set("data", modesArr);
    return retObj;
}
Napi::Value f_IC_SetTriggerMode(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto szModeStr = info[1].As<Napi::String>().Utf8Value();
    char *szMode = (char *)szModeStr.c_str();

    IC_SetTriggerMode *fPtr = (IC_SetTriggerMode *)GetProcAddress(tisgrabber, "IC_SetTriggerMode");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetTriggerMode in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, szMode);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetTriggerPolarity(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iPolarity = (int)info[1].As<Napi::Number>().Int64Value();

    IC_SetTriggerPolarity *fPtr = (IC_SetTriggerPolarity *)GetProcAddress(tisgrabber, "IC_SetTriggerPolarity");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetTriggerPolarity in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iPolarity);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetExpRegValRange(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    long lMin = 0;
    long lMax = 0;

    IC_GetExpRegValRange *fPtr = (IC_GetExpRegValRange *)GetProcAddress(tisgrabber, "IC_GetExpRegValRange");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpRegValRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, &lMin, &lMax);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    Napi::Object data = Napi::Object::New(env);
    data.Set("min", Napi::Number::New(env, lMin));
    data.Set("max", Napi::Number::New(env, lMax));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_GetExpRegVal(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    long lValue = 0;

    IC_GetExpRegVal *fPtr = (IC_GetExpRegVal *)GetProcAddress(tisgrabber, "IC_GetExpRegVal");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpRegVal in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, &lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Number::New(env, lValue));
    return retObj;
}
Napi::Value f_IC_SetExpRegVal(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    long lValue = (long)info[1].As<Napi::Number>().Int64Value();

    IC_SetExpRegVal *fPtr = (IC_SetExpRegVal *)GetProcAddress(tisgrabber, "IC_SetExpRegVal");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetExpRegVal in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_EnableExpRegValAuto(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iOnOff = (int)info[1].As<Napi::Number>().Int32Value();

    IC_EnableExpRegValAuto *fPtr = (IC_EnableExpRegValAuto *)GetProcAddress(tisgrabber, "IC_EnableExpRegValAuto");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EnableExpRegValAuto in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetExpRegValAuto(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int iOnOff = 0;

    IC_GetExpRegValAuto *fPtr = (IC_GetExpRegValAuto *)GetProcAddress(tisgrabber, "IC_GetExpRegValAuto");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpRegValAuto in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, &iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Boolean::New(env, (bool)iOnOff));
    return retObj;
}
Napi::Value f_IC_IsExpAbsValAvailable(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_IsExpAbsValAvailable *fPtr = (IC_IsExpAbsValAvailable *)GetProcAddress(tisgrabber, "IC_IsExpAbsValAvailable");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsExpAbsValAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    BOOL_RETURN()
    return retObj;
}
Napi::Value f_IC_GetExpAbsValRange(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    float fMin = 0;
    float fMax = 0;

    IC_GetExpAbsValRange *fPtr = (IC_GetExpAbsValRange *)GetProcAddress(tisgrabber, "IC_GetExpAbsValRange");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpAbsValRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, &fMin, &fMax);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    if (ret == IC_SUCCESS)
    {
        Napi::Object data = Napi::Object::New(env);
        data.Set("fMin", Napi::Number::New(env, fMin));
        data.Set("fMax", Napi::Number::New(env, fMax));
        retObj.Set("data", data);
    }
    return retObj;
}
Napi::Value f_IC_GetExpAbsVal(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    float fValue = 0;

    IC_GetExpAbsVal *fPtr = (IC_GetExpAbsVal *)GetProcAddress(tisgrabber, "IC_GetExpAbsVal");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpAbsVal in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, &fValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    if (ret == IC_SUCCESS)
    {
        retObj.Set("data", Napi::Number::New(env, fValue));
    }

    return retObj;
}
Napi::Value f_IC_SetExpAbsVal(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    float fValue = (float)info[1].As<Napi::Number>().DoubleValue();

    IC_SetExpAbsVal *fPtr = (IC_SetExpAbsVal *)GetProcAddress(tisgrabber, "IC_SetExpAbsVal");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetExpAbsVal in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, fValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetColorEnhancement(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int OnOff = 0;

    IC_GetColorEnhancement *fPtr = (IC_GetColorEnhancement *)GetProcAddress(tisgrabber, "IC_GetColorEnhancement");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetColorEnhancement in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, &OnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    if (ret == IC_SUCCESS)
    {
        retObj.Set("data", Napi::Boolean::New(env, (bool)OnOff));
    }
    return retObj;
}
Napi::Value f_IC_SetColorEnhancement(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int OnOff = (int)info[1].As<Napi::Number>().Int32Value();

    IC_SetColorEnhancement *fPtr = (IC_SetColorEnhancement *)GetProcAddress(tisgrabber, "IC_SetColorEnhancement");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetColorEnhancement in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, OnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SoftwareTrigger(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_SoftwareTrigger *fPtr = (IC_SoftwareTrigger *)GetProcAddress(tisgrabber, "IC_SoftwareTrigger");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SoftwareTrigger in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetWhiteBalanceRed(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    long Value = (long)info[1].As<Napi::Number>().Int64Value();

    IC_SetWhiteBalanceRed *fPtr = (IC_SetWhiteBalanceRed *)GetProcAddress(tisgrabber, "IC_SetWhiteBalanceRed");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWhiteBalanceRed in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetWhiteBalanceGreen(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    long Value = (long)info[1].As<Napi::Number>().Int64Value();

    IC_SetWhiteBalanceGreen *fPtr = (IC_SetWhiteBalanceGreen *)GetProcAddress(tisgrabber, "IC_SetWhiteBalanceGreen");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWhiteBalanceGreen in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_SetWhiteBalanceBlue(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    long Value = (long)info[1].As<Napi::Number>().Int64Value();

    IC_SetWhiteBalanceBlue *fPtr = (IC_SetWhiteBalanceBlue *)GetProcAddress(tisgrabber, "IC_SetWhiteBalanceBlue");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWhiteBalanceBlue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_FocusOnePush(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_FocusOnePush *fPtr = (IC_FocusOnePush *)GetProcAddress(tisgrabber, "IC_FocusOnePush");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_FocusOnePush in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}

Napi::Value f_IC_enumProperties(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    if (!info[1].IsFunction())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    Napi::Function callback = info[1].As<Napi::Function>();

    IC_enumProperties *fPtr = (IC_enumProperties *)GetProcAddress(tisgrabber, "IC_enumProperties");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_enumProperties in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    auto cbRef = Napi::Weak(callback);
    EnumCbData cbData = {cbRef};
    int ret = f(hGrabber, EnumCb, &cbData);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}

Napi::Value f_IC_enumPropertyElements(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsFunction())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    Napi::Function callback = info[2].As<Napi::Function>();

    IC_enumPropertyElements *fPtr = (IC_enumPropertyElements *)GetProcAddress(tisgrabber, "IC_enumPropertyElements");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_enumPropertyElements in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    auto cbRef = Napi::Weak(callback);
    EnumCbData cbData = {cbRef};
    int ret = f(hGrabber, Property, EnumCb, &cbData);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}

Napi::Value f_IC_enumPropertyElementInterfaces(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 4)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[3].IsFunction())
    {
        Napi::TypeError::New(env, "Wrong type of argument 3").ThrowAsJavaScriptException();
        return env.Undefined();
    };

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();
    Napi::Function callback = info[3].As<Napi::Function>();

    IC_enumPropertyElementInterfaces *fPtr = (IC_enumPropertyElementInterfaces *)GetProcAddress(tisgrabber, "IC_enumPropertyElementInterfaces");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_enumPropertyElementInterfaces in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    auto cbRef = Napi::Weak(callback);
    EnumCbData cbData = {cbRef};
    int ret = f(hGrabber, Property, Element, EnumCb, &cbData);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}

Napi::Value f_IC_IsPropertyAvailable(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString() && !info[2].IsNull())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    char *Element = nullptr;
    if (info[2].IsString())
    {
        auto ElementStr = info[2].As<Napi::String>().Utf8Value();
        Element = (char *)ElementStr.c_str();
    }

    IC_IsPropertyAvailable *fPtr = (IC_IsPropertyAvailable *)GetProcAddress(tisgrabber, "IC_IsPropertyAvailable");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsPropertyAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element);
    Napi::Object retObj = Napi::Object::New(env);
    if (ret == IC_SUCCESS)
    {
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
        retObj.Set("data", Napi::Boolean::New(env, true));
    }
    else if (ret == IC_NO_HANDLE || ret == IC_NO_DEVICE)
    {
        retObj.Set("code", Napi::Number::New(env, ret));
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
        retObj.Set("data", Napi::Boolean::New(env, false));
    }
    return retObj;
}

Napi::Value f_IC_GetPropertyValueRange(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();
    int Min = 0;
    int Max = 0;

    IC_GetPropertyValueRange *fPtr = (IC_GetPropertyValueRange *)GetProcAddress(tisgrabber, "IC_GetPropertyValueRange");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyValueRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element, &Min, &Max);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    Napi::Object data = Napi::Object::New(env);
    data.Set("min", Napi::Number::New(env, Min));
    data.Set("max", Napi::Number::New(env, Max));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_GetPropertyValue(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();
    int Value = 0;

    IC_GetPropertyValue *fPtr = (IC_GetPropertyValue *)GetProcAddress(tisgrabber, "IC_GetPropertyValue");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyValue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element, &Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Number::New(env, Value));
    return retObj;
}
Napi::Value f_IC_SetPropertyValue(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 4)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[3].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 3").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();
    int Value = (int)info[3].As<Napi::Number>().Int64Value();

    IC_SetPropertyValue *fPtr = (IC_SetPropertyValue *)GetProcAddress(tisgrabber, "IC_SetPropertyValue");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetPropertyValue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetPropertyAbsoluteValueRange(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();
    float Min = 0;
    float Max = 0;

    IC_GetPropertyAbsoluteValueRange *fPtr = (IC_GetPropertyAbsoluteValueRange *)GetProcAddress(tisgrabber, "IC_GetPropertyAbsoluteValueRange");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyAbsoluteValueRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element, &Min, &Max);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    Napi::Object data = Napi::Object::New(env);
    data.Set("min", Napi::Number::New(env, Min));
    data.Set("max", Napi::Number::New(env, Max));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_GetPropertyAbsoluteValue(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();
    float Value = 0;

    IC_GetPropertyAbsoluteValue *fPtr = (IC_GetPropertyAbsoluteValue *)GetProcAddress(tisgrabber, "IC_GetPropertyAbsoluteValue");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyAbsoluteValue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element, &Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Number::New(env, Value));
    return retObj;
}
Napi::Value f_IC_SetPropertyAbsoluteValue(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 4)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[3].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 3").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();
    float Value = (float)info[3].As<Napi::Number>().DoubleValue();

    IC_SetPropertyAbsoluteValue *fPtr = (IC_SetPropertyAbsoluteValue *)GetProcAddress(tisgrabber, "IC_SetPropertyAbsoluteValue");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetPropertyAbsoluteValue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetPropertySwitch(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();
    int On = 0;

    IC_GetPropertySwitch *fPtr = (IC_GetPropertySwitch *)GetProcAddress(tisgrabber, "IC_GetPropertySwitch");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertySwitch in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element, &On);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Number::New(env, On));
    return retObj;
}
Napi::Value f_IC_SetPropertySwitch(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 4)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[3].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 3").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();
    int On = (int)info[3].As<Napi::Number>().Int32Value();

    IC_SetPropertySwitch *fPtr = (IC_SetPropertySwitch *)GetProcAddress(tisgrabber, "IC_SetPropertySwitch");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetPropertySwitch in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element, On);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_PropertyOnePush(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();
    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();

    IC_PropertyOnePush *fPtr = (IC_PropertyOnePush *)GetProcAddress(tisgrabber, "IC_PropertyOnePush");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_PropertyOnePush in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}

Napi::Value f_IC_GetPropertyMapStrings(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 4)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();

    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();

    IC_GetPropertyMapStrings *fPtr = (IC_GetPropertyMapStrings *)GetProcAddress(tisgrabber, "IC_GetPropertyMapStrings");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyMapStrings in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int StringCount = 0;
    int StringLength = 0;
    char **Strings = nullptr;
    Napi::Object retObj = Napi::Object::New(env);
    int getSizeRet = f(hGrabber, Property, Element, &StringCount, &StringLength, nullptr);
    if (getSizeRet == IC_SUCCESS)
    {
        int stringCountWithNull = StringLength + 1;
        char **Strings = new char *[stringCountWithNull];
        memset(Strings, 0, stringCountWithNull);

        for (size_t i = 0; i < StringCount; i++)
        {
            int stringLengthWithNull = StringLength + 1;
            Strings[i] = new char[stringLengthWithNull];
            memset(Strings[i], 0, stringLengthWithNull);
        }

        // Second call, fill the created array:
        int ret = f(hGrabber, Property, Element, &StringCount, &StringLength, Strings);

        if (ret == IC_SUCCESS)
        {
            Napi::Array arr = Napi::Array::New(env);
            for (size_t i = 0; i < StringCount; i++)
            {
                arr.Set(i, Napi::String::New(env, Strings[i]));
            }
            retObj.Set("data", arr);
            retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
        }
        else
        {
            retObj.Set("code", Napi::Number::New(env, ret));
        }
        // Clean up
        for (size_t j = 0; j < StringCount; j++)
            delete Strings[j];

        delete Strings;
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, getSizeRet));
        retObj.Set("message", Napi::String::New(env, "Cannot get size of array"));
    }
    return retObj;
}

Napi::Value f_IC_GetPropertyMapString(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 4)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();

    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();

    IC_GetPropertyMapString *fPtr = (IC_GetPropertyMapString *)GetProcAddress(tisgrabber, "IC_GetPropertyMapString");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyMapString in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int StringLength = 0;
    Napi::Object retObj = Napi::Object::New(env);
    int getLengthRet = f(hGrabber, Property, Element, &StringLength, nullptr);
    if (getLengthRet == IC_SUCCESS)
    {
        int stringLengthWithNull = StringLength + 1;
        char *String = new char[stringLengthWithNull];
        memset(String, 0, stringLengthWithNull);
        int ret = f(hGrabber, Property, Element, &StringLength, String);
        retObj.Set("code", Napi::Number::New(env, ret));
        retObj.Set("data", Napi::String::New(env, String));
        delete String;
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, getLengthRet));
        retObj.Set("message", Napi::String::New(env, "Cannot get length of string"));
    }
    return retObj;
}
Napi::Value f_IC_SetPropertyMapString(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 4)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[3].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 3").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    auto PropertyStr = info[1].As<Napi::String>().Utf8Value();
    char *Property = (char *)PropertyStr.c_str();

    auto ElementStr = info[2].As<Napi::String>().Utf8Value();
    char *Element = (char *)ElementStr.c_str();

    auto StringStr = info[3].As<Napi::String>().Utf8Value();
    char *String = (char *)StringStr.c_str();

    IC_SetPropertyMapString *fPtr = (IC_SetPropertyMapString *)GetProcAddress(tisgrabber, "IC_SetPropertyMapString");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetPropertyMapString in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Property, Element, String);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_ResetProperties(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();

    IC_ResetProperties *fPtr = (IC_ResetProperties *)GetProcAddress(tisgrabber, "IC_ResetProperties");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ResetProperties in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}

Napi::Value f_IC_SetRingBufferSize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int Count = (int)info[1].As<Napi::Number>().Int64Value();

    IC_SetRingBufferSize *fPtr = (IC_SetRingBufferSize *)GetProcAddress(tisgrabber, "IC_SetRingBufferSize");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetRingBufferSize in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Count);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_GetRingBufferSize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int pCount = 0;

    IC_GetRingBufferSize *fPtr = (IC_GetRingBufferSize *)GetProcAddress(tisgrabber, "IC_GetRingBufferSize");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetRingBufferSize in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, &pCount);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Number::New(env, pCount));
    return retObj;
}

Napi::Value f_IC_GetMemBuffer(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    int Index = info[1].As<Napi::Number>().Int32Value();
    HMEMBUFFER *phBuffer;

    IC_GetMemBuffer *fPtr = (IC_GetMemBuffer *)GetProcAddress(tisgrabber, "IC_GetMemBuffer");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetMemBuffer in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, Index, phBuffer);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::External<ImageBuffer>::New(env, *phBuffer));
    return retObj;
}

Napi::Value f_IC_GetMemBufferLastAcq(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    HMEMBUFFER *phBuffer;

    IC_GetMemBufferLastAcq *fPtr = (IC_GetMemBufferLastAcq *)GetProcAddress(tisgrabber, "IC_GetMemBufferLastAcq");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetMemBufferLastAcq in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hGrabber, phBuffer);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    if (ret == IC_SUCCESS)
    {
        retObj.Set("data", Napi::External<ImageBuffer>::New(env, *phBuffer));
    }

    return retObj;
}

Napi::Value f_IC_GetMemBufferDescription(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HMEMBUFFER hBuffer = info[0].As<Napi::External<ImageBuffer>>().Data();
    int pWidth = 0;
    int pHeight = 0;
    int pBitsPerPixel = 0;

    IC_GetMemBufferDescription *fPtr = (IC_GetMemBufferDescription *)GetProcAddress(tisgrabber, "IC_GetMemBufferDescription");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetMemBufferDescription in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hBuffer, &pWidth, &pHeight, &pBitsPerPixel);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    Napi::Object data = Napi::Object::New(env);
    data.Set("width", Napi::Number::New(env, pWidth));
    data.Set("height", Napi::Number::New(env, pHeight));
    data.Set("bitsPerPixel", Napi::Number::New(env, pBitsPerPixel));
    retObj.Set("data", data);
    return retObj;
}
Napi::Value f_IC_MemBufferLock(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    HMEMBUFFER hBuffer = info[0].As<Napi::External<ImageBuffer>>().Data();
    int lock = (int)info[1].As<Napi::Number>().Int32Value();

    IC_MemBufferLock *fPtr = (IC_MemBufferLock *)GetProcAddress(tisgrabber, "IC_MemBufferLock");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_MemBufferLock in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hBuffer, lock);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    return retObj;
}
Napi::Value f_IC_MemBufferisLocked(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HMEMBUFFER hBuffer = info[0].As<Napi::External<ImageBuffer>>().Data();
    int plocked = 0;

    IC_MemBufferisLocked *fPtr = (IC_MemBufferisLocked *)GetProcAddress(tisgrabber, "IC_MemBufferisLocked");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_MemBufferisLocked in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hBuffer, &plocked);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Boolean::New(env, (bool)plocked));
    return retObj;
}
Napi::Value f_IC_MemBufferGetIndex(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HMEMBUFFER hBuffer = info[0].As<Napi::External<ImageBuffer>>().Data();
    int pIndex = 0;

    IC_MemBufferGetIndex *fPtr = (IC_MemBufferGetIndex *)GetProcAddress(tisgrabber, "IC_MemBufferGetIndex");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_MemBufferGetIndex in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *fPtr;
    int ret = f(hBuffer, &pIndex);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("code", Napi::Number::New(env, ret));
    retObj.Set("data", Napi::Number::New(env, pIndex));
    return retObj;
}
Napi::Value f_IC_MemBufferGetData(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HMEMBUFFER hBuffer = info[0].As<Napi::External<ImageBuffer>>().Data();
    IC_MemBufferGetDataPtr *fPtr = (IC_MemBufferGetDataPtr *)GetProcAddress(tisgrabber, "IC_MemBufferGetDataPtr");
    IC_GetMemBufferDescription *f_ptr_get_desc = (IC_GetMemBufferDescription *)GetProcAddress(tisgrabber, "IC_GetMemBufferDescription");
    if (fPtr == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_MemBufferGetDataPtr in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (f_ptr_get_desc == nullptr)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetMemBufferDescription in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    Napi::Object retObj = Napi::Object::New(env);
    int pWidth = 0;
    int pHeight = 0;
    int pBitsPerPixel = 0;
    if ((*f_ptr_get_desc)(hBuffer, &pWidth, &pHeight, &pBitsPerPixel) == IC_SUCCESS)
    {
        size_t size = (pWidth) * (pHeight) * (pBitsPerPixel) / 8;
        auto f = *fPtr;
        unsigned char *bufferPtr = nullptr;
        int ret = f(hBuffer, &bufferPtr);
        if (ret == IC_SUCCESS)
        {
            Napi::Buffer<unsigned char> buffer = Napi::Buffer<unsigned char>::Copy(env, bufferPtr, size);
            retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
            retObj.Set("data", buffer);
        }
        else
        {
            retObj.Set("code", Napi::Number::New(env, ret));
            retObj.Set("message", Napi::String::New(env, "Cannot get buffer data"));
        }
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, IC_ERROR));
        retObj.Set("message", Napi::String::New(env, "Cannot get buffer description"));
    }
}

Napi::Value f_IC_SetFrameReadyCallbackEx(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    Napi::Function cb = info[1].As<Napi::Function>();
    Napi::Object retObj = Napi::Object::New(env);
    if (g_frameReadyCb == nullptr)
    {
        IC_SetFrameReadyCallbackEx *fPtr = (IC_SetFrameReadyCallbackEx *)GetProcAddress(tisgrabber, "IC_SetFrameReadyCallbackEx");
        if (fPtr == nullptr)
        {
            FreeLibrary(tisgrabber);
            Napi::Error::New(env, "Cannot find function IC_SetFrameReadyCallbackEx in tisgrabber_x64.dll").ThrowAsJavaScriptException();
            return env.Undefined();
        };
        auto f = *fPtr;
        int ret = f(hGrabber, frameReadyCb, nullptr);
        if (ret != IC_SUCCESS)
        {
            retObj.Set("code", Napi::Number::New(env, ret));
            retObj.Set("message", Napi::String::New(env, "Cannot set frame ready callback"));
            return retObj;
        }
        auto cbRef = Napi::Persistent(cb);
        cbRef.SuppressDestruct();
        g_frameReadyCb = &cbRef;
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, IC_ERROR));
        retObj.Set("message", Napi::String::New(env, "Frame ready callback already setted"));
    }
    return retObj;
}

Napi::Value f_IC_SetDeviceLostCallback(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    Napi::Function cb = info[1].As<Napi::Function>();
    Napi::Object retObj = Napi::Object::New(env);
    if (g_frameReadyCb == nullptr)
    {
        IC_SetCallbacks *fPtr = (IC_SetCallbacks *)GetProcAddress(tisgrabber, "IC_SetCallbacks");
        if (fPtr == nullptr)
        {
            FreeLibrary(tisgrabber);
            Napi::Error::New(env, "Cannot find function IC_SetCallbacks in tisgrabber_x64.dll").ThrowAsJavaScriptException();
            return env.Undefined();
        };
        auto f = *fPtr;
        int ret = f(hGrabber, nullptr, nullptr, deviceLostCb, nullptr);
        if (ret != IC_SUCCESS)
        {
            retObj.Set("code", Napi::Number::New(env, ret));
            retObj.Set("message", Napi::String::New(env, "Cannot set device lost callback"));
            return retObj;
        }
        auto cbRef = Napi::Persistent(cb);
        cbRef.SuppressDestruct();
        g_deviceLostCb = &cbRef;
        retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    }
    else
    {
        retObj.Set("code", Napi::Number::New(env, IC_ERROR));
        retObj.Set("message", Napi::String::New(env, "Device lose callback already setted"));
    }
    return retObj;
}

Napi::Value f_IC_printItemandElementNames(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    HGRABBER hGrabber = info[0].As<Napi::External<HGRABBER_t>>().Data();
    Napi::Object retObj = Napi::Object::New(env);
    IC_printItemandElementNames *fPtr = (IC_printItemandElementNames *)GetProcAddress(tisgrabber, "IC_printItemandElementNames");
    auto f = *fPtr;
    int ret = f(hGrabber);
    retObj.Set("code", Napi::Number::New(env, IC_SUCCESS));
    return retObj;
}

// generate end

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    tisgrabber = LoadLibrary("tisgrabber_x64.dll");
    if (tisgrabber == nullptr)
    {
        Napi::Error::New(env, "Cannot load tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return exports;
    }
    Napi::Object ic_static = Napi::Object::New(env);
    exports.Set("ic_static", ic_static);
    INIT_STATIC_METHOD(IC_InitLibrary)
    INIT_STATIC_METHOD(IC_CreateGrabber)
    INIT_STATIC_METHOD(IC_TidyUP)
    INIT_STATIC_METHOD(IC_CloseLibrary)
    INIT_STATIC_METHOD(IC_OpenVideoCaptureDevice)
    INIT_STATIC_METHOD(IC_CloseVideoCaptureDevice)
    INIT_STATIC_METHOD(IC_GetDeviceName)
    INIT_STATIC_METHOD(IC_GetVideoFormatWidth)
    INIT_STATIC_METHOD(IC_GetVideoFormatHeight)
    INIT_STATIC_METHOD(IC_SetFormat)
    INIT_STATIC_METHOD(IC_GetFormat)
    INIT_STATIC_METHOD(IC_SetVideoFormat)
    INIT_STATIC_METHOD(IC_SetVideoNorm)
    INIT_STATIC_METHOD(IC_SetInputChannel)
    INIT_STATIC_METHOD(IC_StartLive)
    INIT_STATIC_METHOD(IC_PrepareLive)
    INIT_STATIC_METHOD(IC_SuspendLive)
    INIT_STATIC_METHOD(IC_IsLive)
    INIT_STATIC_METHOD(IC_StopLive)
    INIT_STATIC_METHOD(IC_IsCameraPropertyAvailable)
    INIT_STATIC_METHOD(IC_SetCameraProperty)
    INIT_STATIC_METHOD(IC_CameraPropertyGetRange)
    INIT_STATIC_METHOD(IC_GetCameraProperty)
    INIT_STATIC_METHOD(IC_EnableAutoCameraProperty)
    INIT_STATIC_METHOD(IC_IsCameraPropertyAutoAvailable)
    INIT_STATIC_METHOD(IC_GetAutoCameraProperty)
    INIT_STATIC_METHOD(IC_IsVideoPropertyAvailable)
    INIT_STATIC_METHOD(IC_VideoPropertyGetRange)
    INIT_STATIC_METHOD(IC_GetVideoProperty)
    INIT_STATIC_METHOD(IC_IsVideoPropertyAutoAvailable)
    INIT_STATIC_METHOD(IC_GetAutoVideoProperty)
    INIT_STATIC_METHOD(IC_SetVideoProperty)
    INIT_STATIC_METHOD(IC_EnableAutoVideoProperty)
    INIT_STATIC_METHOD(IC_GetImageDescription)
    INIT_STATIC_METHOD(IC_SnapImage)
    INIT_STATIC_METHOD(IC_SaveImage)
    INIT_STATIC_METHOD(IC_SetHWnd)
    INIT_STATIC_METHOD(IC_GetSerialNumber)
    // INIT_STATIC_METHOD(IC_ListVideoFormats)
    INIT_STATIC_METHOD(IC_GetDeviceCount)
    INIT_STATIC_METHOD(IC_GetDevice)
    INIT_STATIC_METHOD(IC_GetUniqueNamefromList)
    INIT_STATIC_METHOD(IC_GetInputChannelCount)
    INIT_STATIC_METHOD(IC_GetInputChannel)
    INIT_STATIC_METHOD(IC_GetVideoNormCount)
    INIT_STATIC_METHOD(IC_GetVideoNorm)
    INIT_STATIC_METHOD(IC_GetVideoFormatCount)
    INIT_STATIC_METHOD(IC_GetVideoFormat)
    INIT_STATIC_METHOD(IC_SaveDeviceStateToFile)
    INIT_STATIC_METHOD(IC_LoadDeviceStateFromFileEx)
    INIT_STATIC_METHOD(IC_SaveDeviceSettings)
    INIT_STATIC_METHOD(IC_OpenDeviceBySettings)
    INIT_STATIC_METHOD(IC_LoadDeviceSettings)
    INIT_STATIC_METHOD(IC_OpenDevByDisplayName)
    INIT_STATIC_METHOD(IC_GetDisplayName)
    INIT_STATIC_METHOD(IC_OpenDevByUniqueName)
    INIT_STATIC_METHOD(IC_IsDevValid)
    INIT_STATIC_METHOD(IC_ShowPropertyDialog)
    INIT_STATIC_METHOD(IC_ShowDeviceSelectionDialog)
    INIT_STATIC_METHOD(IC_IsTriggerAvailable)
    INIT_STATIC_METHOD(IC_EnableTrigger)
    INIT_STATIC_METHOD(IC_MsgBox)
    INIT_STATIC_METHOD(IC_SetContinuousMode)
    INIT_STATIC_METHOD(IC_SetFrameRate)
    INIT_STATIC_METHOD(IC_GetFrameRate)
    INIT_STATIC_METHOD(IC_GetAvailableFrameRates)
    INIT_STATIC_METHOD(IC_SetDefaultWindowPosition)
    INIT_STATIC_METHOD(IC_SetWindowPosition)
    INIT_STATIC_METHOD(IC_GetWindowPosition)
    INIT_STATIC_METHOD(IC_SetWhiteBalanceAuto)
    INIT_STATIC_METHOD(IC_SignalDetected)
    INIT_STATIC_METHOD(IC_GetTriggerModes)
    INIT_STATIC_METHOD(IC_SetTriggerMode)
    INIT_STATIC_METHOD(IC_SetTriggerPolarity)
    INIT_STATIC_METHOD(IC_GetExpRegValRange)
    INIT_STATIC_METHOD(IC_GetExpRegVal)
    INIT_STATIC_METHOD(IC_SetExpRegVal)
    INIT_STATIC_METHOD(IC_EnableExpRegValAuto)
    INIT_STATIC_METHOD(IC_GetExpRegValAuto)
    INIT_STATIC_METHOD(IC_IsExpAbsValAvailable)
    INIT_STATIC_METHOD(IC_GetExpAbsValRange)
    INIT_STATIC_METHOD(IC_GetExpAbsVal)
    INIT_STATIC_METHOD(IC_SetExpAbsVal)
    INIT_STATIC_METHOD(IC_GetColorEnhancement)
    INIT_STATIC_METHOD(IC_SetColorEnhancement)
    INIT_STATIC_METHOD(IC_SoftwareTrigger)
    INIT_STATIC_METHOD(IC_SetWhiteBalanceRed)
    INIT_STATIC_METHOD(IC_SetWhiteBalanceGreen)
    INIT_STATIC_METHOD(IC_SetWhiteBalanceBlue)
    INIT_STATIC_METHOD(IC_FocusOnePush)
    INIT_STATIC_METHOD(IC_IsPropertyAvailable)
    INIT_STATIC_METHOD(IC_GetPropertyValueRange)
    INIT_STATIC_METHOD(IC_GetPropertyValue)
    INIT_STATIC_METHOD(IC_SetPropertyValue)
    INIT_STATIC_METHOD(IC_GetPropertyAbsoluteValueRange)
    INIT_STATIC_METHOD(IC_GetPropertyAbsoluteValue)
    INIT_STATIC_METHOD(IC_SetPropertyAbsoluteValue)
    INIT_STATIC_METHOD(IC_GetPropertySwitch)
    INIT_STATIC_METHOD(IC_SetPropertySwitch)
    INIT_STATIC_METHOD(IC_PropertyOnePush)
    INIT_STATIC_METHOD(IC_GetPropertyMapString)
    INIT_STATIC_METHOD(IC_SetPropertyMapString)
    INIT_STATIC_METHOD(IC_ResetProperties)
    INIT_STATIC_METHOD(IC_SetRingBufferSize)
    INIT_STATIC_METHOD(IC_GetRingBufferSize)
    INIT_STATIC_METHOD(IC_GetMemBufferDescription)
    INIT_STATIC_METHOD(IC_MemBufferLock)
    INIT_STATIC_METHOD(IC_MemBufferisLocked)
    INIT_STATIC_METHOD(IC_MemBufferGetIndex)
    INIT_STATIC_METHOD(IC_MemBufferGetData)
    INIT_STATIC_METHOD(IC_SetFrameReadyCallbackEx)
    INIT_STATIC_METHOD(IC_SetDeviceLostCallback)
    INIT_STATIC_METHOD(IC_GetUniqueName)
    INIT_STATIC_METHOD(IC_enumProperties)
    INIT_STATIC_METHOD(IC_enumPropertyElements)
    INIT_STATIC_METHOD(IC_printItemandElementNames)

    return exports;
}

NODE_API_MODULE(ic_node, Init)

#else
#endif