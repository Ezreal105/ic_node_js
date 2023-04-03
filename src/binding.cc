#ifdef _WIN32

#include <napi.h>
#include <Windows.h>
#include "./binding.h"

#define LOAD_STATIC_METHOD(method)                                                                                           \
    TISGrabber::##method = (method)GetProcAddress(tisgrabber, #method);                                                      \
    if (TISGrabber::##method == NULL)                                                                                        \
    {                                                                                                                        \
        FreeLibrary(tisgrabber);                                                                                             \
        Napi::Error::New(info.Env(), "Cannot find function " #method " in tisgrabber_x64.dll").ThrowAsJavaScriptException(); \
        return;                                                                                                              \
    }                                                                                                                        \
    properties.push_back(StaticMethod<&TISGrabber::##method>(#method, static_cast<napi_property_attributes>(napi_writable | napi_configurable)));

class TISGrabber : public Napi::ObjectWrap<TISGrabber>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    TISGrabber(const Napi::CallbackInfo &info);

private:
    // ~TISGrabber();
    static IC_InitLibrary IC_InitLibrary;
    static IC_CreateGrabber IC_CreateGrabber;
    static IC_ReleaseGrabber IC_ReleaseGrabber;
    static IC_TidyUP IC_TidyUP;
    static IC_CloseLibrary IC_CloseLibrary;
    static IC_OpenVideoCaptureDevice IC_OpenVideoCaptureDevice;
    static IC_CloseVideoCaptureDevice IC_CloseVideoCaptureDevice;
    static IC_GetDeviceName IC_GetDeviceName;
    static IC_GetVideoFormatWidth IC_GetVideoFormatWidth;
    static IC_GetVideoFormatHeight IC_GetVideoFormatHeight;
    static IC_SetFormat IC_SetFormat;
    static IC_GetFormat IC_GetFormat;
    static IC_SetVideoFormat IC_SetVideoFormat;
    static IC_SetVideoNorm IC_SetVideoNorm;
    static IC_SetInputChannel IC_SetInputChannel;
    static IC_StartLive IC_StartLive;
    static IC_PrepareLive IC_PrepareLive;
    static IC_SuspendLive IC_SuspendLive;
    static IC_IsLive IC_IsLive;
    static IC_StopLive IC_StopLive;
    static IC_IsCameraPropertyAvailable IC_IsCameraPropertyAvailable;
    static IC_SetCameraProperty IC_SetCameraProperty;
    static IC_CameraPropertyGetRange IC_CameraPropertyGetRange;
    static IC_GetCameraProperty IC_GetCameraProperty;
    static IC_EnableAutoCameraProperty IC_EnableAutoCameraProperty;
    static IC_IsCameraPropertyAutoAvailable IC_IsCameraPropertyAutoAvailable;
    static IC_GetAutoCameraProperty IC_GetAutoCameraProperty;
    static IC_IsVideoPropertyAvailable IC_IsVideoPropertyAvailable;
    static IC_VideoPropertyGetRange IC_VideoPropertyGetRange;
    static IC_GetVideoProperty IC_GetVideoProperty;
    static IC_IsVideoPropertyAutoAvailable IC_IsVideoPropertyAutoAvailable;
    static IC_GetAutoVideoProperty IC_GetAutoVideoProperty;
    static IC_SetVideoProperty IC_SetVideoProperty;
    static IC_EnableAutoVideoProperty IC_EnableAutoVideoProperty;
    static IC_GetImageDescription IC_GetImageDescription;
    static IC_SnapImage IC_SnapImage;
    static IC_SaveImage IC_SaveImage;
    static IC_GetImagePtr IC_GetImagePtr;
    static IC_SetHWnd IC_SetHWnd;
    static IC_GetSerialNumber IC_GetSerialNumber;
    static IC_ListDevices IC_ListDevices;
    static IC_ListDevicesbyIndex IC_ListDevicesbyIndex;
    static IC_ListVideoFormats IC_ListVideoFormats;
    static IC_ListVideoFormatbyIndex IC_ListVideoFormatbyIndex;
    static IC_GetDeviceCount IC_GetDeviceCount;
    static IC_GetDevice IC_GetDevice;
    static IC_GetUniqueNamefromList IC_GetUniqueNamefromList;
    static IC_GetInputChannelCount IC_GetInputChannelCount;
    static IC_GetInputChannel IC_GetInputChannel;
    static IC_GetVideoNormCount IC_GetVideoNormCount;
    static IC_GetVideoNorm IC_GetVideoNorm;
    static IC_GetVideoFormatCount IC_GetVideoFormatCount;
    static IC_GetVideoFormat IC_GetVideoFormat;
    static IC_SaveDeviceStateToFile IC_SaveDeviceStateToFile;
    static IC_LoadDeviceStateFromFile IC_LoadDeviceStateFromFile;
    static IC_LoadDeviceStateFromFileEx IC_LoadDeviceStateFromFileEx;
    static IC_SaveDeviceSettings IC_SaveDeviceSettings;
    static IC_OpenDeviceBySettings IC_OpenDeviceBySettings;
    static IC_LoadDeviceSettings IC_LoadDeviceSettings;
    static IC_OpenDevByDisplayName IC_OpenDevByDisplayName;
    static IC_GetDisplayName IC_GetDisplayName;
    static IC_OpenDevByUniqueName IC_OpenDevByUniqueName;
    static IC_GetUniqueName IC_GetUniqueName;
    static IC_IsDevValid IC_IsDevValid;
    static IC_ShowPropertyDialog IC_ShowPropertyDialog;
    static IC_ShowDeviceSelectionDialog IC_ShowDeviceSelectionDialog;
    static IC_IsTriggerAvailable IC_IsTriggerAvailable;
    static IC_EnableTrigger IC_EnableTrigger;
    static IC_RemoveOverlay IC_RemoveOverlay;
    static IC_EnableOverlay IC_EnableOverlay;
    static IC_BeginPaint IC_BeginPaint;
    static IC_EndPaint IC_EndPaint;
    static IC_MsgBox IC_MsgBox;
    static IC_SetFrameReadyCallbackEx IC_SetFrameReadyCallbackEx;
    static IC_SetFrameReadyCallback IC_SetFrameReadyCallback;
    static IC_SetCallbacks IC_SetCallbacks;
    static IC_SetContinuousMode IC_SetContinuousMode;
    static IC_SetFrameRate IC_SetFrameRate;
    static IC_GetFrameRate IC_GetFrameRate;
    static IC_GetAvailableFrameRates IC_GetAvailableFrameRates;
    static IC_ShowInternalPropertyPage IC_ShowInternalPropertyPage;
    static IC_ResetUSBCam IC_ResetUSBCam;
    static IC_QueryPropertySet IC_QueryPropertySet;
    static IC_SetDefaultWindowPosition IC_SetDefaultWindowPosition;
    static IC_SetWindowPosition IC_SetWindowPosition;
    static IC_GetWindowPosition IC_GetWindowPosition;
    static IC_SetWhiteBalanceAuto IC_SetWhiteBalanceAuto;
    static IC_SignalDetected IC_SignalDetected;
    static IC_GetTriggerModes IC_GetTriggerModes;
    static IC_SetTriggerMode IC_SetTriggerMode;
    static IC_SetTriggerPolarity IC_SetTriggerPolarity;
    static IC_GetExpRegValRange IC_GetExpRegValRange;
    static IC_GetExpRegVal IC_GetExpRegVal;
    static IC_SetExpRegVal IC_SetExpRegVal;
    static IC_EnableExpRegValAuto IC_EnableExpRegValAuto;
    static IC_GetExpRegValAuto IC_GetExpRegValAuto;
    static IC_IsExpAbsValAvailable IC_IsExpAbsValAvailable;
    static IC_GetExpAbsValRange IC_GetExpAbsValRange;
    static IC_GetExpAbsVal IC_GetExpAbsVal;
    static IC_SetExpAbsVal IC_SetExpAbsVal;
    static IC_GetColorEnhancement IC_GetColorEnhancement;
    static IC_SetColorEnhancement IC_SetColorEnhancement;
    static IC_SoftwareTrigger IC_SoftwareTrigger;
    static IC_SetWhiteBalanceRed IC_SetWhiteBalanceRed;
    static IC_SetWhiteBalanceGreen IC_SetWhiteBalanceGreen;
    static IC_SetWhiteBalanceBlue IC_SetWhiteBalanceBlue;
    static IC_FocusOnePush IC_FocusOnePush;
    static IC_enumProperties IC_enumProperties;
    static IC_printItemandElementNames IC_printItemandElementNames;
    static IC_enumPropertyElements IC_enumPropertyElements;
    static IC_enumPropertyElementInterfaces IC_enumPropertyElementInterfaces;
    static IC_IsPropertyAvailable IC_IsPropertyAvailable;
    static IC_GetPropertyValueRange IC_GetPropertyValueRange;
    static IC_GetPropertyValue IC_GetPropertyValue;
    static IC_SetPropertyValue IC_SetPropertyValue;
    static IC_GetPropertyAbsoluteValueRange IC_GetPropertyAbsoluteValueRange;
    static IC_GetPropertyAbsoluteValue IC_GetPropertyAbsoluteValue;
    static IC_SetPropertyAbsoluteValue IC_SetPropertyAbsoluteValue;
    static IC_GetPropertySwitch IC_GetPropertySwitch;
    static IC_SetPropertySwitch IC_SetPropertySwitch;
    static IC_PropertyOnePush IC_PropertyOnePush;
    static IC_GetPropertyMapStrings IC_GetPropertyMapStrings;
    static IC_GetPropertyMapString IC_GetPropertyMapString;
    static IC_SetPropertyMapString IC_SetPropertyMapString;
    static IC_ResetProperties IC_ResetProperties;
    static IC_GetAvailableFrameFilterCount IC_GetAvailableFrameFilterCount;
    static IC_GetAvailableFrameFilters IC_GetAvailableFrameFilters;
    static IC_CreateFrameFilter IC_CreateFrameFilter;
    static IC_AddFrameFilterToDevice IC_AddFrameFilterToDevice;
    static IC_RemoveFrameFilterFromDevice IC_RemoveFrameFilterFromDevice;
    static IC_DeleteFrameFilter IC_DeleteFrameFilter;
    static IC_FrameFilterShowDialog IC_FrameFilterShowDialog;
    static IC_FrameFilterGetParameter IC_FrameFilterGetParameter;
    static IC_FrameFilterSetParameterInt IC_FrameFilterSetParameterInt;
    static IC_FrameFilterSetParameterFloat IC_FrameFilterSetParameterFloat;
    static IC_FrameFilterSetParameterBoolean IC_FrameFilterSetParameterBoolean;
    static IC_FrameFilterSetParameterString IC_FrameFilterSetParameterString;
    static IC_FrameFilterDeviceClear IC_FrameFilterDeviceClear;
    static IC_enumCodecs IC_enumCodecs;
    static IC_Codec_Create IC_Codec_Create;
    static IC_Codec_Release IC_Codec_Release;
    static IC_Codec_getName IC_Codec_getName;
    static IC_Codec_hasDialog IC_Codec_hasDialog;
    static IC_Codec_showDialog IC_Codec_showDialog;
    static IC_SetCodec IC_SetCodec;
    static IC_SetAVIFileName IC_SetAVIFileName;
    static IC_enableAVICapturePause IC_enableAVICapturePause;
    static IC_SetRingBufferSize IC_SetRingBufferSize;
    static IC_GetRingBufferSize IC_GetRingBufferSize;
    static IC_GetMemBuffer IC_GetMemBuffer;
    static IC_GetMemBufferLastAcq IC_GetMemBufferLastAcq;
    static IC_ReleaseMemBuffer IC_ReleaseMemBuffer;
    static IC_GetMemBufferDescription IC_GetMemBufferDescription;
    static IC_MemBufferLock IC_MemBufferLock;
    static IC_MemBufferisLocked IC_MemBufferisLocked;
    static IC_MemBufferGetIndex IC_MemBufferGetIndex;
    static IC_MemBufferGetDataPtr IC_MemBufferGetDataPtr;
    // HGRABBER m_hgrabber;
};

Napi::Object TISGrabber::Init(Napi::Env env, Napi::Object exports)
{
    // 加载动态库
    HMODULE tisgrabber = LoadLibrary("tisgrabber_x64.dll");
    if (tisgrabber == NULL)
    {
        Napi::Error::New(env, "Cannot load tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return;
    }
    std::initializer_list<Napi::ClassPropertyDescriptor<TISGrabber>> properties = {};
    LOAD_STATIC_METHOD(IC_InitLibrary);
    LOAD_STATIC_METHOD(IC_CreateGrabber);
    LOAD_STATIC_METHOD(IC_ReleaseGrabber);
    LOAD_STATIC_METHOD(IC_TidyUP);
    LOAD_STATIC_METHOD(IC_CloseLibrary);
    LOAD_STATIC_METHOD(IC_OpenVideoCaptureDevice);
    LOAD_STATIC_METHOD(IC_CloseVideoCaptureDevice);
    LOAD_STATIC_METHOD(IC_GetDeviceName);
    LOAD_STATIC_METHOD(IC_GetVideoFormatWidth);
    LOAD_STATIC_METHOD(IC_GetVideoFormatHeight);
    LOAD_STATIC_METHOD(IC_SetFormat);
    LOAD_STATIC_METHOD(IC_GetFormat);
    LOAD_STATIC_METHOD(IC_SetVideoFormat);
    LOAD_STATIC_METHOD(IC_SetVideoNorm);
    LOAD_STATIC_METHOD(IC_SetInputChannel);
    LOAD_STATIC_METHOD(IC_StartLive);
    LOAD_STATIC_METHOD(IC_PrepareLive);
    LOAD_STATIC_METHOD(IC_SuspendLive);
    LOAD_STATIC_METHOD(IC_IsLive);
    LOAD_STATIC_METHOD(IC_StopLive);
    LOAD_STATIC_METHOD(IC_IsCameraPropertyAvailable);
    LOAD_STATIC_METHOD(IC_SetCameraProperty);
    LOAD_STATIC_METHOD(IC_CameraPropertyGetRange);
    LOAD_STATIC_METHOD(IC_GetCameraProperty);
    LOAD_STATIC_METHOD(IC_EnableAutoCameraProperty);
    LOAD_STATIC_METHOD(IC_IsCameraPropertyAutoAvailable);
    LOAD_STATIC_METHOD(IC_GetAutoCameraProperty);
    LOAD_STATIC_METHOD(IC_IsVideoPropertyAvailable);
    LOAD_STATIC_METHOD(IC_VideoPropertyGetRange);
    LOAD_STATIC_METHOD(IC_GetVideoProperty);
    LOAD_STATIC_METHOD(IC_IsVideoPropertyAutoAvailable);
    LOAD_STATIC_METHOD(IC_GetAutoVideoProperty);
    LOAD_STATIC_METHOD(IC_SetVideoProperty);
    LOAD_STATIC_METHOD(IC_EnableAutoVideoProperty);
    LOAD_STATIC_METHOD(IC_GetImageDescription);
    LOAD_STATIC_METHOD(IC_SnapImage);
    LOAD_STATIC_METHOD(IC_SaveImage);
    LOAD_STATIC_METHOD(IC_GetImagePtr);
    LOAD_STATIC_METHOD(IC_SetHWnd);
    LOAD_STATIC_METHOD(IC_GetSerialNumber);
    LOAD_STATIC_METHOD(IC_ListDevices);
    LOAD_STATIC_METHOD(IC_ListDevicesbyIndex);
    LOAD_STATIC_METHOD(IC_ListVideoFormats);
    LOAD_STATIC_METHOD(IC_ListVideoFormatbyIndex);
    LOAD_STATIC_METHOD(IC_GetDeviceCount);
    LOAD_STATIC_METHOD(IC_GetDevice);
    LOAD_STATIC_METHOD(IC_GetUniqueNamefromList);
    LOAD_STATIC_METHOD(IC_GetInputChannelCount);
    LOAD_STATIC_METHOD(IC_GetInputChannel);
    LOAD_STATIC_METHOD(IC_GetVideoNormCount);
    LOAD_STATIC_METHOD(IC_GetVideoNorm);
    LOAD_STATIC_METHOD(IC_GetVideoFormatCount);
    LOAD_STATIC_METHOD(IC_GetVideoFormat);
    LOAD_STATIC_METHOD(IC_SaveDeviceStateToFile);
    LOAD_STATIC_METHOD(IC_LoadDeviceStateFromFile);
    LOAD_STATIC_METHOD(IC_LoadDeviceStateFromFileEx);
    LOAD_STATIC_METHOD(IC_SaveDeviceSettings);
    LOAD_STATIC_METHOD(IC_OpenDeviceBySettings);
    LOAD_STATIC_METHOD(IC_LoadDeviceSettings);
    LOAD_STATIC_METHOD(IC_OpenDevByDisplayName);
    LOAD_STATIC_METHOD(IC_GetDisplayName);
    LOAD_STATIC_METHOD(IC_OpenDevByUniqueName);
    LOAD_STATIC_METHOD(IC_GetUniqueName);
    LOAD_STATIC_METHOD(IC_IsDevValid);
    LOAD_STATIC_METHOD(IC_ShowPropertyDialog);
    LOAD_STATIC_METHOD(IC_ShowDeviceSelectionDialog);
    LOAD_STATIC_METHOD(IC_IsTriggerAvailable);
    LOAD_STATIC_METHOD(IC_EnableTrigger);
    LOAD_STATIC_METHOD(IC_RemoveOverlay);
    LOAD_STATIC_METHOD(IC_EnableOverlay);
    LOAD_STATIC_METHOD(IC_BeginPaint);
    LOAD_STATIC_METHOD(IC_EndPaint);
    LOAD_STATIC_METHOD(IC_MsgBox);
    LOAD_STATIC_METHOD(IC_SetFrameReadyCallbackEx);
    LOAD_STATIC_METHOD(IC_SetFrameReadyCallback);
    LOAD_STATIC_METHOD(IC_SetCallbacks);
    LOAD_STATIC_METHOD(IC_SetContinuousMode);
    LOAD_STATIC_METHOD(IC_SetFrameRate);
    LOAD_STATIC_METHOD(IC_GetFrameRate);
    LOAD_STATIC_METHOD(IC_GetAvailableFrameRates);
    LOAD_STATIC_METHOD(IC_ShowInternalPropertyPage);
    LOAD_STATIC_METHOD(IC_ResetUSBCam);
    LOAD_STATIC_METHOD(IC_QueryPropertySet);
    LOAD_STATIC_METHOD(IC_SetDefaultWindowPosition);
    LOAD_STATIC_METHOD(IC_SetWindowPosition);
    LOAD_STATIC_METHOD(IC_GetWindowPosition);
    LOAD_STATIC_METHOD(IC_SetWhiteBalanceAuto);
    LOAD_STATIC_METHOD(IC_SignalDetected);
    LOAD_STATIC_METHOD(IC_GetTriggerModes);
    LOAD_STATIC_METHOD(IC_SetTriggerMode);
    LOAD_STATIC_METHOD(IC_SetTriggerPolarity);
    LOAD_STATIC_METHOD(IC_GetExpRegValRange);
    LOAD_STATIC_METHOD(IC_GetExpRegVal);
    LOAD_STATIC_METHOD(IC_SetExpRegVal);
    LOAD_STATIC_METHOD(IC_EnableExpRegValAuto);
    LOAD_STATIC_METHOD(IC_GetExpRegValAuto);
    LOAD_STATIC_METHOD(IC_IsExpAbsValAvailable);
    LOAD_STATIC_METHOD(IC_GetExpAbsValRange);
    LOAD_STATIC_METHOD(IC_GetExpAbsVal);
    LOAD_STATIC_METHOD(IC_SetExpAbsVal);
    LOAD_STATIC_METHOD(IC_GetColorEnhancement);
    LOAD_STATIC_METHOD(IC_SetColorEnhancement);
    LOAD_STATIC_METHOD(IC_SoftwareTrigger);
    LOAD_STATIC_METHOD(IC_SetWhiteBalanceRed);
    LOAD_STATIC_METHOD(IC_SetWhiteBalanceGreen);
    LOAD_STATIC_METHOD(IC_SetWhiteBalanceBlue);
    LOAD_STATIC_METHOD(IC_FocusOnePush);
    LOAD_STATIC_METHOD(IC_enumProperties);
    LOAD_STATIC_METHOD(IC_printItemandElementNames);
    LOAD_STATIC_METHOD(IC_enumPropertyElements);
    LOAD_STATIC_METHOD(IC_enumPropertyElementInterfaces);
    LOAD_STATIC_METHOD(IC_IsPropertyAvailable);
    LOAD_STATIC_METHOD(IC_GetPropertyValueRange);
    LOAD_STATIC_METHOD(IC_GetPropertyValue);
    LOAD_STATIC_METHOD(IC_SetPropertyValue);
    LOAD_STATIC_METHOD(IC_GetPropertyAbsoluteValueRange);
    LOAD_STATIC_METHOD(IC_GetPropertyAbsoluteValue);
    LOAD_STATIC_METHOD(IC_SetPropertyAbsoluteValue);
    LOAD_STATIC_METHOD(IC_GetPropertySwitch);
    LOAD_STATIC_METHOD(IC_SetPropertySwitch);
    LOAD_STATIC_METHOD(IC_PropertyOnePush);
    LOAD_STATIC_METHOD(IC_GetPropertyMapStrings);
    LOAD_STATIC_METHOD(IC_GetPropertyMapString);
    LOAD_STATIC_METHOD(IC_SetPropertyMapString);
    LOAD_STATIC_METHOD(IC_ResetProperties);
    LOAD_STATIC_METHOD(IC_GetAvailableFrameFilterCount);
    LOAD_STATIC_METHOD(IC_GetAvailableFrameFilters);
    LOAD_STATIC_METHOD(IC_CreateFrameFilter);
    LOAD_STATIC_METHOD(IC_AddFrameFilterToDevice);
    LOAD_STATIC_METHOD(IC_RemoveFrameFilterFromDevice);
    LOAD_STATIC_METHOD(IC_DeleteFrameFilter);
    LOAD_STATIC_METHOD(IC_FrameFilterShowDialog);
    LOAD_STATIC_METHOD(IC_FrameFilterGetParameter);
    LOAD_STATIC_METHOD(IC_FrameFilterSetParameterInt);
    LOAD_STATIC_METHOD(IC_FrameFilterSetParameterFloat);
    LOAD_STATIC_METHOD(IC_FrameFilterSetParameterBoolean);
    LOAD_STATIC_METHOD(IC_FrameFilterSetParameterString);
    LOAD_STATIC_METHOD(IC_FrameFilterDeviceClear);
    LOAD_STATIC_METHOD(IC_enumCodecs);
    LOAD_STATIC_METHOD(IC_Codec_Create);
    LOAD_STATIC_METHOD(IC_Codec_Release);
    LOAD_STATIC_METHOD(IC_Codec_getName);
    LOAD_STATIC_METHOD(IC_Codec_hasDialog);
    LOAD_STATIC_METHOD(IC_Codec_showDialog);
    LOAD_STATIC_METHOD(IC_SetCodec);
    LOAD_STATIC_METHOD(IC_SetAVIFileName);
    LOAD_STATIC_METHOD(IC_enableAVICapturePause);
    LOAD_STATIC_METHOD(IC_SetRingBufferSize);
    LOAD_STATIC_METHOD(IC_GetRingBufferSize);
    LOAD_STATIC_METHOD(IC_GetMemBuffer);
    LOAD_STATIC_METHOD(IC_GetMemBufferLastAcq);
    LOAD_STATIC_METHOD(IC_ReleaseMemBuffer);
    LOAD_STATIC_METHOD(IC_GetMemBufferDescription);
    LOAD_STATIC_METHOD(IC_MemBufferLock);
    LOAD_STATIC_METHOD(IC_MemBufferisLocked);
    LOAD_STATIC_METHOD(IC_MemBufferGetIndex);
    LOAD_STATIC_METHOD(IC_MemBufferGetDataPtr);

    Napi::Function func = DefineClass(env, "TISGrabber", properties);
    Napi::FunctionReference *constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);

    exports.Set("TISGrabber", func);
    return exports;
}

// TISGrabber::TISGrabber(const Napi::CallbackInfo &info) : Napi::ObjectWrap<TISGrabber>(info)
// {
//     Napi::String unique_name = info[0].As<Napi::String>();
//     m_hgrabber = IC_CreateGrabber();
//     TISGrabber::IC_OpenDevByUniqueName(m_hgrabber, unique_name.Utf8Value().c_str());
// }

// TISGrabber::~TISGrabber()
// {
//     IC_ReleaseGrabber(&m_hgrabber);
// }

#else
#endif