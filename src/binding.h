#ifndef _TISGRABBER
#define _TISGRABBER
#ifdef _WIN32
#define AC __stdcall
#define CDECL __cdecl
typedef int __cdecl IC_ENUMCB(char *Name, void *);
typedef int cdecl ENUMCODECCB(char *CodecName, void *);
#else
#define AC __attribute__((stdcall))
#define CDECL __attribute__((cdecl))
typedef int __attribute__((cdecl)) IC_ENUMCB(char *Name, void *);
typedef int __attribute__((cdecl)) ENUMCODECCB(char *CodecName, void *);
#endif
#ifndef _WINUSER_
#define NOHWNDDEFINED 1
#define __HWND int
#else
#define __HWND HWND
#endif
typedef enum
{
	FILETYPE_BMP,
	FILETYPE_JPEG,
	FILETYPE_MEGA = 65536
} IMG_FILETYPE;
typedef enum
{
	Y800,
	RGB24,
	RGB32,
	UYVY,
	Y16,
	NONE,
	COLORFORMAT_MEGA = 65536
} COLORFORMAT;
typedef enum
{
	PROP_VID_BRIGHTNESS = 0,
	PROP_VID_CONTRAST,
	PROP_VID_HUE,
	PROP_VID_SATURATION,
	PROP_VID_SHARPNESS,
	PROP_VID_GAMMA,
	PROP_VID_COLORENABLE,
	PROP_VID_WHITEBALANCE,
	PROP_VID_BLACKLIGHTCOMPENSATION,
	PROP_VID_GAIN,
	PROP_VID_MEGA = 65536
} VIDEO_PROPERTY;
typedef enum
{
	PROP_CAM_PAN = 0,
	PROP_CAM_TILT,
	PROP_CAM_ROLL,
	PROP_CAM_ZOOM,
	PROP_CAM_EXPOSURE,
	PROP_CAM_IRIS,
	PROP_CAM_FOCUS,
	PROP_CAM_MEGA = 65536
} CAMERA_PROPERTY;
typedef enum
{
	eParamLong,
	eParamBoolean,
	eParamFloat,
	eParamString,
	eParamData
} FRAMEFILTER_PARAM_TYPE;
typedef enum
{
	ePropertyRange,
	ePropertyAbsoluteValue,
	ePropertySwitch,
	ePropertyButton,
	ePropertyMapStrings,
	ePropertyUnknown
} PROPERTY_INTERFACE_TYPE;
typedef struct HGRABBER_t__
{
	int unused;
} HGRABBER_t;
#define HGRABBER HGRABBER_t *
struct ImageBuffer;
typedef struct ImageBuffer *HMEMBUFFER;

