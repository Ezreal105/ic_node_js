export enum ICNodeResuleCode {
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
  FILE_NOT_FOUND = 35,
}

export enum ICNodeColorFormat {
  Y800 = 0,
  RGB24,
  RGB32,
  UYVY,
  Y16,
  NONE,
  COLORFORMAT_MEGA = 65536,
}

export enum ICNodeImgFileType {
  FILETYPE_BMP = 0,
  FILETYPE_JPEG,
  FILETYPE_MEGA = 65536,
}

export enum ICNodeVideoProperty {
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
  PROP_VID_MEGA = 65536,
}

export enum ICNodeCameraProperty {
  PROP_CAM_PAN = 0,
  PROP_CAM_TILT,
  PROP_CAM_ROLL,
  PROP_CAM_ZOOM,
  PROP_CAM_EXPOSURE,
  PROP_CAM_IRIS,
  PROP_CAM_FOCUS,
  PROP_CAM_MEGA = 65536,
}

export type ICNodeResult<T = undefined> = {
  code: ICNodeResuleCode;
  data?: T;
  message?: string;
};

// Napi::Extrenal object
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
  IC_IsCameraPropertyAvailable(
    grabber: ICNodeGrabber,
    property: ICNodeCameraProperty,
  ): ICNodeResult<boolean>;
  IC_SetCameraProperty(
    grabber: ICNodeGrabber,
    property: ICNodeCameraProperty,
    value: number,
  ): ICNodeResult;
  IC_CameraPropertyGetRange(
    grabber: ICNodeGrabber,
    property: ICNodeCameraProperty,
  ): ICNodeResult<ICNodePropertyRange>;
  IC_GetCameraProperty(
    grabber: ICNodeGrabber,
    property: ICNodeCameraProperty,
  ): ICNodeResult<number>;
  IC_EnableAutoCameraProperty(
    grabber: ICNodeGrabber,
    property: ICNodeCameraProperty,
    onOff: ICNodeSwitch,
  ): ICNodeResult;
  IC_IsCameraPropertyAutoAvailable(
    grabber: ICNodeGrabber,
    property: ICNodeCameraProperty,
  ): ICNodeResult<boolean>;
  IC_GetAutoCameraProperty(
    grabber: ICNodeGrabber,
    property: ICNodeCameraProperty,
  ): ICNodeResult<boolean>;
  IC_IsVideoPropertyAvailable(
    grabber: ICNodeGrabber,
    property: ICNodeVideoProperty,
  ): ICNodeResult<boolean>;
  IC_VideoPropertyGetRange(
    grabber: ICNodeGrabber,
    property: ICNodeVideoProperty,
  ): ICNodeResult<ICNodePropertyRange>;
  IC_GetVideoProperty(grabber: ICNodeGrabber, property: ICNodeVideoProperty): ICNodeResult<number>;
  IC_IsVideoPropertyAutoAvailable(
    grabber: ICNodeGrabber,
    property: ICNodeVideoProperty,
  ): ICNodeResult<boolean>;
  IC_GetAutoVideoProperty(
    grabber: ICNodeGrabber,
    property: ICNodeVideoProperty,
  ): ICNodeResult<boolean>;
  IC_SetVideoProperty(
    grabber: ICNodeGrabber,
    property: ICNodeVideoProperty,
    value: number,
  ): ICNodeResult;
  IC_EnableAutoVideoProperty(
    grabber: ICNodeGrabber,
    property: ICNodeVideoProperty,
    onOff: ICNodeSwitch,
  ): ICNodeResult;
  IC_GetImageDescription(grabber: ICNodeGrabber): ICNodeResult<ICNodeImageDescriptionWithFormat>;
  IC_SnapImage(grabber: ICNodeGrabber, timeout: MillSecond): ICNodeResult;
  IC_SaveImage(
    grabber: ICNodeGrabber,
    fileName: string,
    fileType: ICNodeImgFileType,
    quality?: number,
  ): ICNodeResult;
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
  IC_LoadDeviceStateFromFileEx(
    grabber: ICNodeGrabber,
    fileName: string,
    openDevice: ICNodeSwitch,
  ): ICNodeResult;
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
  IC_SetFrameReadyCallbackEx(
    grabber: ICNodeGrabber,
    callback: ICNodeFrameReadyCallback,
  ): ICNodeResult;
  IC_SetDeviceLostCallback(
    grabber: ICNodeGrabber,
    callback: ICNodeDeviceLostCallback,
  ): ICNodeResult;
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
  IC_enumPropertyElements(
    grabber: ICNodeGrabber,
    property: string,
    cb: ICNodeEnumCallback,
  ): ICNodeResult;
  IC_enumPropertyElementInterfaces(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
    cb: ICNodeEnumCallback,
  ): ICNodeResult;
  IC_IsPropertyAvailable(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
  ): ICNodeResult<boolean>;
  IC_GetPropertyValueRange(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
  ): ICNodeResult<ICNodePropertyRange>;
  IC_GetPropertyValue(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
  ): ICNodeResult<number>;
  IC_SetPropertyValue(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
    value?: number,
  ): ICNodeResult;
  IC_GetPropertyAbsoluteValueRange(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
  ): ICNodeResult<ICNodePropertyRange>;
  IC_GetPropertyAbsoluteValue(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
  ): ICNodeResult<number>;
  IC_SetPropertyAbsoluteValue(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
    value?: number,
  ): ICNodeResult;
  IC_GetPropertySwitch(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
  ): ICNodeResult<ICNodeSwitch>;
  IC_SetPropertySwitch(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
    value?: boolean,
  ): ICNodeResult;
  IC_PropertyOnePush(grabber: ICNodeGrabber, property: string, element: string): ICNodeResult;
  IC_GetPropertyMapStrings(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
  ): ICNodeResult<string[]>;
  IC_GetPropertyMapString(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
  ): ICNodeResult<string>;
  IC_SetPropertyMapString(
    grabber: ICNodeGrabber,
    property: string,
    element: string,
    value?: string,
  ): ICNodeResult;
  IC_ResetProperties(grabber: ICNodeGrabber): ICNodeResult;
  IC_SetRingBufferSize(grabber: ICNodeGrabber, size: number): ICNodeResult;
  IC_GetRingBufferSize(grabber: ICNodeGrabber): ICNodeResult<number>;
  IC_GetMemBuffer(grabber: ICNodeGrabber, index: number): ICNodeResult<ICNodeImageBuffer>;
  IC_GetMemBufferLastAcq(grabber: ICNodeGrabber): ICNodeResult<ICNodeImageBuffer>;
  IC_GetMemBufferDescription(
    imgBuffer: ICNodeImageBuffer,
  ): ICNodeResult<ICNodeImageDescriptionBase>;
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
export type ICNodePropertyElement =
  | ICNodeSwitchPropertyElement
  | ICNodeButtonPropertyElement
  | ICNodeRangePropertyElement;

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
  // 是否支持亮度调节
  supportBrightness: boolean;
  // 是否支持自动亮度调节
  supportAutoBrightness: boolean;
  // 亮度范围
  brightnessRange: ICNodePropertyRange | null;
  // 是否支持对比度调节
  supportContrast: boolean;
  // 是否支持自动对比度调节
  supportAutoContrast: boolean;
  // 对比度范围
  contrastRange: ICNodePropertyRange | null;
  // 是否支持曝光调节
  supportExposure: boolean;
  // 是否支持自动曝光调节
  supportAutoExposure: boolean;
  // 曝光范围
  exposureRange: ICNodePropertyRange | null;
  // 是否支持增益调节
  supportGain: boolean;
  // 是否支持自动增益调节
  supportAutoGain: boolean;
  // 增益范围
  gainRange: ICNodePropertyRange | null;
  // 是否支持清晰度调节
  supportSharpness: boolean;
  // 是否支持自动清晰度调节
  supportAutoSharpness: boolean;
  // 清晰度范围
  sharpnessRange: ICNodePropertyRange | null;
  // 是否支持伽马校正调节
  supportGamma: boolean;
  // 是否支持自动伽马校正调节
  supportAutoGamma: boolean;
  // 伽马校正范围
  gammaRange: ICNodePropertyRange | null;
  // 是否支持白平衡调节
  supportWhiteBalance: boolean;
  // 是否支持自动白平衡调节
  supportAutoWhiteBalance: boolean;
  // 白平衡范围
  whiteBalanceRange: ICNodePropertyRange | null;
  // 是否支持缩放(ZOOM)调节
  supportZoom: boolean;
  // 是否支持自动缩放
  supportAutoZoom: boolean;
  // 缩放范围
  zoomRange: ICNodePropertyRange | null;
  // 是否支持聚焦(FOCUS调节
  supportFocus: boolean;
  // 是否支持自动聚焦
  supportAutoFocus: boolean;
  // 聚焦范围
  focusRange: ICNodePropertyRange | null;
  // 是否支持光圈(IRIS)调节
  supportIris: boolean;
  // 是否支持自动光圈
  supportAutoIris: boolean;
  // 光圈范围
  irisRange: ICNodePropertyRange | null;
  // 是否支持饱和度调节
  supportSaturation: boolean;
  // 是否支持自动饱和度调节
  supportAutoSaturation: boolean;
  // 饱和度范围
  saturationRange: ICNodePropertyRange | null;
  // 是否支持色相调节
  supportHue: boolean;
  // 是否支持自动色相调节
  supportAutoHue: boolean;
  // 色相范围
  hueRange: ICNodePropertyRange | null;
  // 是否支持逆光补偿
  supportBacklightCompensation: boolean;
};

export type ICNodeImageFileFormat = 'bmp' | 'jpg' | 'tiff';

export type ICGrabberState = {
  device: DeviceMeta | null;
  // 视频格式
  videoFormat: ICNodeVideoFormat;
  // 视频制式
  videoNorm: ICNodeVideoNorm | null;
  // 输入通道
  inputChannel: ICNodeInputChannel | null;
  // 连续截图是否正在执行的标识
  continuousCaptureRunning: boolean;
  // 连续截图的时间间隔(ms)
  continuousCaptureInterval: number;
  // 连续截图的图片格式
  continuousCaptureImageFormat: ICNodeImageFileFormat;
  // 连续截图的图片质量(仅 jpg 格式有效)
  continuousCaptureImageQuality: number;
  // 连续截图的图片保存路径
  continuousCaptureImageSavePath: string;
  // 亮度
  brightness: number;
  // 帧率
  frameRate: number;
};
