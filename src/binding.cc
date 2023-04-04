// #define _WIN32
#ifdef _WIN32

#include <unordered_map>
#include <napi.h>
#include <Windows.h>
#include <functional>
#include "./binding.h"

#define INIT_STATIC_METHOD(method) \
    ic_static.Set(#method, Napi::Function::New<f_##method>(env));

static HMODULE tisgrabber;
static std::unordered_map<HGRABBER, std::vector<Napi::FunctionReference>> grabber_device_lost_callbacks{};

// generate start
Napi::Value f_IC_InitLibrary(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    char *szLicenseKey = (char *)info[0].As<Napi::String>().Utf8Value().c_str();
    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_InitLibrary *f_ptr = (IC_InitLibrary *)GetProcAddress(tisgrabber, "IC_InitLibrary");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_InitLibrary in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(szLicenseKey);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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

    IC_CreateGrabber *f_ptr = (IC_CreateGrabber *)GetProcAddress(tisgrabber, "IC_CreateGrabber");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_CreateGrabber in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    HGRABBER ret = f();
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::External<HGRABBER>::New(env, &ret));
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

    IC_TidyUP *f_ptr = (IC_TidyUP *)GetProcAddress(tisgrabber, "IC_TidyUP");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_TidyUP in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f();
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
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

    IC_CloseLibrary *f_ptr = (IC_CloseLibrary *)GetProcAddress(tisgrabber, "IC_CloseLibrary");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_CloseLibrary in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f();
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szDeviceName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_OpenVideoCaptureDevice *f_ptr = (IC_OpenVideoCaptureDevice *)GetProcAddress(tisgrabber, "IC_OpenVideoCaptureDevice");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_OpenVideoCaptureDevice in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szDeviceName);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_CloseVideoCaptureDevice *f_ptr = (IC_CloseVideoCaptureDevice *)GetProcAddress(tisgrabber, "IC_CloseVideoCaptureDevice");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_CloseVideoCaptureDevice in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_GetDeviceName *f_ptr = (IC_GetDeviceName *)GetProcAddress(tisgrabber, "IC_GetDeviceName");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetDeviceName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    char *ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::String::New(env, ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_GetVideoFormatWidth *f_ptr = (IC_GetVideoFormatWidth *)GetProcAddress(tisgrabber, "IC_GetVideoFormatWidth");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoFormatWidth in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_GetVideoFormatHeight *f_ptr = (IC_GetVideoFormatHeight *)GetProcAddress(tisgrabber, "IC_GetVideoFormatHeight");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoFormatHeight in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    COLORFORMAT format = (COLORFORMAT)info[1].As<Napi::Number>().Int32Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetFormat *f_ptr = (IC_SetFormat *)GetProcAddress(tisgrabber, "IC_SetFormat");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetFormat in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, format);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_GetFormat *f_ptr = (IC_GetFormat *)GetProcAddress(tisgrabber, "IC_GetFormat");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetFormat in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    COLORFORMAT ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFormat = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetVideoFormat *f_ptr = (IC_SetVideoFormat *)GetProcAddress(tisgrabber, "IC_SetVideoFormat");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetVideoFormat in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szFormat);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szNorm = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetVideoNorm *f_ptr = (IC_SetVideoNorm *)GetProcAddress(tisgrabber, "IC_SetVideoNorm");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetVideoNorm in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szNorm);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szChannel = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetInputChannel *f_ptr = (IC_SetInputChannel *)GetProcAddress(tisgrabber, "IC_SetInputChannel");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetInputChannel in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szChannel);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iShow = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_StartLive *f_ptr = (IC_StartLive *)GetProcAddress(tisgrabber, "IC_StartLive");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_StartLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iShow);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iShow = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_PrepareLive *f_ptr = (IC_PrepareLive *)GetProcAddress(tisgrabber, "IC_PrepareLive");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_PrepareLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iShow);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_SuspendLive *f_ptr = (IC_SuspendLive *)GetProcAddress(tisgrabber, "IC_SuspendLive");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SuspendLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_IsLive *f_ptr = (IC_IsLive *)GetProcAddress(tisgrabber, "IC_IsLive");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_StopLive *f_ptr = (IC_StopLive *)GetProcAddress(tisgrabber, "IC_StopLive");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_StopLive in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    CAMERA_PROPERTY eProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_IsCameraPropertyAvailable *f_ptr = (IC_IsCameraPropertyAvailable *)GetProcAddress(tisgrabber, "IC_IsCameraPropertyAvailable");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsCameraPropertyAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, eProperty);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    CAMERA_PROPERTY eProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long lValue = (long)info[2].As<Napi::Number>().Int64Value();
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
    IC_SetCameraProperty *f_ptr = (IC_SetCameraProperty *)GetProcAddress(tisgrabber, "IC_SetCameraProperty");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetCameraProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, eProperty, lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    CAMERA_PROPERTY eProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long *lMin;
    long *lMax;
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_CameraPropertyGetRange *f_ptr = (IC_CameraPropertyGetRange *)GetProcAddress(tisgrabber, "IC_CameraPropertyGetRange");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_CameraPropertyGetRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, eProperty, lMin, lMax);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("lMin", Napi::Number::New(env, *lMin));
    outArgs.Set("lMax", Napi::Number::New(env, *lMax));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    CAMERA_PROPERTY eProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long *lValue;
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetCameraProperty *f_ptr = (IC_GetCameraProperty *)GetProcAddress(tisgrabber, "IC_GetCameraProperty");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetCameraProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, eProperty, lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("lValue", Napi::Number::New(env, *lValue));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iProperty = (int)info[1].As<Napi::Number>().Int64Value();
    int iOnOff = (int)info[2].As<Napi::Number>().Int64Value();
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
    IC_EnableAutoCameraProperty *f_ptr = (IC_EnableAutoCameraProperty *)GetProcAddress(tisgrabber, "IC_EnableAutoCameraProperty");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EnableAutoCameraProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iProperty, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    CAMERA_PROPERTY iProperty = (CAMERA_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_IsCameraPropertyAutoAvailable *f_ptr = (IC_IsCameraPropertyAutoAvailable *)GetProcAddress(tisgrabber, "IC_IsCameraPropertyAutoAvailable");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsCameraPropertyAutoAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iProperty);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iProperty = (int)info[1].As<Napi::Number>().Int64Value();
    int *iOnOff;
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetAutoCameraProperty *f_ptr = (IC_GetAutoCameraProperty *)GetProcAddress(tisgrabber, "IC_GetAutoCameraProperty");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetAutoCameraProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iProperty, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("iOnOff", Napi::Number::New(env, *iOnOff));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_IsVideoPropertyAvailable *f_ptr = (IC_IsVideoPropertyAvailable *)GetProcAddress(tisgrabber, "IC_IsVideoPropertyAvailable");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsVideoPropertyAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, eProperty);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long *lMin;
    long *lMax;
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_VideoPropertyGetRange *f_ptr = (IC_VideoPropertyGetRange *)GetProcAddress(tisgrabber, "IC_VideoPropertyGetRange");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_VideoPropertyGetRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, eProperty, lMin, lMax);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("lMin", Napi::Number::New(env, *lMin));
    outArgs.Set("lMax", Napi::Number::New(env, *lMax));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long *lValue;
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetVideoProperty *f_ptr = (IC_GetVideoProperty *)GetProcAddress(tisgrabber, "IC_GetVideoProperty");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, eProperty, lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("lValue", Napi::Number::New(env, *lValue));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_IsVideoPropertyAutoAvailable *f_ptr = (IC_IsVideoPropertyAutoAvailable *)GetProcAddress(tisgrabber, "IC_IsVideoPropertyAutoAvailable");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsVideoPropertyAutoAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, eProperty);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iProperty = (int)info[1].As<Napi::Number>().Int64Value();
    int *iOnOff;
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetAutoVideoProperty *f_ptr = (IC_GetAutoVideoProperty *)GetProcAddress(tisgrabber, "IC_GetAutoVideoProperty");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetAutoVideoProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iProperty, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("iOnOff", Napi::Number::New(env, *iOnOff));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    VIDEO_PROPERTY eProperty = (VIDEO_PROPERTY)info[1].As<Napi::Number>().Int32Value();
    long lValue = (long)info[2].As<Napi::Number>().Int64Value();
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
    IC_SetVideoProperty *f_ptr = (IC_SetVideoProperty *)GetProcAddress(tisgrabber, "IC_SetVideoProperty");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetVideoProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, eProperty, lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iProperty = (int)info[1].As<Napi::Number>().Int64Value();
    int iOnOff = (int)info[2].As<Napi::Number>().Int64Value();
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
    IC_EnableAutoVideoProperty *f_ptr = (IC_EnableAutoVideoProperty *)GetProcAddress(tisgrabber, "IC_EnableAutoVideoProperty");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EnableAutoVideoProperty in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iProperty, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    long *lWidth;
    long *lHeight;
    int *iBitsPerPixel;
    COLORFORMAT *format;

    IC_GetImageDescription *f_ptr = (IC_GetImageDescription *)GetProcAddress(tisgrabber, "IC_GetImageDescription");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetImageDescription in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, lWidth, lHeight, iBitsPerPixel, format);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("lWidth", Napi::Number::New(env, *lWidth));
    outArgs.Set("lHeight", Napi::Number::New(env, *lHeight));
    outArgs.Set("iBitsPerPixel", Napi::Number::New(env, *iBitsPerPixel));
    outArgs.Set("format", Napi::Number::New(env, *format));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iTimeOutMillisek = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SnapImage *f_ptr = (IC_SnapImage *)GetProcAddress(tisgrabber, "IC_SnapImage");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SnapImage in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iTimeOutMillisek);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFileName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    IMG_FILETYPE ft = (IMG_FILETYPE)info[2].As<Napi::Number>().Int32Value();
    long quality = (long)info[3].As<Napi::Number>().Int64Value();
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
    IC_SaveImage *f_ptr = (IC_SaveImage *)GetProcAddress(tisgrabber, "IC_SaveImage");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SaveImage in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szFileName, ft, quality);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    __HWND hWnd = *info[1].As<Napi::External<__HWND>>().Data();

    IC_SetHWnd *f_ptr = (IC_SetHWnd *)GetProcAddress(tisgrabber, "IC_SetHWnd");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetHWnd in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, hWnd);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_GetSerialNumber(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szSerial = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetSerialNumber *f_ptr = (IC_GetSerialNumber *)GetProcAddress(tisgrabber, "IC_GetSerialNumber");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetSerialNumber in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(hGrabber, szSerial);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
    return retObj;
}
Napi::Value f_IC_ListDevices(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    char *szDeviceList = (char *)info[0].As<Napi::String>().Utf8Value().c_str();
    int iSize = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_ListDevices *f_ptr = (IC_ListDevices *)GetProcAddress(tisgrabber, "IC_ListDevices");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ListDevices in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(szDeviceList, iSize);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_ListDevicesbyIndex(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    char *szDeviceName = (char *)info[0].As<Napi::String>().Utf8Value().c_str();
    int iSize = (int)info[1].As<Napi::Number>().Int64Value();
    int DeviceIndex = (int)info[2].As<Napi::Number>().Int64Value();
    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
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
    IC_ListDevicesbyIndex *f_ptr = (IC_ListDevicesbyIndex *)GetProcAddress(tisgrabber, "IC_ListDevicesbyIndex");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ListDevicesbyIndex in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(szDeviceName, iSize, DeviceIndex);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_ListVideoFormats(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFormatList = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    int iSize = (int)info[2].As<Napi::Number>().Int64Value();
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
    IC_ListVideoFormats *f_ptr = (IC_ListVideoFormats *)GetProcAddress(tisgrabber, "IC_ListVideoFormats");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ListVideoFormats in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szFormatList, iSize);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_ListVideoFormatbyIndex(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 4)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFormatName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    int iSize = (int)info[2].As<Napi::Number>().Int64Value();
    int iIndex = (int)info[3].As<Napi::Number>().Int64Value();
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
    IC_ListVideoFormatbyIndex *f_ptr = (IC_ListVideoFormatbyIndex *)GetProcAddress(tisgrabber, "IC_ListVideoFormatbyIndex");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ListVideoFormatbyIndex in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szFormatName, iSize, iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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

    IC_GetDeviceCount *f_ptr = (IC_GetDeviceCount *)GetProcAddress(tisgrabber, "IC_GetDeviceCount");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetDeviceCount in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f();
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    int iIndex = (int)info[0].As<Napi::Number>().Int64Value();
    if (!info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetDevice *f_ptr = (IC_GetDevice *)GetProcAddress(tisgrabber, "IC_GetDevice");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetDevice in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    char *ret = f(iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::String::New(env, ret));
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
    int iIndex = (int)info[0].As<Napi::Number>().Int64Value();
    if (!info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetUniqueNamefromList *f_ptr = (IC_GetUniqueNamefromList *)GetProcAddress(tisgrabber, "IC_GetUniqueNamefromList");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetUniqueNamefromList in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    char *ret = f(iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::String::New(env, ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_GetInputChannelCount *f_ptr = (IC_GetInputChannelCount *)GetProcAddress(tisgrabber, "IC_GetInputChannelCount");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetInputChannelCount in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iIndex = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetInputChannel *f_ptr = (IC_GetInputChannel *)GetProcAddress(tisgrabber, "IC_GetInputChannel");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetInputChannel in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    char *ret = f(hGrabber, iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::String::New(env, ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_GetVideoNormCount *f_ptr = (IC_GetVideoNormCount *)GetProcAddress(tisgrabber, "IC_GetVideoNormCount");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoNormCount in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iIndex = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetVideoNorm *f_ptr = (IC_GetVideoNorm *)GetProcAddress(tisgrabber, "IC_GetVideoNorm");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoNorm in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    char *ret = f(hGrabber, iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::String::New(env, ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_GetVideoFormatCount *f_ptr = (IC_GetVideoFormatCount *)GetProcAddress(tisgrabber, "IC_GetVideoFormatCount");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoFormatCount in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iIndex = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetVideoFormat *f_ptr = (IC_GetVideoFormat *)GetProcAddress(tisgrabber, "IC_GetVideoFormat");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetVideoFormat in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    char *ret = f(hGrabber, iIndex);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::String::New(env, ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFileName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SaveDeviceStateToFile *f_ptr = (IC_SaveDeviceStateToFile *)GetProcAddress(tisgrabber, "IC_SaveDeviceStateToFile");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SaveDeviceStateToFile in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szFileName);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_LoadDeviceStateFromFile(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFileName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_LoadDeviceStateFromFile *f_ptr = (IC_LoadDeviceStateFromFile *)GetProcAddress(tisgrabber, "IC_LoadDeviceStateFromFile");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_LoadDeviceStateFromFile in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    HGRABBER ret = f(hGrabber, szFileName);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::External<HGRABBER>::New(env, &ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFileName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    int OpenDevice = (int)info[2].As<Napi::Number>().Int64Value();
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
    IC_LoadDeviceStateFromFileEx *f_ptr = (IC_LoadDeviceStateFromFileEx *)GetProcAddress(tisgrabber, "IC_LoadDeviceStateFromFileEx");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_LoadDeviceStateFromFileEx in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szFileName, OpenDevice);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFilename = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SaveDeviceSettings *f_ptr = (IC_SaveDeviceSettings *)GetProcAddress(tisgrabber, "IC_SaveDeviceSettings");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SaveDeviceSettings in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szFilename);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFilename = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_OpenDeviceBySettings *f_ptr = (IC_OpenDeviceBySettings *)GetProcAddress(tisgrabber, "IC_OpenDeviceBySettings");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_OpenDeviceBySettings in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szFilename);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szFilename = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_LoadDeviceSettings *f_ptr = (IC_LoadDeviceSettings *)GetProcAddress(tisgrabber, "IC_LoadDeviceSettings");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_LoadDeviceSettings in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szFilename);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szDisplayname = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_OpenDevByDisplayName *f_ptr = (IC_OpenDevByDisplayName *)GetProcAddress(tisgrabber, "IC_OpenDevByDisplayName");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_OpenDevByDisplayName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szDisplayname);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_GetDisplayName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szDisplayname = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    int iLen = (int)info[2].As<Napi::Number>().Int64Value();
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
    IC_GetDisplayName *f_ptr = (IC_GetDisplayName *)GetProcAddress(tisgrabber, "IC_GetDisplayName");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetDisplayName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szDisplayname, iLen);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szDisplayname = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_OpenDevByUniqueName *f_ptr = (IC_OpenDevByUniqueName *)GetProcAddress(tisgrabber, "IC_OpenDevByUniqueName");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_OpenDevByUniqueName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szDisplayname);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_IsDevValid *f_ptr = (IC_IsDevValid *)GetProcAddress(tisgrabber, "IC_IsDevValid");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsDevValid in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_ShowPropertyDialog *f_ptr = (IC_ShowPropertyDialog *)GetProcAddress(tisgrabber, "IC_ShowPropertyDialog");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ShowPropertyDialog in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_ShowDeviceSelectionDialog *f_ptr = (IC_ShowDeviceSelectionDialog *)GetProcAddress(tisgrabber, "IC_ShowDeviceSelectionDialog");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ShowDeviceSelectionDialog in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    HGRABBER ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::External<HGRABBER>::New(env, &ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_IsTriggerAvailable *f_ptr = (IC_IsTriggerAvailable *)GetProcAddress(tisgrabber, "IC_IsTriggerAvailable");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsTriggerAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iEnable = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_EnableTrigger *f_ptr = (IC_EnableTrigger *)GetProcAddress(tisgrabber, "IC_EnableTrigger");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EnableTrigger in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iEnable);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_RemoveOverlay(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iEnable = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_RemoveOverlay *f_ptr = (IC_RemoveOverlay *)GetProcAddress(tisgrabber, "IC_RemoveOverlay");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_RemoveOverlay in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(hGrabber, iEnable);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
    return retObj;
}
Napi::Value f_IC_EnableOverlay(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iEnable = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_EnableOverlay *f_ptr = (IC_EnableOverlay *)GetProcAddress(tisgrabber, "IC_EnableOverlay");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EnableOverlay in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(hGrabber, iEnable);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
    return retObj;
}
Napi::Value f_IC_BeginPaint(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_BeginPaint *f_ptr = (IC_BeginPaint *)GetProcAddress(tisgrabber, "IC_BeginPaint");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_BeginPaint in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    long ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_EndPaint(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_EndPaint *f_ptr = (IC_EndPaint *)GetProcAddress(tisgrabber, "IC_EndPaint");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EndPaint in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
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
    char *szText = (char *)info[0].As<Napi::String>().Utf8Value().c_str();
    char *szTitle = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
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
    IC_MsgBox *f_ptr = (IC_MsgBox *)GetProcAddress(tisgrabber, "IC_MsgBox");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_MsgBox in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(szText, szTitle);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int cont = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetContinuousMode *f_ptr = (IC_SetContinuousMode *)GetProcAddress(tisgrabber, "IC_SetContinuousMode");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetContinuousMode in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, cont);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    float FrameRate = (float)info[1].As<Napi::Number>().DoubleValue();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetFrameRate *f_ptr = (IC_SetFrameRate *)GetProcAddress(tisgrabber, "IC_SetFrameRate");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetFrameRate in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, FrameRate);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_GetFrameRate *f_ptr = (IC_GetFrameRate *)GetProcAddress(tisgrabber, "IC_GetFrameRate");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetFrameRate in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    float ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_GetAvailableFrameRates(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int Index = (int)info[1].As<Napi::Number>().Int64Value();
    float *fps;
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetAvailableFrameRates *f_ptr = (IC_GetAvailableFrameRates *)GetProcAddress(tisgrabber, "IC_GetAvailableFrameRates");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetAvailableFrameRates in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Index, fps);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("fps", Napi::Number::New(env, *fps));
    retObj.Set("outArgs", outArgs);
    return retObj;
}
Napi::Value f_IC_ShowInternalPropertyPage(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_ShowInternalPropertyPage *f_ptr = (IC_ShowInternalPropertyPage *)GetProcAddress(tisgrabber, "IC_ShowInternalPropertyPage");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ShowInternalPropertyPage in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_ResetUSBCam(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_ResetUSBCam *f_ptr = (IC_ResetUSBCam *)GetProcAddress(tisgrabber, "IC_ResetUSBCam");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ResetUSBCam in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_QueryPropertySet(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_QueryPropertySet *f_ptr = (IC_QueryPropertySet *)GetProcAddress(tisgrabber, "IC_QueryPropertySet");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_QueryPropertySet in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int Default = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetDefaultWindowPosition *f_ptr = (IC_SetDefaultWindowPosition *)GetProcAddress(tisgrabber, "IC_SetDefaultWindowPosition");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetDefaultWindowPosition in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Default);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int PosX = (int)info[1].As<Napi::Number>().Int64Value();
    int PosY = (int)info[2].As<Napi::Number>().Int64Value();
    int Width = (int)info[3].As<Napi::Number>().Int64Value();
    int Height = (int)info[4].As<Napi::Number>().Int64Value();
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
    IC_SetWindowPosition *f_ptr = (IC_SetWindowPosition *)GetProcAddress(tisgrabber, "IC_SetWindowPosition");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWindowPosition in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, PosX, PosY, Width, Height);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int *PosX;
    int *PosY;
    int *Width;
    int *Height;

    IC_GetWindowPosition *f_ptr = (IC_GetWindowPosition *)GetProcAddress(tisgrabber, "IC_GetWindowPosition");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetWindowPosition in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, PosX, PosY, Width, Height);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("PosX", Napi::Number::New(env, *PosX));
    outArgs.Set("PosY", Napi::Number::New(env, *PosY));
    outArgs.Set("Width", Napi::Number::New(env, *Width));
    outArgs.Set("Height", Napi::Number::New(env, *Height));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iOnOff = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetWhiteBalanceAuto *f_ptr = (IC_SetWhiteBalanceAuto *)GetProcAddress(tisgrabber, "IC_SetWhiteBalanceAuto");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWhiteBalanceAuto in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_SignalDetected *f_ptr = (IC_SignalDetected *)GetProcAddress(tisgrabber, "IC_SignalDetected");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SignalDetected in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_GetTriggerModes(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szModeList = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    int iSize = (int)info[2].As<Napi::Number>().Int64Value();
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
    IC_GetTriggerModes *f_ptr = (IC_GetTriggerModes *)GetProcAddress(tisgrabber, "IC_GetTriggerModes");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetTriggerModes in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szModeList, iSize);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *szMode = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetTriggerMode *f_ptr = (IC_SetTriggerMode *)GetProcAddress(tisgrabber, "IC_SetTriggerMode");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetTriggerMode in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, szMode);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iPolarity = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetTriggerPolarity *f_ptr = (IC_SetTriggerPolarity *)GetProcAddress(tisgrabber, "IC_SetTriggerPolarity");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetTriggerPolarity in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iPolarity);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    long *lMin;
    long *lMax;

    IC_GetExpRegValRange *f_ptr = (IC_GetExpRegValRange *)GetProcAddress(tisgrabber, "IC_GetExpRegValRange");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpRegValRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, lMin, lMax);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("lMin", Napi::Number::New(env, *lMin));
    outArgs.Set("lMax", Napi::Number::New(env, *lMax));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    long *lValue;

    IC_GetExpRegVal *f_ptr = (IC_GetExpRegVal *)GetProcAddress(tisgrabber, "IC_GetExpRegVal");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpRegVal in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("lValue", Napi::Number::New(env, *lValue));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    long lValue = (long)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetExpRegVal *f_ptr = (IC_SetExpRegVal *)GetProcAddress(tisgrabber, "IC_SetExpRegVal");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetExpRegVal in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, lValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int iOnOff = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_EnableExpRegValAuto *f_ptr = (IC_EnableExpRegValAuto *)GetProcAddress(tisgrabber, "IC_EnableExpRegValAuto");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_EnableExpRegValAuto in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int *iOnOff;

    IC_GetExpRegValAuto *f_ptr = (IC_GetExpRegValAuto *)GetProcAddress(tisgrabber, "IC_GetExpRegValAuto");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpRegValAuto in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, iOnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("iOnOff", Napi::Number::New(env, *iOnOff));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_IsExpAbsValAvailable *f_ptr = (IC_IsExpAbsValAvailable *)GetProcAddress(tisgrabber, "IC_IsExpAbsValAvailable");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsExpAbsValAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    float *fMin;
    float *fMax;

    IC_GetExpAbsValRange *f_ptr = (IC_GetExpAbsValRange *)GetProcAddress(tisgrabber, "IC_GetExpAbsValRange");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpAbsValRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, fMin, fMax);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("fMin", Napi::Number::New(env, *fMin));
    outArgs.Set("fMax", Napi::Number::New(env, *fMax));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    float *fValue;

    IC_GetExpAbsVal *f_ptr = (IC_GetExpAbsVal *)GetProcAddress(tisgrabber, "IC_GetExpAbsVal");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetExpAbsVal in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, fValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("fValue", Napi::Number::New(env, *fValue));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    float fValue = (float)info[1].As<Napi::Number>().DoubleValue();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetExpAbsVal *f_ptr = (IC_SetExpAbsVal *)GetProcAddress(tisgrabber, "IC_SetExpAbsVal");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetExpAbsVal in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, fValue);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int *OnOff;

    IC_GetColorEnhancement *f_ptr = (IC_GetColorEnhancement *)GetProcAddress(tisgrabber, "IC_GetColorEnhancement");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetColorEnhancement in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, OnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("OnOff", Napi::Number::New(env, *OnOff));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int OnOff = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetColorEnhancement *f_ptr = (IC_SetColorEnhancement *)GetProcAddress(tisgrabber, "IC_SetColorEnhancement");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetColorEnhancement in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, OnOff);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_SoftwareTrigger *f_ptr = (IC_SoftwareTrigger *)GetProcAddress(tisgrabber, "IC_SoftwareTrigger");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SoftwareTrigger in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    long Value = (long)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetWhiteBalanceRed *f_ptr = (IC_SetWhiteBalanceRed *)GetProcAddress(tisgrabber, "IC_SetWhiteBalanceRed");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWhiteBalanceRed in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    long Value = (long)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetWhiteBalanceGreen *f_ptr = (IC_SetWhiteBalanceGreen *)GetProcAddress(tisgrabber, "IC_SetWhiteBalanceGreen");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWhiteBalanceGreen in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    long Value = (long)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetWhiteBalanceBlue *f_ptr = (IC_SetWhiteBalanceBlue *)GetProcAddress(tisgrabber, "IC_SetWhiteBalanceBlue");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetWhiteBalanceBlue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_FocusOnePush *f_ptr = (IC_FocusOnePush *)GetProcAddress(tisgrabber, "IC_FocusOnePush");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_FocusOnePush in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_printItemandElementNames *f_ptr = (IC_printItemandElementNames *)GetProcAddress(tisgrabber, "IC_printItemandElementNames");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_printItemandElementNames in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
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
    IC_IsPropertyAvailable *f_ptr = (IC_IsPropertyAvailable *)GetProcAddress(tisgrabber, "IC_IsPropertyAvailable");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_IsPropertyAvailable in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    int *Min;
    int *Max;
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
    IC_GetPropertyValueRange *f_ptr = (IC_GetPropertyValueRange *)GetProcAddress(tisgrabber, "IC_GetPropertyValueRange");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyValueRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, Min, Max);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("Min", Napi::Number::New(env, *Min));
    outArgs.Set("Max", Napi::Number::New(env, *Max));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    int *Value;
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
    IC_GetPropertyValue *f_ptr = (IC_GetPropertyValue *)GetProcAddress(tisgrabber, "IC_GetPropertyValue");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyValue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("Value", Napi::Number::New(env, *Value));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    int Value = (int)info[3].As<Napi::Number>().Int64Value();
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
    IC_SetPropertyValue *f_ptr = (IC_SetPropertyValue *)GetProcAddress(tisgrabber, "IC_SetPropertyValue");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetPropertyValue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    float *Min;
    float *Max;
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
    IC_GetPropertyAbsoluteValueRange *f_ptr = (IC_GetPropertyAbsoluteValueRange *)GetProcAddress(tisgrabber, "IC_GetPropertyAbsoluteValueRange");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyAbsoluteValueRange in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, Min, Max);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("Min", Napi::Number::New(env, *Min));
    outArgs.Set("Max", Napi::Number::New(env, *Max));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    float *Value;
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
    IC_GetPropertyAbsoluteValue *f_ptr = (IC_GetPropertyAbsoluteValue *)GetProcAddress(tisgrabber, "IC_GetPropertyAbsoluteValue");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyAbsoluteValue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("Value", Napi::Number::New(env, *Value));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    float Value = (float)info[3].As<Napi::Number>().DoubleValue();
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
    IC_SetPropertyAbsoluteValue *f_ptr = (IC_SetPropertyAbsoluteValue *)GetProcAddress(tisgrabber, "IC_SetPropertyAbsoluteValue");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetPropertyAbsoluteValue in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, Value);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    int *On;
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
    IC_GetPropertySwitch *f_ptr = (IC_GetPropertySwitch *)GetProcAddress(tisgrabber, "IC_GetPropertySwitch");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertySwitch in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, On);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("On", Napi::Number::New(env, *On));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    int On = (int)info[3].As<Napi::Number>().Int64Value();
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
    IC_SetPropertySwitch *f_ptr = (IC_SetPropertySwitch *)GetProcAddress(tisgrabber, "IC_SetPropertySwitch");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetPropertySwitch in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, On);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
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
    IC_PropertyOnePush *f_ptr = (IC_PropertyOnePush *)GetProcAddress(tisgrabber, "IC_PropertyOnePush");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_PropertyOnePush in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    int *StringLength;
    char *String = (char *)info[4].As<Napi::String>().Utf8Value().c_str();
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
    if (!info[4].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 4").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_GetPropertyMapString *f_ptr = (IC_GetPropertyMapString *)GetProcAddress(tisgrabber, "IC_GetPropertyMapString");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetPropertyMapString in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, StringLength, String);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("StringLength", Napi::Number::New(env, *StringLength));
    retObj.Set("outArgs", outArgs);
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *Property = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Element = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    char *String = (char *)info[3].As<Napi::String>().Utf8Value().c_str();
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
    IC_SetPropertyMapString *f_ptr = (IC_SetPropertyMapString *)GetProcAddress(tisgrabber, "IC_SetPropertyMapString");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetPropertyMapString in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Property, Element, String);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_ResetProperties *f_ptr = (IC_ResetProperties *)GetProcAddress(tisgrabber, "IC_ResetProperties");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_ResetProperties in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_GetAvailableFrameFilterCount(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 0)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    IC_GetAvailableFrameFilterCount *f_ptr = (IC_GetAvailableFrameFilterCount *)GetProcAddress(tisgrabber, "IC_GetAvailableFrameFilterCount");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetAvailableFrameFilterCount in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f();
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_AddFrameFilterToDevice(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    HFRAMEFILTER FilterHandle = *info[1].As<Napi::External<HFRAMEFILTER>>().Data();

    IC_AddFrameFilterToDevice *f_ptr = (IC_AddFrameFilterToDevice *)GetProcAddress(tisgrabber, "IC_AddFrameFilterToDevice");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_AddFrameFilterToDevice in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, FilterHandle);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_RemoveFrameFilterFromDevice(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    HFRAMEFILTER FilterHandle = *info[1].As<Napi::External<HFRAMEFILTER>>().Data();

    IC_RemoveFrameFilterFromDevice *f_ptr = (IC_RemoveFrameFilterFromDevice *)GetProcAddress(tisgrabber, "IC_RemoveFrameFilterFromDevice");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_RemoveFrameFilterFromDevice in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(hGrabber, FilterHandle);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
    return retObj;
}
Napi::Value f_IC_DeleteFrameFilter(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HFRAMEFILTER FilterHandle = *info[0].As<Napi::External<HFRAMEFILTER>>().Data();

    IC_DeleteFrameFilter *f_ptr = (IC_DeleteFrameFilter *)GetProcAddress(tisgrabber, "IC_DeleteFrameFilter");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_DeleteFrameFilter in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(FilterHandle);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
    return retObj;
}
Napi::Value f_IC_FrameFilterShowDialog(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HFRAMEFILTER FilterHandle = *info[0].As<Napi::External<HFRAMEFILTER>>().Data();

    IC_FrameFilterShowDialog *f_ptr = (IC_FrameFilterShowDialog *)GetProcAddress(tisgrabber, "IC_FrameFilterShowDialog");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_FrameFilterShowDialog in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(FilterHandle);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_FrameFilterGetParameter(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HFRAMEFILTER FilterHandle = *info[0].As<Napi::External<HFRAMEFILTER>>().Data();
    char *ParameterName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    void *Data = nullptr;
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_FrameFilterGetParameter *f_ptr = (IC_FrameFilterGetParameter *)GetProcAddress(tisgrabber, "IC_FrameFilterGetParameter");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_FrameFilterGetParameter in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(FilterHandle, ParameterName, Data);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_FrameFilterSetParameterInt(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HFRAMEFILTER FilterHandle = *info[0].As<Napi::External<HFRAMEFILTER>>().Data();
    char *ParameterName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    int Data = (int)info[2].As<Napi::Number>().Int64Value();
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
    IC_FrameFilterSetParameterInt *f_ptr = (IC_FrameFilterSetParameterInt *)GetProcAddress(tisgrabber, "IC_FrameFilterSetParameterInt");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_FrameFilterSetParameterInt in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(FilterHandle, ParameterName, Data);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_FrameFilterSetParameterFloat(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HFRAMEFILTER FilterHandle = *info[0].As<Napi::External<HFRAMEFILTER>>().Data();
    char *ParameterName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    float Data = (float)info[2].As<Napi::Number>().DoubleValue();
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
    IC_FrameFilterSetParameterFloat *f_ptr = (IC_FrameFilterSetParameterFloat *)GetProcAddress(tisgrabber, "IC_FrameFilterSetParameterFloat");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_FrameFilterSetParameterFloat in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(FilterHandle, ParameterName, Data);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_FrameFilterSetParameterBoolean(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HFRAMEFILTER FilterHandle = *info[0].As<Napi::External<HFRAMEFILTER>>().Data();
    char *ParameterName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    int Data = (int)info[2].As<Napi::Number>().Int64Value();
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
    IC_FrameFilterSetParameterBoolean *f_ptr = (IC_FrameFilterSetParameterBoolean *)GetProcAddress(tisgrabber, "IC_FrameFilterSetParameterBoolean");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_FrameFilterSetParameterBoolean in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(FilterHandle, ParameterName, Data);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_FrameFilterSetParameterString(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HFRAMEFILTER FilterHandle = *info[0].As<Napi::External<HFRAMEFILTER>>().Data();
    char *ParameterName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    char *Data = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
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
    IC_FrameFilterSetParameterString *f_ptr = (IC_FrameFilterSetParameterString *)GetProcAddress(tisgrabber, "IC_FrameFilterSetParameterString");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_FrameFilterSetParameterString in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(FilterHandle, ParameterName, Data);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_FrameFilterDeviceClear(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();

    IC_FrameFilterDeviceClear *f_ptr = (IC_FrameFilterDeviceClear *)GetProcAddress(tisgrabber, "IC_FrameFilterDeviceClear");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_FrameFilterDeviceClear in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_Codec_Create(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    char *Name = (char *)info[0].As<Napi::String>().Utf8Value().c_str();
    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 0").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_Codec_Create *f_ptr = (IC_Codec_Create *)GetProcAddress(tisgrabber, "IC_Codec_Create");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_Codec_Create in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    HCODEC ret = f(Name);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::External<HCODEC>::New(env, &ret));
    return retObj;
}
Napi::Value f_IC_Codec_Release(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HCODEC Codec = *info[0].As<Napi::External<HCODEC>>().Data();

    IC_Codec_Release *f_ptr = (IC_Codec_Release *)GetProcAddress(tisgrabber, "IC_Codec_Release");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_Codec_Release in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    f(Codec);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
    return retObj;
}
Napi::Value f_IC_Codec_getName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HCODEC Codec = *info[0].As<Napi::External<HCODEC>>().Data();
    int l = (int)info[1].As<Napi::Number>().Int64Value();
    char *Name = (char *)info[2].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    if (!info[2].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 2").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_Codec_getName *f_ptr = (IC_Codec_getName *)GetProcAddress(tisgrabber, "IC_Codec_getName");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_Codec_getName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(Codec, l, Name);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_Codec_hasDialog(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HCODEC Codec = *info[0].As<Napi::External<HCODEC>>().Data();

    IC_Codec_hasDialog *f_ptr = (IC_Codec_hasDialog *)GetProcAddress(tisgrabber, "IC_Codec_hasDialog");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_Codec_hasDialog in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(Codec);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_Codec_showDialog(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HCODEC Codec = *info[0].As<Napi::External<HCODEC>>().Data();

    IC_Codec_showDialog *f_ptr = (IC_Codec_showDialog *)GetProcAddress(tisgrabber, "IC_Codec_showDialog");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_Codec_showDialog in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(Codec);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_SetCodec(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hlGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    HCODEC Codec = *info[1].As<Napi::External<HCODEC>>().Data();

    IC_SetCodec *f_ptr = (IC_SetCodec *)GetProcAddress(tisgrabber, "IC_SetCodec");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetCodec in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hlGrabber, Codec);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_SetAVIFileName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hlGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    char *FileName = (char *)info[1].As<Napi::String>().Utf8Value().c_str();
    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetAVIFileName *f_ptr = (IC_SetAVIFileName *)GetProcAddress(tisgrabber, "IC_SetAVIFileName");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetAVIFileName in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hlGrabber, FileName);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    return retObj;
}
Napi::Value f_IC_enableAVICapturePause(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    HGRABBER hlGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int Pause = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_enableAVICapturePause *f_ptr = (IC_enableAVICapturePause *)GetProcAddress(tisgrabber, "IC_enableAVICapturePause");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_enableAVICapturePause in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hlGrabber, Pause);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int Count = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_SetRingBufferSize *f_ptr = (IC_SetRingBufferSize *)GetProcAddress(tisgrabber, "IC_SetRingBufferSize");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_SetRingBufferSize in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, Count);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HGRABBER hGrabber = *info[0].As<Napi::External<HGRABBER>>().Data();
    int *pCount;

    IC_GetRingBufferSize *f_ptr = (IC_GetRingBufferSize *)GetProcAddress(tisgrabber, "IC_GetRingBufferSize");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetRingBufferSize in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hGrabber, pCount);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("pCount", Napi::Number::New(env, *pCount));
    retObj.Set("outArgs", outArgs);
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
    HMEMBUFFER hBuffer = *info[0].As<Napi::External<HMEMBUFFER>>().Data();
    int *pWidth;
    int *pHeight;
    int *pBitsPerPixel;

    IC_GetMemBufferDescription *f_ptr = (IC_GetMemBufferDescription *)GetProcAddress(tisgrabber, "IC_GetMemBufferDescription");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_GetMemBufferDescription in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hBuffer, pWidth, pHeight, pBitsPerPixel);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("pWidth", Napi::Number::New(env, *pWidth));
    outArgs.Set("pHeight", Napi::Number::New(env, *pHeight));
    outArgs.Set("pBitsPerPixel", Napi::Number::New(env, *pBitsPerPixel));
    retObj.Set("outArgs", outArgs);
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
    HMEMBUFFER hBuffer = *info[0].As<Napi::External<HMEMBUFFER>>().Data();
    int lock = (int)info[1].As<Napi::Number>().Int64Value();
    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong type of argument 1").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    IC_MemBufferLock *f_ptr = (IC_MemBufferLock *)GetProcAddress(tisgrabber, "IC_MemBufferLock");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_MemBufferLock in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hBuffer, lock);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
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
    HMEMBUFFER hBuffer = *info[0].As<Napi::External<HMEMBUFFER>>().Data();
    int *plocked;

    IC_MemBufferisLocked *f_ptr = (IC_MemBufferisLocked *)GetProcAddress(tisgrabber, "IC_MemBufferisLocked");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_MemBufferisLocked in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hBuffer, plocked);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("plocked", Napi::Number::New(env, *plocked));
    retObj.Set("outArgs", outArgs);
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
    HMEMBUFFER hBuffer = *info[0].As<Napi::External<HMEMBUFFER>>().Data();
    int *pIndex;

    IC_MemBufferGetIndex *f_ptr = (IC_MemBufferGetIndex *)GetProcAddress(tisgrabber, "IC_MemBufferGetIndex");
    if (f_ptr == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_MemBufferGetIndex in tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return env.Undefined();
    };
    auto f = *f_ptr;
    int ret = f(hBuffer, pIndex);
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", Napi::Number::New(env, (double)ret));
    Napi::Object outArgs = Napi::Object::New(env);
    outArgs.Set("pIndex", Napi::Number::New(env, *pIndex));
    retObj.Set("outArgs", outArgs);
    return retObj;
}
// generate end

void device_lost_cb(HGRABBER hGrabber, void *data = nullptr)
{

    // std::vector<Napi::FunctionReference> cbs = grabber_device_lost_callbacks[hGrabber];
    // for (std::vector<Napi::FunctionReference>::iterator it = cbs.begin(); it != cbs.end(); ++it)
    // {
    //     Napi::FunctionReference cb = *it;
    //     cb.Call({Napi::External<HGRABBER>::New(env, &hGrabber)});
    // }
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
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
    INIT_STATIC_METHOD(IC_ListDevices)
    INIT_STATIC_METHOD(IC_ListDevicesbyIndex)
    INIT_STATIC_METHOD(IC_ListVideoFormats)
    INIT_STATIC_METHOD(IC_ListVideoFormatbyIndex)
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
    INIT_STATIC_METHOD(IC_LoadDeviceStateFromFile)
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
    INIT_STATIC_METHOD(IC_RemoveOverlay)
    INIT_STATIC_METHOD(IC_EnableOverlay)
    INIT_STATIC_METHOD(IC_BeginPaint)
    INIT_STATIC_METHOD(IC_EndPaint)
    INIT_STATIC_METHOD(IC_MsgBox)
    INIT_STATIC_METHOD(IC_SetContinuousMode)
    INIT_STATIC_METHOD(IC_SetFrameRate)
    INIT_STATIC_METHOD(IC_GetFrameRate)
    INIT_STATIC_METHOD(IC_GetAvailableFrameRates)
    INIT_STATIC_METHOD(IC_ShowInternalPropertyPage)
    INIT_STATIC_METHOD(IC_ResetUSBCam)
    INIT_STATIC_METHOD(IC_QueryPropertySet)
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
    INIT_STATIC_METHOD(IC_printItemandElementNames)
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
    INIT_STATIC_METHOD(IC_GetAvailableFrameFilterCount)
    INIT_STATIC_METHOD(IC_AddFrameFilterToDevice)
    INIT_STATIC_METHOD(IC_RemoveFrameFilterFromDevice)
    INIT_STATIC_METHOD(IC_DeleteFrameFilter)
    INIT_STATIC_METHOD(IC_FrameFilterShowDialog)
    INIT_STATIC_METHOD(IC_FrameFilterGetParameter)
    INIT_STATIC_METHOD(IC_FrameFilterSetParameterInt)
    INIT_STATIC_METHOD(IC_FrameFilterSetParameterFloat)
    INIT_STATIC_METHOD(IC_FrameFilterSetParameterBoolean)
    INIT_STATIC_METHOD(IC_FrameFilterSetParameterString)
    INIT_STATIC_METHOD(IC_FrameFilterDeviceClear)
    INIT_STATIC_METHOD(IC_Codec_Create)
    INIT_STATIC_METHOD(IC_Codec_Release)
    INIT_STATIC_METHOD(IC_Codec_getName)
    INIT_STATIC_METHOD(IC_Codec_hasDialog)
    INIT_STATIC_METHOD(IC_Codec_showDialog)
    INIT_STATIC_METHOD(IC_SetCodec)
    INIT_STATIC_METHOD(IC_SetAVIFileName)
    INIT_STATIC_METHOD(IC_enableAVICapturePause)
    INIT_STATIC_METHOD(IC_SetRingBufferSize)
    INIT_STATIC_METHOD(IC_GetRingBufferSize)
    INIT_STATIC_METHOD(IC_GetMemBufferDescription)
    INIT_STATIC_METHOD(IC_MemBufferLock)
    INIT_STATIC_METHOD(IC_MemBufferisLocked)
    INIT_STATIC_METHOD(IC_MemBufferGetIndex)
    return exports;
}

NODE_API_MODULE(ic_node, Init)

#else
#endif