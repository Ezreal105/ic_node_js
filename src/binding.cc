// #define _WIN32
#ifdef _WIN32

#include <napi.h>
#include <Windows.h>
#include <functional>
#include "./binding.h"

#define INIT_STATIC_METHOD(method) \
    ic_static.Set(#method, Napi::Function::New<f_##method>(env));

static HMODULE tisgrabber;

void device_lost_cb(Napi::FunctionReference js_func, const Napi::CallbackInfo &info, HGRABBER hGrabber, void *data = nullptr)
{
    Napi::Env env = info.Env();
    js_func.Call({Napi::External<HGRABBER>::New(env, &hGrabber)});
}

DEVICE_LOST_CALLBACK GET_DEVICE_LOST_CALLBACK(Napi::FunctionReference js_func, const Napi::CallbackInfo &info)
{
    auto func = std::bind(frame_ready_cb, js_func, info, std::placeholders::_1, std::placeholders::_2);
    return reinterpret_cast<DEVICE_LOST_CALLBACK>(std::addressof(func));
}

void frame_ready_cb(Napi::FunctionReference js_func, const Napi::CallbackInfo &info, HGRABBER hGrabber, unsigned char *pData, unsigned long frameNumber, void *data = nullptr)
{
    Napi::Env env = info.Env();
    js_func.Call({Napi::External<HGRABBER>::New(env, &hGrabber), Napi::External<unsigned char>::New(env, pData), Napi::Number::New(env, frameNumber)});
}

FRAME_READY_CALLBACK GET_FRAME_READY_CALLBACK(Napi::FunctionReference js_func, const Napi::CallbackInfo &info)
{
    auto func = std::bind(frame_ready_cb, js_func, info, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    return reinterpret_cast<FRAME_READY_CALLBACK>(std::addressof(func));
}

void frame_ready_cb_ex(Napi::FunctionReference js_func, const Napi::CallbackInfo &info, HGRABBER hGrabber, HMEMBUFFER hBuffer, unsigned long frameNumber, void *data = nullptr)
{
    Napi::Env env = info.Env();
    js_func.Call({Napi::External<HGRABBER>::New(env, &hGrabber), Napi::External<HMEMBUFFER>::New(env, hBuffer), Napi::Number::New(env, frameNumber)});
}

FRAME_READY_CALLBACK GET_FRAME_READY_CALLBACK_EX(Napi::FunctionReference js_func, const Napi::CallbackInfo &info)
{
    auto func = std::bind(frame_ready_cb_ex, js_func, info, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    return reinterpret_cast<FRAME_READY_CALLBACK_EX>(std::addressof(func));
}

void ic_enum_cb(Napi::FunctionReference js_func, const Napi::CallbackInfo &info, char *Name, void *data = nullptr)
{
    Napi::Env env = info.Env();
    js_func.Call({Napi::String::New(env, Name)});
}

IC_ENUMCB GET_IC_ENUMCB(Napi::FunctionReference js_func, const Napi::CallbackInfo &info)
{
    auto func = std::bind(ic_enum_cb, js_func, info, std::placeholders::_1, std::placeholders::_2);
    return reinterpret_cast<IC_ENUMCB>(func);
}

void enum_codec_cb(Napi::FunctionReference js_func, const Napi::CallbackInfo &info, char *CodecName, void *data = nullptr)
{
    Napi::Env env = info.Env();
    js_func.Call({Napi::String::New(env, CodecName)});
}

IC_ENUMCB GET_ENUMCODECCB(Napi::FunctionReference js_func, const Napi::CallbackInfo &info)
{
    auto func = std::bind(ic_enum_cb, js_func, info, std::placeholders::_1, std::placeholders::_2);
    return reinterpret_cast<ENUMCODECCB>(func);
}

// generated

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    Napi::Object ic_static = Napi::Object::New(env);
    exports.Set("ic_static", ic_static);
    INIT_STATIC_METHOD(IC_InitLibrary)
    INIT_STATIC_METHOD(IC_CreateGrabber)
    INIT_STATIC_METHOD(IC_ReleaseGrabber)
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
    INIT_STATIC_METHOD(IC_GetUniqueName)
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
    INIT_STATIC_METHOD(IC_SetFrameReadyCallbackEx)
    INIT_STATIC_METHOD(IC_SetFrameReadyCallback)
    INIT_STATIC_METHOD(IC_SetCallbacks)
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
    INIT_STATIC_METHOD(IC_enumProperties)
    INIT_STATIC_METHOD(IC_printItemandElementNames)
    INIT_STATIC_METHOD(IC_enumPropertyElements)
    INIT_STATIC_METHOD(IC_enumPropertyElementInterfaces)
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
    INIT_STATIC_METHOD(IC_GetPropertyMapStrings)
    INIT_STATIC_METHOD(IC_GetPropertyMapString)
    INIT_STATIC_METHOD(IC_SetPropertyMapString)
    INIT_STATIC_METHOD(IC_ResetProperties)
    INIT_STATIC_METHOD(IC_GetAvailableFrameFilterCount)
    INIT_STATIC_METHOD(IC_GetAvailableFrameFilters)
    INIT_STATIC_METHOD(IC_CreateFrameFilter)
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
    INIT_STATIC_METHOD(IC_enumCodecs)
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
    INIT_STATIC_METHOD(IC_GetMemBuffer)
    INIT_STATIC_METHOD(IC_GetMemBufferLastAcq)
    INIT_STATIC_METHOD(IC_GetMemBufferDescription)
    INIT_STATIC_METHOD(IC_MemBufferLock)
    INIT_STATIC_METHOD(IC_MemBufferisLocked)
    INIT_STATIC_METHOD(IC_MemBufferGetIndex)
    return exports;
}

NODE_API_MODULE(ic_node, Init)

#else
#endif