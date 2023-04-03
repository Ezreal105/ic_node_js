#ifdef _WIN32

#include <napi.h>
#include <Windows.h>
#include "./binding.h"

#define LOAD_METHOD(method)                                                                                                     \
    m_IC_##method = (method)GetProcAddress(tisgrabber, "##method");                                                             \
    if (m_IC_##method == NULL)                                                                                                  \
    {                                                                                                                           \
        FreeLibrary(tisgrabber);                                                                                                \
        Napi::Error::New(info.Env(), "Cannot find function IC_" #method " in tisgrabber_x64.dll").ThrowAsJavaScriptException(); \
        return;                                                                                                                 \
    }                                                                                                                           \
    properties.push_back(InstanceMethod<&TISGrabber::m_IC_##method>(#method, static_cast<napi_property_attributes>(napi_writable | napi_configurable)));

#define LOAD_STATIC_METHOD(method)                                                                                              \
    TISGrabber::IC_##method = (method)GetProcAddress(tisgrabber, "IC_##method");                                                \
    if (TISGrabber::IC_##method == NULL)                                                                                        \
    {                                                                                                                           \
        FreeLibrary(tisgrabber);                                                                                                \
        Napi::Error::New(info.Env(), "Cannot find function IC_" #method " in tisgrabber_x64.dll").ThrowAsJavaScriptException(); \
        return;                                                                                                                 \
    }                                                                                                                           \
    properties.push_back(StaticMethod<&TISGrabber::IC_##method>(#method, static_cast<napi_property_attributes>(napi_writable | napi_configurable)));

// typedef int AC (*IC_InitLibrary)(char *);
// typedef HGRABBER (*IC_CreateGrabber)();
// typedef void (*IC_ReleaseGrabber)(HGRABBER *);
// typedef void (*IC_TidyUP)();
// typedef void (*IC_CloseLibrary)();
// typedef int (*IC_OpenVideoCaptureDevice)(HGRABBER, char *);
// typedef void (*IC_CloseVideoCaptureDevice)(HGRABBER);
// typedef char *(*IC_GetDeviceName)(HGRABBER);
// typedef int (*IC_GetVideoFormatWidth)(HGRABBER);
// typedef int (*IC_GetVideoFormatHeight)(HGRABBER);
// typedef int (*IC_SetFormat)(HGRABBER, COLORFORMAT);
// typedef COLORFORMAT (*IC_GetFormat)(HGRABBER);
// typedef int (*IC_SetVideoFormat)(HGRABBER, char *);
// typedef int (*IC_SetVideoNorm)(HGRABBER, char *);
// typedef int (*IC_SetInputChannel)(HGRABBER, char *);
// typedef int (*IC_StartLive)(HGRABBER, int);
// typedef int (*IC_PrepareLive)(HGRABBER, int);
// typedef int (*IC_SuspendLive)(HGRABBER);
// typedef int (*IC_IsLive)(HGRABBER);
// typedef void (*IC_StopLive)(HGRABBER);
// typedef int (*IC_IsCameraPropertyAvailable)(HGRABBER, CAMERA_PROPERTY);
// typedef int (*IC_SetCameraProperty)(HGRABBER, CAMERA_PROPERTY, long);
// typedef int (*IC_CameraPropertyGetRange)(HGRABBER, CAMERA_PROPERTY, long *, long *);
// typedef int (*IC_GetCameraProperty)(HGRABBER, CAMERA_PROPERTY);
// typedef int AC (*IC_EnableAutoCameraProperty)(HGRABBER, int, int);
// typedef int AC (*IC_IsCameraPropertyAutoAvailable)(HGRABBER, CAMERA_PROPERTY);
// typedef int AC (*IC_GetAutoCameraProperty)(HGRABBER, int, int *);
// typedef int AC (*IC_IsVideoPropertyAvailable)(HGRABBER, VIDEO_PROPERTY);
// typedef int AC (*IC_VideoPropertyGetRange)(HGRABBER, VIDEO_PROPERTY, long *, long *);
// typedef int AC (*IC_GetVideoProperty)(HGRABBER, VIDEO_PROPERTY, long *);
// typedef int AC (*IC_IsVideoPropertyAutoAvailable)(HGRABBER, VIDEO_PROPERTY);
// typedef int AC (*IC_GetAutoVideoProperty)(HGRABBER, int, int *);
// typedef int AC (*IC_SetVideoProperty)(HGRABBER, VIDEO_PROPERTY, long);
// typedef int AC (*IC_EnableAutoVideoProperty)(HGRABBER, int, int);
// typedef int AC (*IC_GetImageDescription)(HGRABBER, long *, long *, int *, COLORFORMAT *);
// typedef int AC (*IC_SnapImage)(HGRABBER, int);
// typedef int AC (*IC_SaveImage)(HGRABBER, char *, IMG_FILETYPE, long);
// typedef unsigned char *AC (*IC_GetImagePtr)(HGRABBER);

// typedef int AC (*IC_SetHWnd)(HGRABBER, __HWND);

// typedef int AC (*IC_GetSerialNumber)(HGRABBER, char *);

// typedef int AC (*IC_ListDevices)(char *, int);

// typedef int AC (*IC_ListDevicesbyIndex)(char *, int, int);

// typedef int AC (*IC_ListVideoFormats)(HGRABBER, char *, int);

// typedef int AC (*IC_ListVideoFormatbyIndex)(HGRABBER, char *, int, int);

// typedef int (*IC_GetDeviceCount)();

// typedef char *(*IC_GetDevice)(int);

// typedef char *(*IC_GetUniqueNamefromList)(int);

// typedef int (*IC_GetInputChannelCount)(HGRABBER);

// typedef char *(*IC_GetInputChannel)(HGRABBER, int);

// typedef int (*IC_GetVideoNormCount)(HGRABBER);

// typedef char *(*IC_GetVideoNorm)(HGRABBER, int);

// typedef int (*IC_GetVideoFormatCount)(HGRABBER);

// typedef char *(*IC_GetVideoFormat)(HGRABBER, int);
// typedef int AC (*IC_SaveDeviceStateToFile)(HGRABBER, char *);
// typedef HGRABBER AC (*IC_LoadDeviceStateFromFile)(HGRABBER, char *);
// typedef int AC (*IC_LoadDeviceStateFromFileEx)(HGRABBER, char *, int);
// typedef int AC (*IC_SaveDeviceSettings)(HGRABBER, char *);
// typedef int AC (*IC_OpenDeviceBySettings)(HGRABBER, char *);
// typedef int AC (*IC_LoadDeviceSettings)(HGRABBER, char *);
// typedef int AC (*IC_OpenDevByDisplayName)(HGRABBER, char *);
// typedef int AC (*IC_GetDisplayName)(HGRABBER, char *, int);
// typedef int AC (*IC_OpenDevByUniqueName)(HGRABBER, char *);
// typedef int AC (*IC_GetUniqueName)(HGRABBER, char *, int);
// typedef int AC (*IC_IsDevValid)(HGRABBER);
// typedef int AC (*IC_ShowPropertyDialog)(HGRABBER);
// typedef HGRABBER AC (*IC_ShowDeviceSelectionDialog)(HGRABBER);
// typedef int AC (*IC_IsTriggerAvailable)(HGRABBER);
// typedef int AC (*IC_EnableTrigger)(HGRABBER, int);
// typedef void AC (*IC_RemoveOverlay)(HGRABBER, int);
// typedef void AC (*IC_EnableOverlay)(HGRABBER, int);
// typedef long AC (*IC_BeginPaint)(HGRABBER);
// typedef void AC (*IC_EndPaint)(HGRABBER);
// typedef void AC (*IC_MsgBox)(char *, char *);
// typedef int AC (*IC_SetFrameReadyCallbackEx)(HGRABBER, FRAME_READY_CALLBACK_EX, void *);
// typedef int AC (*IC_SetFrameReadyCallback)(HGRABBER, FRAME_READY_CALLBACK_EX, void *);
// typedef int AC (*IC_SetCallbacks)(HGRABBER, FRAME_READY_CALLBACK, void *, DEVICE_LOST_CALLBACK, void *);
// typedef int AC (*IC_SetContinuousMode)(HGRABBER, int);
// typedef int AC (*IC_SetFrameRate)(HGRABBER, float);
// typedef float AC (*IC_GetFrameRate)(HGRABBER);
// typedef int AC (*IC_GetAvailableFrameRates)(HGRABBER, int, float *);
// typedef int AC (*IC_ShowInternalPropertyPage)(HGRABBER);
// typedef int AC (*IC_ResetUSBCam)(HGRABBER);
// typedef int AC (*IC_QueryPropertySet)(HGRABBER);
// typedef int AC (*IC_SetDefaultWindowPosition)(HGRABBER, int);
// typedef int AC (*IC_SetWindowPosition)(HGRABBER, int, int, int, int);
// typedef int AC (*IC_GetWindowPosition)(HGRABBER, int *, int *, int *, int *);
// typedef int AC (*IC_SetWhiteBalanceAuto)(HGRABBER, int);
// typedef int AC (*IC_SignalDetected)(HGRABBER);
// typedef int AC (*IC_GetTriggerModes)(HGRABBER, char *, int);
// typedef int AC (*IC_SetTriggerMode)(HGRABBER, char *);
// typedef int AC (*IC_SetTriggerPolarity)(HGRABBER, int);

// typedef int AC (*IC_GetExpRegValRange)(HGRABBER, long *, long *);
// typedef int AC (*IC_GetExpRegVal)(HGRABBER, long *);
// typedef int AC (*IC_SetExpRegVal)(HGRABBER, long);
// typedef int AC (*IC_EnableExpRegValAuto)(HGRABBER, int);
// typedef int AC (*IC_GetExpRegValAuto)(HGRABBER, int *);

// typedef int AC (*IC_IsExpAbsValAvailable)(HGRABBER);
// typedef int AC (*IC_GetExpAbsValRange)(HGRABBER, float *, float *);
// typedef int AC (*IC_GetExpAbsVal)(HGRABBER, float *);
// typedef int AC (*IC_SetExpAbsVal)(HGRABBER, float);

// typedef int AC (*IC_GetColorEnhancement)(HGRABBER, int *);
// typedef int AC (*IC_SetColorEnhancement)(HGRABBER, int);

// typedef int AC (*IC_SoftwareTrigger)(HGRABBER);
// typedef int AC (*IC_SetWhiteBalanceRed)(HGRABBER, long);
// typedef int AC (*IC_SetWhiteBalanceGreen)(HGRABBER, long);
// typedef int AC (*IC_SetWhiteBalanceBlue)(HGRABBER, long);

// typedef int AC (*IC_FocusOnePush)(HGRABBER);
// typedef int AC (*IC_enumProperties)(HGRABBER, IC_ENUMCB, void *);
// typedef int AC (*IC_printItemandElementNames)(HGRABBER);
// typedef int AC (*IC_enumPropertyElements)(HGRABBER, char *, IC_ENUMCB, void *);
// typedef int AC (*IC_enumPropertyElementInterfaces)(HGRABBER, char *, char *, IC_ENUMCB, void *);
// typedef int AC (*IC_IsPropertyAvailable)(HGRABBER, char *, char *);
// typedef int AC (*IC_GetPropertyValueRange)(HGRABBER, char *, char *, int *, int *);
// typedef int AC (*IC_GetPropertyValue)(HGRABBER, char *, char *, int *);
// typedef int AC (*IC_SetPropertyValue)(HGRABBER, char *, char *, int);
// typedef int AC (*IC_GetPropertyAbsoluteValueRange)(HGRABBER, char *, char *, float *, float *);
// typedef int AC (*IC_GetPropertyAbsoluteValue)(HGRABBER, char *, char *, float *);
// typedef int AC (*IC_SetPropertyAbsoluteValue)(HGRABBER, char *, char *, float);
// typedef int AC (*IC_GetPropertySwitch)(HGRABBER, char *, char *, int *);
// typedef int AC (*IC_SetPropertySwitch)(HGRABBER, char *, char *, int);
// typedef int AC (*IC_PropertyOnePush)(HGRABBER, char *, char *);

class TISGrabber : public Napi::ObjectWrap<TISGrabber>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    TISGrabber(const Napi::CallbackInfo &info);

private:
    // ~TISGrabber();
    static IC_InitLibrary IC_InitLibrary;
    static IC_CloseLibrary IC_CloseLibrary;
    static IC_CreateGrabber IC_CreateGrabber;
    static IC_ReleaseGrabber IC_ReleaseGrabber;
    static IC_GetDeviceCount IC_GetDeviceCount;
    static IC_GetUniqueNamefromList IC_GetUniqueNamefromList;
    static IC_OpenDevByUniqueName IC_OpenDevByUniqueName;
    static IC_ListVideoFormats IC_ListVideoFormats;
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
    LOAD_STATIC_METHOD(InitLibrary);
    LOAD_STATIC_METHOD(CloseLibrary);
    LOAD_STATIC_METHOD(CreateGrabber);
    LOAD_STATIC_METHOD(ReleaseGrabber);
    LOAD_STATIC_METHOD(GetDeviceCount);
    LOAD_STATIC_METHOD(GetUniqueNamefromList);
    LOAD_STATIC_METHOD(OpenDevByUniqueName);

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