// #define _WIN32
#ifdef _WIN32

#include <napi.h>
#include <Windows.h>
#include "./binding.h"

static HMODULE tisgrabber;

Napi::Value f_IC_TidyUP(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 0)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    IC_TidyUP f = (IC_TidyUP)GetProcAddress(tisgrabber, "IC_TidyUP");
    if (f == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_TidyUP in tisgrabber_x64.dll").ThrowAsJavaScriptException return env.undefined();
    };
    void ret = f();
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

    IC_CloseLibrary f = (IC_CloseLibrary)GetProcAddress(tisgrabber, "IC_CloseLibrary");
    if (f == NULL)
    {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function IC_CloseLibrary in tisgrabber_x64.dll").ThrowAsJavaScriptException return env.undefined();
    };
    void ret = f();
    Napi::Object retObj = Napi::Object::New(env);
    retObj.Set("result", env.Undefined());
    return retObj;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    Napi::Object ic_static = Napi::Object::New(env);
    ic_static.Set("IC_InitLibrary", Napi::Function::New<f_IC_InitLibrary>(env));
    exports.Set("ic_static", ic_static);
    // INIT_STATIC_METHOD(IC_InitLibrary);
    // INIT_STATIC_METHOD(IC_CreateGrabber);
    // INIT_STATIC_METHOD(IC_ReleaseGrabber);
    // INIT_STATIC_METHOD(IC_TidyUP);
    // INIT_STATIC_METHOD(IC_CloseLibrary);
    // INIT_STATIC_METHOD(IC_OpenVideoCaptureDevice);
    // INIT_STATIC_METHOD(IC_CloseVideoCaptureDevice);
    // INIT_STATIC_METHOD(IC_GetDeviceName);
    // INIT_STATIC_METHOD(IC_GetVideoFormatWidth);
    // INIT_STATIC_METHOD(IC_GetVideoFormatHeight);
    // INIT_STATIC_METHOD(IC_SetFormat);
    // INIT_STATIC_METHOD(IC_GetFormat);
    // INIT_STATIC_METHOD(IC_SetVideoFormat);
    // INIT_STATIC_METHOD(IC_SetVideoNorm);
    // INIT_STATIC_METHOD(IC_SetInputChannel);
    // INIT_STATIC_METHOD(IC_StartLive);
    // INIT_STATIC_METHOD(IC_PrepareLive);
    // INIT_STATIC_METHOD(IC_SuspendLive);
    // INIT_STATIC_METHOD(IC_IsLive);
    // INIT_STATIC_METHOD(IC_StopLive);
    // INIT_STATIC_METHOD(IC_IsCameraPropertyAvailable);
    // INIT_STATIC_METHOD(IC_SetCameraProperty);
    // INIT_STATIC_METHOD(IC_CameraPropertyGetRange);
    // INIT_STATIC_METHOD(IC_GetCameraProperty);
    // INIT_STATIC_METHOD(IC_EnableAutoCameraProperty);
    // INIT_STATIC_METHOD(IC_IsCameraPropertyAutoAvailable);
    // INIT_STATIC_METHOD(IC_GetAutoCameraProperty);
    // INIT_STATIC_METHOD(IC_IsVideoPropertyAvailable);
    // INIT_STATIC_METHOD(IC_VideoPropertyGetRange);
    // INIT_STATIC_METHOD(IC_GetVideoProperty);
    // INIT_STATIC_METHOD(IC_IsVideoPropertyAutoAvailable);
    // INIT_STATIC_METHOD(IC_GetAutoVideoProperty);
    // INIT_STATIC_METHOD(IC_SetVideoProperty);
    // INIT_STATIC_METHOD(IC_EnableAutoVideoProperty);
    // INIT_STATIC_METHOD(IC_GetImageDescription);
    // INIT_STATIC_METHOD(IC_SnapImage);
    // INIT_STATIC_METHOD(IC_SaveImage);
    // INIT_STATIC_METHOD(IC_GetImagePtr);
    // INIT_STATIC_METHOD(IC_SetHWnd);
    // INIT_STATIC_METHOD(IC_GetSerialNumber);
    // INIT_STATIC_METHOD(IC_ListDevices);
    // INIT_STATIC_METHOD(IC_ListDevicesbyIndex);
    // INIT_STATIC_METHOD(IC_ListVideoFormats);
    // INIT_STATIC_METHOD(IC_ListVideoFormatbyIndex);
    // INIT_STATIC_METHOD(IC_GetDeviceCount);
    // INIT_STATIC_METHOD(IC_GetDevice);
    // INIT_STATIC_METHOD(IC_GetUniqueNamefromList);
    // INIT_STATIC_METHOD(IC_GetInputChannelCount);
    // INIT_STATIC_METHOD(IC_GetInputChannel);
    // INIT_STATIC_METHOD(IC_GetVideoNormCount);
    // INIT_STATIC_METHOD(IC_GetVideoNorm);
    // INIT_STATIC_METHOD(IC_GetVideoFormatCount);
    // INIT_STATIC_METHOD(IC_GetVideoFormat);
    // INIT_STATIC_METHOD(IC_SaveDeviceStateToFile);
    // INIT_STATIC_METHOD(IC_LoadDeviceStateFromFile);
    // INIT_STATIC_METHOD(IC_LoadDeviceStateFromFileEx);
    // INIT_STATIC_METHOD(IC_SaveDeviceSettings);
    // INIT_STATIC_METHOD(IC_OpenDeviceBySettings);
    // INIT_STATIC_METHOD(IC_LoadDeviceSettings);
    // INIT_STATIC_METHOD(IC_OpenDevByDisplayName);
    // INIT_STATIC_METHOD(IC_GetDisplayName);
    // INIT_STATIC_METHOD(IC_OpenDevByUniqueName);
    // INIT_STATIC_METHOD(IC_GetUniqueName);
    // INIT_STATIC_METHOD(IC_IsDevValid);
    // INIT_STATIC_METHOD(IC_ShowPropertyDialog);
    // INIT_STATIC_METHOD(IC_ShowDeviceSelectionDialog);
    // INIT_STATIC_METHOD(IC_IsTriggerAvailable);
    // INIT_STATIC_METHOD(IC_EnableTrigger);
    // INIT_STATIC_METHOD(IC_RemoveOverlay);
    // INIT_STATIC_METHOD(IC_EnableOverlay);
    // INIT_STATIC_METHOD(IC_BeginPaint);
    // INIT_STATIC_METHOD(IC_EndPaint);
    // INIT_STATIC_METHOD(IC_MsgBox);
    // INIT_STATIC_METHOD(IC_SetFrameReadyCallbackEx);
    // INIT_STATIC_METHOD(IC_SetFrameReadyCallback);
    // INIT_STATIC_METHOD(IC_SetCallbacks);
    // INIT_STATIC_METHOD(IC_SetContinuousMode);
    // INIT_STATIC_METHOD(IC_SetFrameRate);
    // INIT_STATIC_METHOD(IC_GetFrameRate);
    // INIT_STATIC_METHOD(IC_GetAvailableFrameRates);
    // INIT_STATIC_METHOD(IC_ShowInternalPropertyPage);
    // INIT_STATIC_METHOD(IC_ResetUSBCam);
    // INIT_STATIC_METHOD(IC_QueryPropertySet);
    // INIT_STATIC_METHOD(IC_SetDefaultWindowPosition);
    // INIT_STATIC_METHOD(IC_SetWindowPosition);
    // INIT_STATIC_METHOD(IC_GetWindowPosition);
    // INIT_STATIC_METHOD(IC_SetWhiteBalanceAuto);
    // INIT_STATIC_METHOD(IC_SignalDetected);
    // INIT_STATIC_METHOD(IC_GetTriggerModes);
    // INIT_STATIC_METHOD(IC_SetTriggerMode);
    // INIT_STATIC_METHOD(IC_SetTriggerPolarity);
    // INIT_STATIC_METHOD(IC_GetExpRegValRange);
    // INIT_STATIC_METHOD(IC_GetExpRegVal);
    // INIT_STATIC_METHOD(IC_SetExpRegVal);
    // INIT_STATIC_METHOD(IC_EnableExpRegValAuto);
    // INIT_STATIC_METHOD(IC_GetExpRegValAuto);
    // INIT_STATIC_METHOD(IC_IsExpAbsValAvailable);
    // INIT_STATIC_METHOD(IC_GetExpAbsValRange);
    // INIT_STATIC_METHOD(IC_GetExpAbsVal);
    // INIT_STATIC_METHOD(IC_SetExpAbsVal);
    // INIT_STATIC_METHOD(IC_GetColorEnhancement);
    // INIT_STATIC_METHOD(IC_SetColorEnhancement);
    // INIT_STATIC_METHOD(IC_SoftwareTrigger);
    // INIT_STATIC_METHOD(IC_SetWhiteBalanceRed);
    // INIT_STATIC_METHOD(IC_SetWhiteBalanceGreen);
    // INIT_STATIC_METHOD(IC_SetWhiteBalanceBlue);
    // INIT_STATIC_METHOD(IC_FocusOnePush);
    // INIT_STATIC_METHOD(IC_enumProperties);
    // INIT_STATIC_METHOD(IC_printItemandElementNames);
    // INIT_STATIC_METHOD(IC_enumPropertyElements);
    // INIT_STATIC_METHOD(IC_enumPropertyElementInterfaces);
    // INIT_STATIC_METHOD(IC_IsPropertyAvailable);
    // INIT_STATIC_METHOD(IC_GetPropertyValueRange);
    // INIT_STATIC_METHOD(IC_GetPropertyValue);
    // INIT_STATIC_METHOD(IC_SetPropertyValue);
    // INIT_STATIC_METHOD(IC_GetPropertyAbsoluteValueRange);
    // INIT_STATIC_METHOD(IC_GetPropertyAbsoluteValue);
    // INIT_STATIC_METHOD(IC_SetPropertyAbsoluteValue);
    // INIT_STATIC_METHOD(IC_GetPropertySwitch);
    // INIT_STATIC_METHOD(IC_SetPropertySwitch);
    // INIT_STATIC_METHOD(IC_PropertyOnePush);
    // INIT_STATIC_METHOD(IC_GetPropertyMapStrings);
    // INIT_STATIC_METHOD(IC_GetPropertyMapString);
    // INIT_STATIC_METHOD(IC_SetPropertyMapString);
    // INIT_STATIC_METHOD(IC_ResetProperties);
    // INIT_STATIC_METHOD(IC_GetAvailableFrameFilterCount);
    // INIT_STATIC_METHOD(IC_GetAvailableFrameFilters);
    // INIT_STATIC_METHOD(IC_CreateFrameFilter);
    // INIT_STATIC_METHOD(IC_AddFrameFilterToDevice);
    // INIT_STATIC_METHOD(IC_RemoveFrameFilterFromDevice);
    // INIT_STATIC_METHOD(IC_DeleteFrameFilter);
    // INIT_STATIC_METHOD(IC_FrameFilterShowDialog);
    // INIT_STATIC_METHOD(IC_FrameFilterGetParameter);
    // INIT_STATIC_METHOD(IC_FrameFilterSetParameterInt);
    // INIT_STATIC_METHOD(IC_FrameFilterSetParameterFloat);
    // INIT_STATIC_METHOD(IC_FrameFilterSetParameterBoolean);
    // INIT_STATIC_METHOD(IC_FrameFilterSetParameterString);
    // INIT_STATIC_METHOD(IC_FrameFilterDeviceClear);
    // INIT_STATIC_METHOD(IC_enumCodecs);
    // INIT_STATIC_METHOD(IC_Codec_Create);
    // INIT_STATIC_METHOD(IC_Codec_Release);
    // INIT_STATIC_METHOD(IC_Codec_getName);
    // INIT_STATIC_METHOD(IC_Codec_hasDialog);
    // INIT_STATIC_METHOD(IC_Codec_showDialog);
    // INIT_STATIC_METHOD(IC_SetCodec);
    // INIT_STATIC_METHOD(IC_SetAVIFileName);
    // INIT_STATIC_METHOD(IC_enableAVICapturePause);
    // INIT_STATIC_METHOD(IC_SetRingBufferSize);
    // INIT_STATIC_METHOD(IC_GetRingBufferSize);
    // INIT_STATIC_METHOD(IC_GetMemBuffer);
    // INIT_STATIC_METHOD(IC_GetMemBufferLastAcq);
    // INIT_STATIC_METHOD(IC_ReleaseMemBuffer);
    // INIT_STATIC_METHOD(IC_GetMemBufferDescription);
    // INIT_STATIC_METHOD(IC_MemBufferLock);
    // INIT_STATIC_METHOD(IC_MemBufferisLocked);
    // INIT_STATIC_METHOD(IC_MemBufferGetIndex);
    // INIT_STATIC_METHOD(IC_MemBufferGetDataPtr);
    return exports;
}

NODE_API_MODULE(ic_node, Init)

#else
#endif