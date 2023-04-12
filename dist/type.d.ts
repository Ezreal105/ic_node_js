export declare enum ICNodeResuleCode {
    SUCCESS = 1,
    ERROR = 0,
    NO_HANDLE = -1,
    NO_DEVICE = -2,
    NOT_AVAILABLE = -3,
    NO_PROPERTYSET = -3,
    DEFAULT_WINDOW_SIZE_SET = -3,
    NOT_IN_LIVEMODE = -3,
    PROPERTY_ITEM_NOT_AVAILABLE = -4,
    PROPERTY_ELEMENT_NOT_AVAILABLE = -5,
    PROPERTY_ELEMENT_WRONG_INTERFACE = -6,
    INDEX_OUT_OF_RANGE = -7,
    WRONG_XML_FORMAT = -1,
    WRONG_INCOMPATIBLE_XML = -3,
    NOT_ALL_PROPERTIES_RESTORED = -4,
    DEVICE_NOT_FOUND = -5,
    FILE_NOT_FOUND = 35
}
export declare enum ICNodeColorFormat {
    Y800 = 0,
    RGB24 = 1,
    RGB32 = 2,
    UYVY = 3,
    Y16 = 4,
    NONE = 5,
    COLORFORMAT_MEGA = 65536
}
export declare enum ICNodeImgFileType {
    FILETYPE_BMP = 0,
    FILETYPE_JPEG = 1,
    FILETYPE_MEGA = 65536
}
export declare enum ICNodeVideoProperty {
    PROP_VID_BRIGHTNESS = 0,
    PROP_VID_CONTRAST = 1,
    PROP_VID_HUE = 2,
    PROP_VID_SATURATION = 3,
    PROP_VID_SHARPNESS = 4,
    PROP_VID_GAMMA = 5,
    PROP_VID_COLORENABLE = 6,
    PROP_VID_WHITEBALANCE = 7,
    PROP_VID_BLACKLIGHTCOMPENSATION = 8,
    PROP_VID_GAIN = 9,
    PROP_VID_MEGA = 65536
}
export declare enum ICNodeCameraProperty {
    PROP_CAM_PAN = 0,
    PROP_CAM_TILT = 1,
    PROP_CAM_ROLL = 2,
    PROP_CAM_ZOOM = 3,
    PROP_CAM_EXPOSURE = 4,
    PROP_CAM_IRIS = 5,
    PROP_CAM_FOCUS = 6,
    PROP_CAM_MEGA = 65536
}
export type ICNodeResult<T = undefined> = {
    code: ICNodeResuleCode;
    data?: T;
    message?: string;
};
export type ICNodeGrabber = object;
export type ICNodeImageBuffer = object;
export type ICNodeVideoFormat = string;
export type ICNodeVideoNorm = string;
export type ICNodeInputChannel = string;
export type ICNodeTriggerMode = string;
export type ICNodeTriggerPolarity = number;
export type ICNodeSwitch = boolean;
export type ICNodePropertyRange = {
    min: number;
    max: number;
};
type MillSecond = number;
export type ICNodeImageDescriptionBase = {
    width: number;
    height: number;
    bitsPerPixel: number;
};
export type ICNodeImageDescriptionWithFormat = ICNodeImageDescriptionBase & {
    format: ICNodeColorFormat;
};
export type ICNodeFrameReadyCallback = {
    (grabber: ICNodeGrabber, buffer: ICNodeImageBuffer, frameNumber: number): void;
};
export type ICNodeDeviceLostCallback = {
    (grabber: ICNodeGrabber): void;
};
export type ICNodeEnumCallback<T = string> = {
    (data: T): void;
};
export type ICNodeStatic = {
    IC_InitLibrary(szLicenseKey: string): ICNodeResult;
    IC_CreateGrabber(): ICNodeResult<ICNodeGrabber>;
    IC_ReleaseGrabber(grabber: ICNodeGrabber): ICNodeResult;
    IC_TidyUP(): ICNodeResult;
    IC_CloseLibrary(): ICNodeResult;
    IC_CloseVideoCaptureDevice(grabber: ICNodeGrabber): ICNodeResult;
    IC_GetDeviceName(grabber: ICNodeGrabber): ICNodeResult<string>;
    IC_GetVideoFormatWidth(grabber: ICNodeGrabber): ICNodeResult<number>;
    IC_GetVideoFormatHeight(grabber: ICNodeGrabber): ICNodeResult<number>;
    IC_SetFormat(grabber: ICNodeGrabber, format: ICNodeColorFormat): ICNodeResult;
    IC_GetFormat(grabber: ICNodeGrabber): ICNodeResult<ICNodeColorFormat>;
    IC_SetVideoFormat(grabber: ICNodeGrabber, format: ICNodeVideoFormat): ICNodeResult;
    IC_SetVideoNorm(grabber: ICNodeGrabber, norm: ICNodeVideoNorm): ICNodeResult;
    IC_SetInputChannel(grabber: ICNodeGrabber, channel: ICNodeInputChannel): ICNodeResult;
    IC_PrepareLive(grabber: ICNodeGrabber, show: ICNodeSwitch): ICNodeResult;
    IC_SuspendLive(grabber: ICNodeGrabber): ICNodeResult;
    IC_IsLive(grabber: ICNodeGrabber): ICNodeResult<boolean>;
    IC_StopLive(grabber: ICNodeGrabber): ICNodeResult;
    IC_IsCameraPropertyAvailable(grabber: ICNodeGrabber, property: ICNodeCameraProperty): ICNodeResult<boolean>;
    IC_SetCameraProperty(grabber: ICNodeGrabber, property: ICNodeCameraProperty, value: number): ICNodeResult;
    IC_CameraPropertyGetRange(grabber: ICNodeGrabber, property: ICNodeCameraProperty): ICNodeResult<ICNodePropertyRange>;
    IC_GetCameraProperty(grabber: ICNodeGrabber, property: ICNodeCameraProperty): ICNodeResult<number>;
    IC_EnableAutoCameraProperty(grabber: ICNodeGrabber, property: ICNodeCameraProperty, onOff: ICNodeSwitch): ICNodeResult;
    IC_IsCameraPropertyAutoAvailable(grabber: ICNodeGrabber, property: ICNodeCameraProperty): ICNodeResult<boolean>;
    IC_GetAutoCameraProperty(grabber: ICNodeGrabber, property: ICNodeCameraProperty): ICNodeResult<boolean>;
    IC_IsVideoPropertyAvailable(grabber: ICNodeGrabber, property: ICNodeVideoProperty): ICNodeResult<boolean>;
    IC_VideoPropertyGetRange(grabber: ICNodeGrabber, property: ICNodeVideoProperty): ICNodeResult<ICNodePropertyRange>;
    IC_GetVideoProperty(grabber: ICNodeGrabber, property: ICNodeVideoProperty): ICNodeResult<number>;
    IC_IsVideoPropertyAutoAvailable(grabber: ICNodeGrabber, property: ICNodeVideoProperty): ICNodeResult<boolean>;
    IC_GetAutoVideoProperty(grabber: ICNodeGrabber, property: ICNodeVideoProperty): ICNodeResult<boolean>;
    IC_SetVideoProperty(grabber: ICNodeGrabber, property: ICNodeVideoProperty, value: number): ICNodeResult;
    IC_EnableAutoVideoProperty(grabber: ICNodeGrabber, property: ICNodeVideoProperty, onOff: ICNodeSwitch): ICNodeResult;
    IC_GetImageDescription(grabber: ICNodeGrabber): ICNodeResult<ICNodeImageDescriptionWithFormat>;
    IC_SnapImage(grabber: ICNodeGrabber, timeout: MillSecond): ICNodeResult;
    IC_SaveImage(grabber: ICNodeGrabber, fileName: string, fileType: ICNodeImgFileType, quality?: number): ICNodeResult;
    IC_GetSerialNumber(grabber: ICNodeGrabber): ICNodeResult<string>;
    IC_GetDeviceCount(): ICNodeResult<number>;
    IC_GetDevice(index: number): ICNodeResult<string>;
    IC_GetUniqueNamefromList(index: number): ICNodeResult<string>;
    IC_GetInputChannelCount(grabber: ICNodeGrabber): ICNodeResult<number>;
    IC_GetInputChannel(grabber: ICNodeGrabber, index: number): ICNodeResult<ICNodeInputChannel>;
    IC_GetVideoNormCount(grabber: ICNodeGrabber): ICNodeResult<number>;
    IC_GetVideoNorm(grabber: ICNodeGrabber, index: number): ICNodeResult<ICNodeVideoNorm>;
    IC_GetVideoFormatCount(grabber: ICNodeGrabber): ICNodeResult<number>;
    IC_GetVideoFormat(grabber: ICNodeGrabber, index: number): ICNodeResult<ICNodeVideoFormat>;
    IC_SaveDeviceStateToFile(grabber: ICNodeGrabber, fileName: string): ICNodeResult;
    IC_LoadDeviceStateFromFileEx(grabber: ICNodeGrabber, fileName: string, openDevice: ICNodeSwitch): ICNodeResult;
    IC_SaveDeviceSettings(grabber: ICNodeGrabber, fileName: string): ICNodeResult;
    IC_OpenDeviceBySettings(grabber: ICNodeGrabber, fileName: string): ICNodeResult;
    IC_LoadDeviceSettings(grabber: ICNodeGrabber, fileName: string): ICNodeResult;
    IC_OpenDevByDisplayName(grabber: ICNodeGrabber, displayName: string): ICNodeResult;
    IC_GetDisplayName(grabber: ICNodeGrabber): ICNodeResult<string>;
    IC_OpenDevByUniqueName(grabber: ICNodeGrabber, uniqueName: string): ICNodeResult;
    IC_GetUniqueName(grabber: ICNodeGrabber): ICNodeResult<string>;
    IC_IsDevValid(grabber: ICNodeGrabber): ICNodeResult<boolean>;
    IC_ShowPropertyDialog(grabber: ICNodeGrabber): ICNodeResult;
    IC_ShowDeviceSelectionDialog(grabber: ICNodeGrabber): ICNodeResult<ICNodeGrabber>;
    IC_IsTriggerAvailable(grabber: ICNodeGrabber): ICNodeResult<boolean>;
    IC_EnableTrigger(grabber: ICNodeGrabber, onOff: ICNodeSwitch): ICNodeResult;
    IC_MsgBox(message: string, title: string): ICNodeResult;
    IC_SetFrameReadyCallbackEx(grabber: ICNodeGrabber, callback: ICNodeFrameReadyCallback): ICNodeResult;
    IC_SetDeviceLostCallback(grabber: ICNodeGrabber, callback: ICNodeDeviceLostCallback): ICNodeResult;
    IC_SetContinuousMode(grabber: ICNodeGrabber, onOff: ICNodeSwitch): ICNodeResult;
    IC_SetFrameRate(grabber: ICNodeGrabber, frameRate: number): ICNodeResult;
    IC_GetFrameRate(grabber: ICNodeGrabber): ICNodeResult<number>;
    IC_GetAvailableFrameRates(grabber: ICNodeGrabber): ICNodeResult<number[]>;
    IC_SetWhiteBalanceAuto(grabber: ICNodeGrabber, onOff: ICNodeSwitch): ICNodeResult;
    IC_SignalDetected(grabber: ICNodeGrabber): ICNodeResult<boolean>;
    IC_GetTriggerModes(grabber: ICNodeGrabber): ICNodeResult<ICNodeTriggerMode[]>;
    IC_SetTriggerMode(grabber: ICNodeGrabber, mode: ICNodeTriggerMode): ICNodeResult;
    IC_SetTriggerPolarity(grabber: ICNodeGrabber, polarity: ICNodeTriggerPolarity): ICNodeResult;
    IC_GetExpRegValRange(grabber: ICNodeGrabber): ICNodeResult<ICNodePropertyRange>;
    IC_GetExpRegVal(grabber: ICNodeGrabber): ICNodeResult<number>;
    IC_SetExpRegVal(grabber: ICNodeGrabber, value: number): ICNodeResult;
    IC_EnableExpRegValAuto(grabber: ICNodeGrabber, onOff: ICNodeSwitch): ICNodeResult;
    IC_GetExpRegValAuto(grabber: ICNodeGrabber): ICNodeResult<boolean>;
    IC_IsExpAbsValAvailable(grabber: ICNodeGrabber): ICNodeResult<boolean>;
    IC_GetExpAbsValRange(grabber: ICNodeGrabber): ICNodeResult<ICNodePropertyRange>;
    IC_GetExpAbsVal(grabber: ICNodeGrabber): ICNodeResult<number>;
    IC_SetExpAbsVal(grabber: ICNodeGrabber, value: number): ICNodeResult;
    IC_GetColorEnhancement(grabber: ICNodeGrabber): ICNodeResult<boolean>;
    IC_SetColorEnhancement(grabber: ICNodeGrabber, onOff: ICNodeSwitch): ICNodeResult;
    IC_SoftwareTrigger(grabber: ICNodeGrabber): ICNodeResult;
    IC_SetWhiteBalanceRed(grabber: ICNodeGrabber, value: number): ICNodeResult;
    IC_SetWhiteBalanceGreen(grabber: ICNodeGrabber, value: number): ICNodeResult;
    IC_SetWhiteBalanceBlue(grabber: ICNodeGrabber, value: number): ICNodeResult;
    IC_FocusOnePush(grabber: ICNodeGrabber): ICNodeResult;
    IC_enumProperties(grabber: ICNodeGrabber, cb: ICNodeEnumCallback): ICNodeResult;
    IC_enumPropertyElements(grabber: ICNodeGrabber, property: string, cb: ICNodeEnumCallback): ICNodeResult;
    IC_enumPropertyElementInterfaces(grabber: ICNodeGrabber, property: string, element: string, cb: ICNodeEnumCallback): ICNodeResult;
    IC_IsPropertyAvailable(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult<boolean>;
    IC_GetPropertyValueRange(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult<ICNodePropertyRange>;
    IC_GetPropertyValue(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult<number>;
    IC_SetPropertyValue(grabber: ICNodeGrabber, property: string, element: string, value?: number): ICNodeResult;
    IC_GetPropertyAbsoluteValueRange(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult<ICNodePropertyRange>;
    IC_GetPropertyAbsoluteValue(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult<number>;
    IC_SetPropertyAbsoluteValue(grabber: ICNodeGrabber, property: string, element: string, value?: number): ICNodeResult;
    IC_GetPropertySwitch(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult<ICNodeSwitch>;
    IC_SetPropertySwitch(grabber: ICNodeGrabber, property: string, element: string, value?: boolean): ICNodeResult;
    IC_PropertyOnePush(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult;
    IC_GetPropertyMapStrings(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult<string[]>;
    IC_GetPropertyMapString(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult<string>;
    IC_SetPropertyMapString(grabber: ICNodeGrabber, property: string, element: string, value?: string): ICNodeResult;
    IC_ResetProperties(grabber: ICNodeGrabber): ICNodeResult;
    IC_SetRingBufferSize(grabber: ICNodeGrabber, size: number): ICNodeResult;
    IC_GetRingBufferSize(grabber: ICNodeGrabber): ICNodeResult<number>;
    IC_GetMemBuffer(grabber: ICNodeGrabber, index: number): ICNodeResult<ICNodeImageBuffer>;
    IC_GetMemBufferLastAcq(grabber: ICNodeGrabber): ICNodeResult<ICNodeImageBuffer>;
    IC_GetMemBufferDescription(imgBuffer: ICNodeImageBuffer): ICNodeResult<ICNodeImageDescriptionBase>;
    IC_MemBufferLock(imgBuffer: ICNodeImageBuffer, lock: ICNodeSwitch): ICNodeResult;
    IC_MemBufferisLocked(imgBuffer: ICNodeImageBuffer): ICNodeResult<boolean>;
    IC_MemBufferGetIndex(imgBuffer: ICNodeImageBuffer): ICNodeResult<number>;
    IC_ReleaseMemBuffer(imgBuffer: ICNodeImageBuffer): ICNodeResult;
    IC_MemBufferGetData(imgBuffer: ICNodeImageBuffer): ICNodeResult<Uint8Array>;
};
export type ICGrabberInitOptions = {
    licenseKey?: string;
    deviceUniqueName: string;
    /**
     * @default true
     */
    autoOpenDevice?: boolean;
};
export type DevicePreviewInfo = {
    displayName: string;
    uniqueName: string;
};
export type ICNodeSwitchPropertyElement = ['Trigger', 'Enable'];
export type ICNodeButtonPropertyElement = ['Trigger', 'Software Trigger'];
export type ICNodeRangePropertyElement = ['Brightness', 'Value'];
export type ICNodePropertyElement = ICNodeSwitchPropertyElement | ICNodeButtonPropertyElement | ICNodeRangePropertyElement;
/**
 * 设备的固有属性
 */
export type DeviceMeta = DevicePreviewInfo & {
    serialNumber: string;
    supprotedVideoFormats: ICNodeVideoFormat[];
    supprotedVideoNorms: ICNodeVideoNorm[];
    supportedInputChannels: ICNodeInputChannel[];
    supportedFrameRates: number[];
    supportSoftwareTrigger: boolean;
    supportBrightness: boolean;
    supportAutoBrightness: boolean;
    brightnessRange: ICNodePropertyRange | null;
    supportContrast: boolean;
    supportAutoContrast: boolean;
    contrastRange: ICNodePropertyRange | null;
    supportExposure: boolean;
    supportAutoExposure: boolean;
    exposureRange: ICNodePropertyRange | null;
    supportGain: boolean;
    supportAutoGain: boolean;
    gainRange: ICNodePropertyRange | null;
    supportSharpness: boolean;
    supportAutoSharpness: boolean;
    sharpnessRange: ICNodePropertyRange | null;
    supportGamma: boolean;
    supportAutoGamma: boolean;
    gammaRange: ICNodePropertyRange | null;
    supportWhiteBalance: boolean;
    supportAutoWhiteBalance: boolean;
    whiteBalanceRange: ICNodePropertyRange | null;
    supportZoom: boolean;
    supportAutoZoom: boolean;
    zoomRange: ICNodePropertyRange | null;
    supportFocus: boolean;
    supportAutoFocus: boolean;
    focusRange: ICNodePropertyRange | null;
    supportIris: boolean;
    supportAutoIris: boolean;
    irisRange: ICNodePropertyRange | null;
    supportSaturation: boolean;
    supportAutoSaturation: boolean;
    saturationRange: ICNodePropertyRange | null;
    supportHue: boolean;
    supportAutoHue: boolean;
    hueRange: ICNodePropertyRange | null;
    supportBacklightCompensation: boolean;
};
export type ICNodeImageFileFormat = 'bmp' | 'jpg' | 'tiff';
export type ICGrabberState = {
    device: DeviceMeta | null;
    videoFormat: ICNodeVideoFormat;
    videoNorm: ICNodeVideoNorm | null;
    inputChannel: ICNodeInputChannel | null;
    continuousCaptureRunning: boolean;
    continuousCaptureInterval: number;
    continuousCaptureImageFormat: ICNodeImageFileFormat;
    continuousCaptureImageQuality: number;
    continuousCaptureImageSavePath: string;
    brightness: number;
    frameRate: number;
};
export {};