typedef struct FILTERPARAMETER_t__
{
	char Name[30];
	FRAMEFILTER_PARAM_TYPE Type;
} FILTERPARAMETER_t;
typedef struct HFRAMEFILTER_t__
{
	void *pFilter;
	int bHasDialog;
	int ParameterCount;
	FILTERPARAMETER_t *Parameters;
} HFRAMEFILTER_t;
#define HFRAMEFILTER HFRAMEFILTER_t
typedef struct CODECHANDLE_t__
{
	int unused;
} CODECHANDLE_t;
#define HCODEC CODECHANDLE_t *
#define IC_SUCCESS 1
#define IC_ERROR 0
#define IC_NO_HANDLE -1
#define IC_NO_DEVICE -2
#define IC_NOT_AVAILABLE -3
#define IC_NO_PROPERTYSET -3
#define IC_DEFAULT_WINDOW_SIZE_SET -3
#define IC_NOT_IN_LIVEMODE -3
#define IC_PROPERTY_ITEM_NOT_AVAILABLE -4
#define IC_PROPERTY_ELEMENT_NOT_AVAILABLE -5
#define IC_PROPERTY_ELEMENT_WRONG_INTERFACE -6
#define IC_INDEX_OUT_OF_RANGE -7
#define IC_WRONG_XML_FORMAT -1
#define IC_WRONG_INCOMPATIBLE_XML -3
#define IC_NOT_ALL_PROPERTIES_RESTORED -4
#define IC_DEVICE_NOT_FOUND -5
#define IC_FILE_NOT_FOUND 35
#if defined(__cplusplus)
extern "C"
{
#endif
	typedef void (*FRAME_READY_CALLBACK)(HGRABBER hGrabber, unsigned char *pData, unsigned long frameNumber, void *);
	typedef void (*DEVICE_LOST_CALLBACK)(HGRABBER hGrabber, void *);
	typedef void (*FRAME_READY_CALLBACK_EX)(HGRABBER hGrabber, HMEMBUFFER hBuffer, unsigned long frameNumber, void *);
	typedef int AC IC_InitLibrary(char *szLicenseKey);
	typedef HGRABBER AC IC_CreateGrabber();
	typedef void AC IC_ReleaseGrabber(HGRABBER *hGrabber);
	typedef void AC IC_TidyUP();
	typedef void AC IC_CloseLibrary();
	typedef int AC IC_OpenVideoCaptureDevice(HGRABBER hGrabber, char *szDeviceName);
	typedef void AC IC_CloseVideoCaptureDevice(HGRABBER hGrabber);
	typedef char *AC IC_GetDeviceName(HGRABBER hGrabber);
	typedef int AC IC_GetVideoFormatWidth(HGRABBER hGrabber);
	typedef int AC IC_GetVideoFormatHeight(HGRABBER hGrabber);
	typedef int AC IC_SetFormat(HGRABBER hGrabber, COLORFORMAT format);
	typedef COLORFORMAT AC IC_GetFormat(HGRABBER hGrabber);
	typedef int AC IC_SetVideoFormat(HGRABBER hGrabber, char *szFormat);
	typedef int AC IC_SetVideoNorm(HGRABBER hGrabber, char *szNorm);
	typedef int AC IC_SetInputChannel(HGRABBER hGrabber, char *szChannel);
	typedef int AC IC_StartLive(HGRABBER hGrabber, int iShow);
	typedef int AC IC_PrepareLive(HGRABBER hGrabber, int iShow);
	typedef int AC IC_SuspendLive(HGRABBER hGrabber);
	typedef int AC IC_IsLive(HGRABBER hGrabber);
	typedef void AC IC_StopLive(HGRABBER hGrabber);
	typedef int AC IC_IsCameraPropertyAvailable(HGRABBER hGrabber, CAMERA_PROPERTY eProperty);
	typedef int AC IC_SetCameraProperty(HGRABBER hGrabber, CAMERA_PROPERTY eProperty, long lValue);
	typedef int AC IC_CameraPropertyGetRange(HGRABBER hGrabber, CAMERA_PROPERTY eProperty, long *lMin, long *lMax);
	typedef int AC IC_GetCameraProperty(HGRABBER hGrabber, CAMERA_PROPERTY eProperty, long *lValue);
	typedef int AC IC_EnableAutoCameraProperty(HGRABBER hGrabber, int iProperty, int iOnOff);
	typedef int AC IC_IsCameraPropertyAutoAvailable(HGRABBER hGrabber, CAMERA_PROPERTY iProperty);
	typedef int AC IC_GetAutoCameraProperty(HGRABBER hGrabber, int iProperty, int *iOnOff);
	typedef int AC IC_IsVideoPropertyAvailable(HGRABBER hGrabber, VIDEO_PROPERTY eProperty);
	typedef int AC IC_VideoPropertyGetRange(HGRABBER hGrabber, VIDEO_PROPERTY eProperty, long *lMin, long *lMax);
	typedef int AC IC_GetVideoProperty(HGRABBER hGrabber, VIDEO_PROPERTY eProperty, long *lValue);
	typedef int AC IC_IsVideoPropertyAutoAvailable(HGRABBER hGrabber, VIDEO_PROPERTY eProperty);
	typedef int AC IC_GetAutoVideoProperty(HGRABBER hGrabber, int iProperty, int *iOnOff);
	typedef int AC IC_SetVideoProperty(HGRABBER hGrabber, VIDEO_PROPERTY eProperty, long lValue);
	typedef int AC IC_EnableAutoVideoProperty(HGRABBER hGrabber, int iProperty, int iOnOff);
	typedef int AC IC_GetImageDescription(HGRABBER hGrabber, long *lWidth, long *lHeight, int *iBitsPerPixel, COLORFORMAT *format);
	typedef int AC IC_SnapImage(HGRABBER hGrabber, int iTimeOutMillisek);
	typedef int AC IC_SaveImage(HGRABBER hGrabber, char *szFileName, IMG_FILETYPE ft, long quality);
	typedef unsigned char *AC IC_GetImagePtr(HGRABBER hGrabber);
	typedef int AC IC_SetHWnd(HGRABBER hGrabber, __HWND hWnd);
	typedef int AC IC_GetSerialNumber(HGRABBER hGrabber, char *szSerial);
	typedef int AC IC_ListDevices(char *szDeviceList, int iSize);
	typedef int AC IC_ListDevicesbyIndex(char *szDeviceName, int iSize, int DeviceIndex);
	typedef int AC IC_ListVideoFormats(HGRABBER hGrabber, char *szFormatList, int iSize);
	typedef int AC IC_ListVideoFormatbyIndex(HGRABBER hGrabber, char *szFormatName, int iSize, int iIndex);
	typedef int AC IC_GetDeviceCount();
	typedef char *AC IC_GetDevice(int iIndex);
	typedef char *AC IC_GetUniqueNamefromList(int iIndex);
	typedef int AC IC_GetInputChannelCount(HGRABBER hGrabber);
	typedef char *AC IC_GetInputChannel(HGRABBER hGrabber, int iIndex);
	typedef int AC IC_GetVideoNormCount(HGRABBER hGrabber);
	typedef char *AC IC_GetVideoNorm(HGRABBER hGrabber, int iIndex);
	typedef int AC IC_GetVideoFormatCount(HGRABBER hGrabber);
	typedef char *AC IC_GetVideoFormat(HGRABBER hGrabber, int iIndex);
	typedef int AC IC_SaveDeviceStateToFile(HGRABBER hGrabber, char *szFileName);
	typedef HGRABBER AC IC_LoadDeviceStateFromFile(HGRABBER hGrabber, char *szFileName);
	typedef int AC IC_LoadDeviceStateFromFileEx(HGRABBER hGrabber, char *szFileName, int OpenDevice);
	typedef int AC IC_SaveDeviceSettings(HGRABBER hGrabber, char *szFilename);
	typedef int AC IC_OpenDeviceBySettings(HGRABBER hGrabber, char *szFilename);
	typedef int AC IC_LoadDeviceSettings(HGRABBER hGrabber, char *szFilename);
	typedef int AC IC_OpenDevByDisplayName(HGRABBER hGrabber, char *szDisplayname);
	typedef int AC IC_GetDisplayName(HGRABBER hGrabber, char *szDisplayname, int iLen);
	typedef int AC IC_OpenDevByUniqueName(HGRABBER hGrabber, char *szDisplayname);
	typedef int AC IC_GetUniqueName(HGRABBER hGrabber, char *szUniquename, int iLen);
	typedef int AC IC_IsDevValid(HGRABBER hGrabber);
	typedef int AC IC_ShowPropertyDialog(HGRABBER hGrabber);
	typedef HGRABBER AC IC_ShowDeviceSelectionDialog(HGRABBER hGrabber);
	typedef int AC IC_IsTriggerAvailable(HGRABBER hGrabber);
	typedef int AC IC_EnableTrigger(HGRABBER hGrabber, int iEnable);
	typedef void AC IC_RemoveOverlay(HGRABBER hGrabber, int iEnable);
	typedef void AC IC_EnableOverlay(HGRABBER hGrabber, int iEnable);
	typedef long AC IC_BeginPaint(HGRABBER hGrabber);
	typedef void AC IC_EndPaint(HGRABBER hGrabber);
	typedef void AC IC_MsgBox(char *szText, char *szTitle);
	typedef int AC IC_SetFrameReadyCallbackEx(
			HGRABBER hGrabber,
			FRAME_READY_CALLBACK_EX cb,
			void *x1_argument_in_void_userdata);
	typedef int AC IC_SetFrameReadyCallback(
			HGRABBER hGrabber,
			FRAME_READY_CALLBACK cb,
			void *x1_argument_in_void_userdata);
	typedef int AC IC_SetCallbacks(
			HGRABBER hGrabber,
			FRAME_READY_CALLBACK cb,
			void *x1_argument_in_void_userdata,
			DEVICE_LOST_CALLBACK dlCB,
			void *x2_argument_in_void_userdata);
	typedef int AC IC_SetContinuousMode(HGRABBER hGrabber, int cont);
	typedef int AC IC_SetFrameRate(HGRABBER hGrabber, float FrameRate);
	typedef float AC IC_GetFrameRate(HGRABBER hGrabber);
	typedef int AC IC_GetAvailableFrameRates(HGRABBER hGrabber, int Index, float *fps);
	typedef int AC IC_ShowInternalPropertyPage(HGRABBER hGrabber);
	typedef int AC IC_ResetUSBCam(HGRABBER hGrabber);
	typedef int AC IC_QueryPropertySet(HGRABBER hGrabber);
	typedef int AC IC_SetDefaultWindowPosition(HGRABBER hGrabber, int Default);
	typedef int AC IC_SetWindowPosition(HGRABBER hGrabber, int PosX, int PosY, int Width, int Height);
	typedef int AC IC_GetWindowPosition(HGRABBER hGrabber, int *PosX, int *PosY, int *Width, int *Height);
	typedef int AC IC_SetWhiteBalanceAuto(HGRABBER hGrabber, int iOnOff);
	typedef int AC IC_SignalDetected(HGRABBER hGrabber);
	typedef int AC IC_GetTriggerModes(HGRABBER hGrabber, char *szModeList, int iSize);
	typedef int AC IC_SetTriggerMode(HGRABBER hGrabber, char *szMode);
	typedef int AC IC_SetTriggerPolarity(HGRABBER hGrabber, int iPolarity);
	typedef int AC IC_GetExpRegValRange(HGRABBER hGrabber, long *lMin, long *lMax);
	typedef int AC IC_GetExpRegVal(HGRABBER hGrabber, long *lValue);
	typedef int AC IC_SetExpRegVal(HGRABBER hGrabber, long lValue);
	typedef int AC IC_EnableExpRegValAuto(HGRABBER hGrabber, int iOnOff);
	typedef int AC IC_GetExpRegValAuto(HGRABBER hGrabber, int *iOnOff);
	typedef int AC IC_IsExpAbsValAvailable(HGRABBER hGrabber);
	typedef int AC IC_GetExpAbsValRange(HGRABBER hGrabber, float *fMin, float *fMax);
	typedef int AC IC_GetExpAbsVal(HGRABBER hGrabber, float *fValue);
	typedef int AC IC_SetExpAbsVal(HGRABBER hGrabber, float fValue);
	typedef int AC IC_GetColorEnhancement(HGRABBER hGrabber, int *OnOff);
	typedef int AC IC_SetColorEnhancement(HGRABBER hGrabber, int OnOff);
	typedef int AC IC_SoftwareTrigger(HGRABBER hGrabber);
	typedef int AC IC_SetWhiteBalanceRed(HGRABBER hGrabber, long Value);
	typedef int AC IC_SetWhiteBalanceGreen(HGRABBER hGrabber, long Value);
	typedef int AC IC_SetWhiteBalanceBlue(HGRABBER hGrabber, long Value);
	typedef int AC IC_FocusOnePush(HGRABBER hGrabber);
	typedef int AC IC_enumProperties(HGRABBER hGrabber, IC_ENUMCB cb, void *data);
	typedef int AC IC_printItemandElementNames(HGRABBER hGrabber);
	typedef int AC IC_enumPropertyElements(HGRABBER hGrabber, char *Property, IC_ENUMCB cb, void *data);
	typedef int AC IC_enumPropertyElementInterfaces(HGRABBER hGrabber, char *Property, char *Element, IC_ENUMCB cb, void *data);
	typedef int AC IC_IsPropertyAvailable(HGRABBER hGrabber, char *Property, char *Element);
	typedef int AC IC_GetPropertyValueRange(HGRABBER hGrabber, char *Property, char *Element, int *Min, int *Max);
	typedef int AC IC_GetPropertyValue(HGRABBER hGrabber, char *Property, char *Element, int *Value);
	typedef int AC IC_SetPropertyValue(HGRABBER hGrabber, char *Property, char *Element, int Value);
	typedef int AC IC_GetPropertyAbsoluteValueRange(HGRABBER hGrabber, char *Property, char *Element, float *Min, float *Max);
	typedef int AC IC_GetPropertyAbsoluteValue(HGRABBER hGrabber, char *Property, char *Element, float *Value);
	typedef int AC IC_SetPropertyAbsoluteValue(HGRABBER hGrabber, char *Property, char *Element, float Value);
	typedef int AC IC_GetPropertySwitch(HGRABBER hGrabber, char *Property, char *Element, int *On);
	typedef int AC IC_SetPropertySwitch(HGRABBER hGrabber, char *Property, char *Element, int On);
	typedef int AC IC_PropertyOnePush(HGRABBER hGrabber, char *Property, char *Element);
	typedef int AC IC_GetPropertyMapStrings(HGRABBER hGrabber, char *Property, char *Element, int *StringCount, int *StringMaxLength, char **Strings);
	typedef int AC IC_GetPropertyMapString(HGRABBER hGrabber, char *Property, char *Element, int *StringLength, char *String);
	typedef int AC IC_SetPropertyMapString(HGRABBER hGrabber, char *Property, char *Element, char *String);
	typedef int AC IC_ResetProperties(HGRABBER hGrabber);
	typedef int AC IC_GetAvailableFrameFilterCount();
	typedef int AC IC_GetAvailableFrameFilters(char **szFilterList, int iSize);
	typedef int AC IC_CreateFrameFilter(char *szFilterName, HFRAMEFILTER *FilterHandle);
	typedef int AC IC_AddFrameFilterToDevice(HGRABBER hGrabber, HFRAMEFILTER FilterHandle);
	typedef void AC IC_RemoveFrameFilterFromDevice(HGRABBER hGrabber, HFRAMEFILTER FilterHandle);
	typedef void AC IC_DeleteFrameFilter(HFRAMEFILTER FilterHandle);
	typedef int AC IC_FrameFilterShowDialog(HFRAMEFILTER FilterHandle);
	typedef int AC IC_FrameFilterGetParameter(HFRAMEFILTER FilterHandle, char *ParameterName, void *Data);
	typedef int AC IC_FrameFilterSetParameterInt(HFRAMEFILTER FilterHandle, char *ParameterName, int Data);
	typedef int AC IC_FrameFilterSetParameterFloat(HFRAMEFILTER FilterHandle, char *ParameterName, float Data);
	typedef int AC IC_FrameFilterSetParameterBoolean(HFRAMEFILTER FilterHandle, char *ParameterName, int Data);
	typedef int AC IC_FrameFilterSetParameterString(HFRAMEFILTER FilterHandle, char *ParameterName, char *Data);
	typedef int AC IC_FrameFilterDeviceClear(HGRABBER hGrabber);
	typedef void AC IC_enumCodecs(ENUMCODECCB cb, void *data);
	typedef HCODEC IC_Codec_Create(char *Name);
	typedef void AC IC_Codec_Release(HCODEC Codec);
	typedef int AC IC_Codec_getName(HCODEC Codec, int l, char *Name);
	typedef int AC IC_Codec_hasDialog(HCODEC Codec);
	typedef int AC IC_Codec_showDialog(HCODEC Codec);
	typedef int AC IC_SetCodec(HGRABBER hlGrabber, HCODEC Codec);
	typedef int IC_SetAVIFileName(HGRABBER hlGrabber, char *FileName);
	typedef int IC_enableAVICapturePause(HGRABBER hlGrabber, int Pause);
	typedef int AC IC_SetRingBufferSize(HGRABBER hGrabber, int Count);
	typedef int AC IC_GetRingBufferSize(HGRABBER hGrabber, int *pCount);
	typedef int AC IC_GetMemBuffer(HGRABBER hGrabber, int Index, HMEMBUFFER *pBuffer);
	typedef int AC IC_GetMemBufferLastAcq(HGRABBER hGrabber, HMEMBUFFER *pBuffer);
	typedef void AC IC_ReleaseMemBuffer(HMEMBUFFER *pBuffer);
	typedef int AC IC_GetMemBufferDescription(HMEMBUFFER hBuffer, int *pWidth, int *pHeight, int *pBitsPerPixel);
	typedef int AC IC_MemBufferLock(HMEMBUFFER hBuffer, int lock);
	typedef int AC IC_MemBufferisLocked(HMEMBUFFER hBuffer, int *plocked);
	typedef int AC IC_MemBufferGetIndex(HMEMBUFFER hBuffer, int *pIndex);
	typedef int AC IC_MemBufferGetDataPtr(HMEMBUFFER hBuffer, unsigned char **pData);
#if defined(__cplusplus)
}
#endif
#endif
