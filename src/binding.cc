#ifdef _WIN32

#include <napi.h>
#include <Windows.h>
#include "./binding.h"

#define LOAD_STATIC_METHOD(method)                                                                                           \
    TISGrabber::##method = GetProcAddress(tisgrabber, #method);                                                              \
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
    static IC_InitLibrary IC_InitLibrary = NULL;
    static IC_CreateGrabber IC_CreateGrabber = NULL;
    static IC_ReleaseGrabber IC_ReleaseGrabber = NULL;
    static IC_TidyUP IC_TidyUP = NULL;
    static IC_CloseLibrary IC_CloseLibrary = NULL;
    static IC_OpenVideoCaptureDevice IC_OpenVideoCaptureDevice = NULL;
    static IC_CloseVideoCaptureDevice IC_CloseVideoCaptureDevice = NULL;
    static IC_GetDeviceName IC_GetDeviceName = NULL;
    static IC_GetVideoFormatWidth IC_GetVideoFormatWidth = NULL;
    static IC_GetVideoFormatHeight IC_GetVideoFormatHeight = NULL;
    static IC_SetFormat IC_SetFormat = NULL;
    static IC_GetFormat IC_GetFormat = NULL;
    static IC_SetVideoFormat IC_SetVideoFormat = NULL;
    static IC_SetVideoNorm IC_SetVideoNorm = NULL;
    static IC_SetInputChannel IC_SetInputChannel = NULL;
    static IC_StartLive IC_StartLive = NULL;
    static IC_PrepareLive IC_PrepareLive = NULL;
    static IC_SuspendLive IC_SuspendLive = NULL;
    static IC_IsLive IC_IsLive = NULL;
    static IC_StopLive IC_StopLive = NULL;
    static IC_IsCameraPropertyAvailable IC_IsCameraPropertyAvailable = NULL;
    static IC_SetCameraProperty IC_SetCameraProperty = NULL;
    static IC_CameraPropertyGetRange IC_CameraPropertyGetRange = NULL;
    static IC_GetCameraProperty IC_GetCameraProperty = NULL;
    static IC_EnableAutoCameraProperty IC_EnableAutoCameraProperty = NULL;
    static IC_IsCameraPropertyAutoAvailable IC_IsCameraPropertyAutoAvailable = NULL;
    static IC_GetAutoCameraProperty IC_GetAutoCameraProperty = NULL;
    static IC_IsVideoPropertyAvailable IC_IsVideoPropertyAvailable = NULL;
    static IC_VideoPropertyGetRange IC_VideoPropertyGetRange = NULL;
    static IC_GetVideoProperty IC_GetVideoProperty = NULL;
    static IC_IsVideoPropertyAutoAvailable IC_IsVideoPropertyAutoAvailable = NULL;
    static IC_GetAutoVideoProperty IC_GetAutoVideoProperty = NULL;
    static IC_SetVideoProperty IC_SetVideoProperty = NULL;
    static IC_EnableAutoVideoProperty IC_EnableAutoVideoProperty = NULL;
    static IC_GetImageDescription IC_GetImageDescription = NULL;
    static IC_SnapImage IC_SnapImage = NULL;
    static IC_SaveImage IC_SaveImage = NULL;
    static IC_GetImagePtr IC_GetImagePtr = NULL;
    static IC_SetHWnd IC_SetHWnd = NULL;
    static IC_GetSerialNumber IC_GetSerialNumber = NULL;
    static IC_ListDevices IC_ListDevices = NULL;
    static IC_ListDevicesbyIndex IC_ListDevicesbyIndex = NULL;
    static IC_ListVideoFormats IC_ListVideoFormats = NULL;
    static IC_ListVideoFormatbyIndex IC_ListVideoFormatbyIndex = NULL;
    static IC_GetDeviceCount IC_GetDeviceCount = NULL;
    static IC_GetDevice IC_GetDevice = NULL;
    static IC_GetUniqueNamefromList IC_GetUniqueNamefromList = NULL;
    static IC_GetInputChannelCount IC_GetInputChannelCount = NULL;
    static IC_GetInputChannel IC_GetInputChannel = NULL;
    static IC_GetVideoNormCount IC_GetVideoNormCount = NULL;
    static IC_GetVideoNorm IC_GetVideoNorm = NULL;
    static IC_GetVideoFormatCount IC_GetVideoFormatCount = NULL;
    static IC_GetVideoFormat IC_GetVideoFormat = NULL;
    static IC_SaveDeviceStateToFile IC_SaveDeviceStateToFile = NULL;
    static IC_LoadDeviceStateFromFile IC_LoadDeviceStateFromFile = NULL;
    static IC_LoadDeviceStateFromFileEx IC_LoadDeviceStateFromFileEx = NULL;
    static IC_SaveDeviceSettings IC_SaveDeviceSettings = NULL;
    static IC_OpenDeviceBySettings IC_OpenDeviceBySettings = NULL;
    static IC_LoadDeviceSettings IC_LoadDeviceSettings = NULL;
    static IC_OpenDevByDisplayName IC_OpenDevByDisplayName = NULL;
    static IC_GetDisplayName IC_GetDisplayName = NULL;
    static IC_OpenDevByUniqueName IC_OpenDevByUniqueName = NULL;
    static IC_GetUniqueName IC_GetUniqueName = NULL;
    static IC_IsDevValid IC_IsDevValid = NULL;
    static IC_ShowPropertyDialog IC_ShowPropertyDialog = NULL;
    static IC_ShowDeviceSelectionDialog IC_ShowDeviceSelectionDialog = NULL;
    static IC_IsTriggerAvailable IC_IsTriggerAvailable = NULL;
    static IC_EnableTrigger IC_EnableTrigger = NULL;
    static IC_RemoveOverlay IC_RemoveOverlay = NULL;
    static IC_EnableOverlay IC_EnableOverlay = NULL;
    static IC_BeginPaint IC_BeginPaint = NULL;
    static IC_EndPaint IC_EndPaint = NULL;
    static IC_MsgBox IC_MsgBox = NULL;
    static IC_SetFrameReadyCallbackEx IC_SetFrameReadyCallbackEx = NULL;
    static IC_SetFrameReadyCallback IC_SetFrameReadyCallback = NULL;
    static IC_SetCallbacks IC_SetCallbacks = NULL;
    static IC_SetContinuousMode IC_SetContinuousMode = NULL;
    static IC_SetFrameRate IC_SetFrameRate = NULL;
    static IC_GetFrameRate IC_GetFrameRate = NULL;
    static IC_GetAvailableFrameRates IC_GetAvailableFrameRates = NULL;
    static IC_ShowInternalPropertyPage IC_ShowInternalPropertyPage = NULL;
    static IC_ResetUSBCam IC_ResetUSBCam = NULL;
    static IC_QueryPropertySet IC_QueryPropertySet = NULL;
    static IC_SetDefaultWindowPosition IC_SetDefaultWindowPosition = NULL;
    static IC_SetWindowPosition IC_SetWindowPosition = NULL;
    static IC_GetWindowPosition IC_GetWindowPosition = NULL;
    static IC_SetWhiteBalanceAuto IC_SetWhiteBalanceAuto = NULL;
    static IC_SignalDetected IC_SignalDetected = NULL;
    static IC_GetTriggerModes IC_GetTriggerModes = NULL;
    static IC_SetTriggerMode IC_SetTriggerMode = NULL;
    static IC_SetTriggerPolarity IC_SetTriggerPolarity = NULL;
    static IC_GetExpRegValRange IC_GetExpRegValRange = NULL;
    static IC_GetExpRegVal IC_GetExpRegVal = NULL;
    static IC_SetExpRegVal IC_SetExpRegVal = NULL;
    static IC_EnableExpRegValAuto IC_EnableExpRegValAuto = NULL;
    static IC_GetExpRegValAuto IC_GetExpRegValAuto = NULL;
    static IC_IsExpAbsValAvailable IC_IsExpAbsValAvailable = NULL;
    static IC_GetExpAbsValRange IC_GetExpAbsValRange = NULL;
    static IC_GetExpAbsVal IC_GetExpAbsVal = NULL;
    static IC_SetExpAbsVal IC_SetExpAbsVal = NULL;
    static IC_GetColorEnhancement IC_GetColorEnhancement = NULL;
    static IC_SetColorEnhancement IC_SetColorEnhancement = NULL;
    static IC_SoftwareTrigger IC_SoftwareTrigger = NULL;
    static IC_SetWhiteBalanceRed IC_SetWhiteBalanceRed = NULL;
    static IC_SetWhiteBalanceGreen IC_SetWhiteBalanceGreen = NULL;
    static IC_SetWhiteBalanceBlue IC_SetWhiteBalanceBlue = NULL;
    static IC_FocusOnePush IC_FocusOnePush = NULL;
    static IC_enumProperties IC_enumProperties = NULL;
    static IC_printItemandElementNames IC_printItemandElementNames = NULL;
    static IC_enumPropertyElements IC_enumPropertyElements = NULL;
    static IC_enumPropertyElementInterfaces IC_enumPropertyElementInterfaces = NULL;
    static IC_IsPropertyAvailable IC_IsPropertyAvailable = NULL;
    static IC_GetPropertyValueRange IC_GetPropertyValueRange = NULL;
    static IC_GetPropertyValue IC_GetPropertyValue = NULL;
    static IC_SetPropertyValue IC_SetPropertyValue = NULL;
    static IC_GetPropertyAbsoluteValueRange IC_GetPropertyAbsoluteValueRange = NULL;
    static IC_GetPropertyAbsoluteValue IC_GetPropertyAbsoluteValue = NULL;
    static IC_SetPropertyAbsoluteValue IC_SetPropertyAbsoluteValue = NULL;
    static IC_GetPropertySwitch IC_GetPropertySwitch = NULL;
    static IC_SetPropertySwitch IC_SetPropertySwitch = NULL;
    static IC_PropertyOnePush IC_PropertyOnePush = NULL;
    static IC_GetPropertyMapStrings IC_GetPropertyMapStrings = NULL;
    static IC_GetPropertyMapString IC_GetPropertyMapString = NULL;
    static IC_SetPropertyMapString IC_SetPropertyMapString = NULL;
    static IC_ResetProperties IC_ResetProperties = NULL;
    static IC_GetAvailableFrameFilterCount IC_GetAvailableFrameFilterCount = NULL;
    static IC_GetAvailableFrameFilters IC_GetAvailableFrameFilters = NULL;
    static IC_CreateFrameFilter IC_CreateFrameFilter = NULL;
    static IC_AddFrameFilterToDevice IC_AddFrameFilterToDevice = NULL;
    static IC_RemoveFrameFilterFromDevice IC_RemoveFrameFilterFromDevice = NULL;
    static IC_DeleteFrameFilter IC_DeleteFrameFilter = NULL;
    static IC_FrameFilterShowDialog IC_FrameFilterShowDialog = NULL;
    static IC_FrameFilterGetParameter IC_FrameFilterGetParameter = NULL;
    static IC_FrameFilterSetParameterInt IC_FrameFilterSetParameterInt = NULL;
    static IC_FrameFilterSetParameterFloat IC_FrameFilterSetParameterFloat = NULL;
    static IC_FrameFilterSetParameterBoolean IC_FrameFilterSetParameterBoolean = NULL;
    static IC_FrameFilterSetParameterString IC_FrameFilterSetParameterString = NULL;
    static IC_FrameFilterDeviceClear IC_FrameFilterDeviceClear = NULL;
    static IC_enumCodecs IC_enumCodecs = NULL;
    static IC_Codec_Create IC_Codec_Create = NULL;
    static IC_Codec_Release IC_Codec_Release = NULL;
    static IC_Codec_getName IC_Codec_getName = NULL;
    static IC_Codec_hasDialog IC_Codec_hasDialog = NULL;
    static IC_Codec_showDialog IC_Codec_showDialog = NULL;
    static IC_SetCodec IC_SetCodec = NULL;
    static IC_SetAVIFileName IC_SetAVIFileName = NULL;
    static IC_enableAVICapturePause IC_enableAVICapturePause = NULL;
    static AC IC_SetRingBufferSize IC_SetRingBufferSize = NULL;
    static AC IC_GetRingBufferSize IC_GetRingBufferSize = NULL;
    static AC IC_GetMemBuffer IC_GetMemBuffer = NULL;
    static AC IC_GetMemBufferLastAcq IC_GetMemBufferLastAcq = NULL;
    static AC IC_ReleaseMemBuffer IC_ReleaseMemBuffer = NULL;
    static AC IC_GetMemBufferDescription IC_GetMemBufferDescription = NULL;
    static AC IC_MemBufferLock IC_MemBufferLock = NULL;
    static AC IC_MemBufferisLocked IC_MemBufferisLocked = NULL;
    static AC IC_MemBufferGetIndex IC_MemBufferGetIndex = NULL;
    static AC IC_MemBufferGetDataPtr IC_MemBufferGetDataPtr = NULL;
    // HGRABBER m_hgrabber;
};

Napi::Object TISGrabber::Init(Napi::Env env, Napi::Object exports)
{
    // 加载动态库
    HMODULE tisgrabber = LoadLibrary("tisgrabber_x64.dll");
    if (tisgrabber == NULL)
    {
        Napi::Error::New(env, "Cannot load tisgrabber_x64.dll").ThrowAsJavaScriptException();
        return exports;
    }
    std::vector<Napi::ClassPropertyDescriptor<TISGrabber>> properties = {};
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

NODE_API_MODULE(ic_node, TISGrabber::Init)

#else
#endif