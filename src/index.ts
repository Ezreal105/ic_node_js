import type {
  DeviceMeta,
  DevicePreviewInfo,
  ICGrabberState,
  ICNodeButtonPropertyElement,
  ICNodeInputChannel,
  ICNodePropertyElement,
  ICNodePropertyValueRange,
  ICNodeRangePropertyElement,
  ICNodeVideoFormat,
  ICNodeVideoNorm,
} from './type';
import {
  type ICNodeStatic,
  type ICNodeGrabber,
  type ICGrabberInitOptions,
  type ICNodeResult,
  ICNodeResuleCode,
} from './type';

const binding = require('../lib/binding/napi-v8/ic_node.node').ic_static;

const icNodeStatic: ICNodeStatic = {
  IC_InitLibrary: (...args) => binding.IC_InitLibrary(...args),
  IC_CloseLibrary: () => binding.IC_CloseLibrary(),
  IC_TidyUP: () => binding.IC_TidyUP(),
  IC_CreateGrabber: () => binding.IC_CreateGrabber(),
  IC_ReleaseGrabber: (...args) => binding.IC_ReleaseGrabber(...args),
  IC_CloseVideoCaptureDevice: (...args) => binding.IC_CloseVideoCaptureDevice(...args),
  IC_GetDeviceName: (...args) => binding.IC_GetDeviceName(...args),
  IC_GetUniqueNamefromList: (...args) => binding.IC_GetUniqueNamefromList(...args),
  IC_GetDevice: (...args) => binding.IC_GetDevice(...args),
  IC_OpenDevByUniqueName: (...args) => binding.IC_OpenDevByUniqueName(...args),

  IC_GetDisplayName: (...args) => binding.IC_GetDisplayName(...args),
  IC_GetUniqueName: (...args) => binding.IC_GetUniqueName(...args),
  IC_GetSerialNumber: (...args) => binding.IC_GetSerialNumber(...args),
  IC_GetVideoFormatCount: (...args) => binding.IC_GetVideoFormatCount(...args),
  IC_GetVideoFormat: (...args) => binding.IC_GetVideoFormat(...args),
  IC_GetVideoNormCount: (...args) => binding.IC_GetVideoNormCount(...args),
  IC_GetVideoNorm: (...args) => binding.IC_GetVideoNorm(...args),
  IC_GetInputChannelCount: (...args) => binding.IC_GetInputChannelCount(...args),
  IC_GetInputChannel: (...args) => binding.IC_GetInputChannel(...args),
  IC_IsPropertyAvailable: (...args) => binding.IC_IsPropertyAvailable(...args),
  IC_PropertyOnePush: (...args) => binding.IC_PropertyOnePush(...args),
  IC_SetVideoFormat: (...args) => binding.IC_SetVideoFormat(...args),
  IC_SetVideoNorm: (...args) => binding.IC_SetVideoNorm(...args),
  IC_SetInputChannel: (...args) => binding.IC_SetInputChannel(...args),
  IC_GetAvailableFrameRates: (...args) => binding.IC_GetAvailableFrameRates(...args),
  IC_SetFrameRate: (...args) => binding.IC_SetFrameRate(...args),
  IC_GetFrameRate: (...args) => binding.IC_GetFrameRate(...args),
  IC_GetPropertyValueRange: (...args) => binding.IC_GetPropertyValueRange(...args),
  IC_GetPropertyValue: (...args) => binding.IC_GetPropertyValue(...args),
  IC_SetPropertyValue: (...args) => binding.IC_SetPropertyValue(...args),
  IC_enumProperties: (...args) => binding.IC_enumProperties(...args),
  IC_enumPropertyElements: (...args) => binding.IC_enumPropertyElements(...args),
  IC_GetDeviceCount: (...args) => binding.IC_GetDeviceCount(...args),
} as ICNodeStatic;

const DEFAULT_OPTIONS: Partial<ICGrabberInitOptions> = {
  licenseKey: '0',
  autoOpenDevice: true,
};

function SUCCESS(res: ICNodeResult<any>) {
  return res.code === ICNodeResuleCode.SUCCESS;
}

function MESSAGE(res: ICNodeResult<any>) {
  return `error code: ${res.code}` + (res.message ? `, message: ${res.message}` : '');
}

function CODE(res: ICNodeResult<any>) {
  return res.code;
}

// eslint-disable-next-line @typescript-eslint/no-unused-vars
function DATA<T>(res: ICNodeResult<T>): T {
  return res.data as T;
}

function FORCE_DATA<T>(res: ICNodeResult<T>): T {
  if (SUCCESS(res)) {
    return res.data as T;
  } else {
    throw new Error(MESSAGE(res));
  }
}

class ICGrabber {
  private static METHODS = icNodeStatic;
  static libInited = false;
  static init(licenseKey: string = DEFAULT_OPTIONS.licenseKey!) {
    if (!ICGrabber.libInited) {
      const initLibResult = ICGrabber.METHODS.IC_InitLibrary(licenseKey!);
      if (SUCCESS(initLibResult)) {
        ICGrabber.libInited = true;
      } else {
        throw new Error(MESSAGE(initLibResult));
      }
    }
    ICGrabber.getDeviceCount();
  }
  static getDeviceCount() {
    return FORCE_DATA(ICGrabber.METHODS.IC_GetDeviceCount());
  }
  static listDevicePreviewInfo(): DevicePreviewInfo[] {
    const deviceInfoList: DevicePreviewInfo[] = [];
    const deviceCount = ICGrabber.getDeviceCount();
    for (let i = 0; i < deviceCount; i++) {
      const uniqueName = FORCE_DATA(ICGrabber.METHODS.IC_GetUniqueNamefromList(i));
      const displayName = FORCE_DATA(ICGrabber.METHODS.IC_GetDevice(i));
      deviceInfoList.push({
        uniqueName,
        displayName,
      });
    }
    return deviceInfoList;
  }

  private grabber: ICNodeGrabber;

  private state: ICGrabberState = {
    device: null,
    videoFormat: '',
    videoNorm: null,
    inputChannel: null,
    continuousCaptureRunning: false,
    continuousCaptureInterval: 1000,
    continuousCaptureImageFormat: 'bmp',
    continuousCaptureImageQuality: 100,
    continuousCaptureImageSavePath: 'TODO',
    brightness: 0,
    frameRate: 0,
  };

  constructor(private _options: ICGrabberInitOptions) {
    Object.assign(this._options, DEFAULT_OPTIONS);
    ICGrabber.init(this.options.licenseKey);
    this.grabber = FORCE_DATA(ICGrabber.METHODS.IC_CreateGrabber());
    if (this.options.autoOpenDevice) {
      this.openDevice();
    }
    this.loadState();
  }

  get options(): Required<ICGrabberInitOptions> {
    return this._options as Required<ICGrabberInitOptions>;
  }

  /**
   * 从持久化存储中加载上次的状态，如果没有则使用默认值
   */
  private loadState() {
    // TODO: 完善这里的逻辑
    this.loadVideoFormat();
    this.loadVideoNorm();
    this.loadInputChannel();
  }

  private loadVideoFormat() {
    // TODO: 完善这里的逻辑
    const supprotedVideoFormats = this.getSupprotedVideoFormats();
    if (supprotedVideoFormats.length <= 0) {
      throw new Error('no supproted video format');
    }
    const state = supprotedVideoFormats[supprotedVideoFormats.length - 1];
    this.setVideoFormat(state);
  }

  private loadVideoNorm() {
    // TODO: 完善这里的逻辑
    const supprotedVideoNorms = this.getSupprotedVideoNorms();
    if (supprotedVideoNorms.length <= 0) {
      // log
    } else {
      const videoNorm = supprotedVideoNorms[supprotedVideoNorms.length - 1];
      this.setVideoNorm(videoNorm);
    }
  }

  private loadInputChannel() {
    const supportedInputChannels = this.getSupprotedInputChannels();
    if (supportedInputChannels.length <= 0) {
      // log
    } else {
      const inputChannel = supportedInputChannels[supportedInputChannels.length - 1];
      this.setInputChannel(inputChannel);
    }
  }

  setVideoFormat(videoFormat: ICNodeVideoFormat) {
    FORCE_DATA(ICGrabber.METHODS.IC_SetVideoFormat(this.grabber, videoFormat));
    this.state.videoFormat = videoFormat;
  }

  getVideoFormat(): ICNodeVideoFormat {
    return this.state.videoFormat;
  }

  setVideoNorm(videoNorm: ICNodeVideoNorm) {
    FORCE_DATA(ICGrabber.METHODS.IC_SetVideoNorm(this.grabber, videoNorm));
    this.state.videoNorm = videoNorm;
  }

  getVideoNorm(): ICNodeVideoNorm | null {
    return this.state.videoNorm;
  }

  setInputChannel(inputChannel: ICNodeInputChannel) {
    FORCE_DATA(ICGrabber.METHODS.IC_SetInputChannel(this.grabber, inputChannel));
    this.state.inputChannel = inputChannel;
  }

  getInputChannel(): ICNodeInputChannel | null {
    return this.state.inputChannel;
  }

  setFrameRate(frameRate: number) {
    FORCE_DATA(ICGrabber.METHODS.IC_SetFrameRate(this.grabber, frameRate));
  }

  getFrameRate(): number {
    return FORCE_DATA(ICGrabber.METHODS.IC_GetFrameRate(this.grabber));
  }

  setBrightness(brightness: number) {
    if (this.state.device?.supportBrightness) {
      const {min, max} = FORCE_DATA(
        ICGrabber.METHODS.IC_GetPropertyValueRange(this.grabber, 'Brightness', 'Value'),
      );
      if (brightness >= min && brightness <= max) {
        FORCE_DATA(
          ICGrabber.METHODS.IC_SetPropertyValue(this.grabber, 'Brightness', 'Value', brightness),
        );
        this.state.brightness = brightness;
      } else {
        // TODO: log
      }
    }
  }

  openDevice() {
    if (!this.state.device) {
      const {deviceUniqueName} = this.options;
      FORCE_DATA(ICGrabber.METHODS.IC_OpenDevByUniqueName(this.grabber, deviceUniqueName));
      this.state.device = this.loadDeviceMeta();
    }
  }

  getUniqueName(): string {
    return FORCE_DATA(ICGrabber.METHODS.IC_GetUniqueName(this.grabber));
  }

  getDeviceName(): string {
    return FORCE_DATA(ICGrabber.METHODS.IC_GetDeviceName(this.grabber));
  }

  getSerialNumber(): string {
    const res = ICGrabber.METHODS.IC_GetSerialNumber(this.grabber);
    const code = CODE(res);
    if (code === ICNodeResuleCode.NOT_AVAILABLE) {
      return '';
    } else {
      return FORCE_DATA(res);
    }
  }

  getSupprotedVideoFormats(): ICNodeVideoFormat[] {
    const count = FORCE_DATA(ICGrabber.METHODS.IC_GetVideoFormatCount(this.grabber));
    const formats: ICNodeVideoFormat[] = [];
    for (let i = 0; i < count; i++) {
      formats.push(FORCE_DATA(ICGrabber.METHODS.IC_GetVideoFormat(this.grabber, i)));
    }
    return formats;
  }

  getSupprotedVideoNorms(): ICNodeVideoNorm[] {
    const count = FORCE_DATA(ICGrabber.METHODS.IC_GetVideoNormCount(this.grabber));
    const norms: ICNodeVideoNorm[] = [];
    for (let i = 0; i < count; i++) {
      norms.push(FORCE_DATA(ICGrabber.METHODS.IC_GetVideoNorm(this.grabber, i)));
    }
    return norms;
  }

  getSupprotedInputChannels(): ICNodeInputChannel[] {
    const count = FORCE_DATA(ICGrabber.METHODS.IC_GetInputChannelCount(this.grabber));
    const channels: ICNodeInputChannel[] = [];
    for (let i = 0; i < count; i++) {
      channels.push(FORCE_DATA(ICGrabber.METHODS.IC_GetInputChannel(this.grabber, i)));
    }
    return channels;
  }

  getSupportedFrameRates(): number[] {
    return FORCE_DATA(ICGrabber.METHODS.IC_GetAvailableFrameRates(this.grabber)).map(i =>
      Math.floor(i),
    );
  }

  isPropertyAvailable(...args: ICNodePropertyElement) {
    return FORCE_DATA(ICGrabber.METHODS.IC_IsPropertyAvailable(this.grabber, args[0], args[1]));
  }

  propertyOnePlus(...args: ICNodeButtonPropertyElement) {
    return FORCE_DATA(ICGrabber.METHODS.IC_PropertyOnePush(this.grabber, args[0], args[1]));
  }

  getAvailablePropertyElements(): ICNodePropertyElement[] {
    const properties: Array<ICNodePropertyElement[0]> = [];
    const enumPropertyCb = (property: string) => {
      properties.push(property as ICNodePropertyElement[0]);
    };
    FORCE_DATA(ICGrabber.METHODS.IC_enumProperties(this.grabber, enumPropertyCb));
    const results: ICNodePropertyElement[] = [];
    for (const property of properties) {
      const enumElementCb = (element: string) => {
        results.push([property, element] as ICNodePropertyElement);
      };
      FORCE_DATA(ICGrabber.METHODS.IC_enumPropertyElements(this.grabber, property, enumElementCb));
    }
    return results;
  }

  getPropertyValueRange<T extends ICNodeRangePropertyElement>(
    property: T[0],
    element: T[1],
  ): ICNodePropertyValueRange {
    return FORCE_DATA(ICGrabber.METHODS.IC_GetPropertyValueRange(this.grabber, property, element));
  }

  private loadDeviceMeta(): DeviceMeta {
    const uniqueName = this.getUniqueName();
    const displayName = this.getDeviceName();
    const serialNumber = this.getSerialNumber();
    const supprotedVideoFormats = this.getSupprotedVideoFormats();
    const supprotedVideoNorms = this.getSupprotedVideoNorms();
    const supportedInputChannels = this.getSupprotedInputChannels();
    const supportedFrameRates = this.getSupportedFrameRates();
    const supportSoftwareTrigger = this.isPropertyAvailable('Trigger', 'Software Trigger');
    const supportBrightness = this.isPropertyAvailable('Brightness', 'Value');
    const supportAutoBrightness = supportBrightness
      ? this.isPropertyAvailable('Brightness', 'Auto')
      : false;
    const brightnessRange = supportBrightness
      ? this.getPropertyValueRange('Brightness', 'Value')
      : null;

    const supportContrast = this.isPropertyAvailable('Contrast', 'Value');
    const supportAutoContrast = supportContrast
      ? this.isPropertyAvailable('Contrast', 'Auto')
      : false;
    const contrastRange = supportContrast ? this.getPropertyValueRange('Contrast', 'Value') : null;
    // 曝光相关
    const supportExposure = this.isPropertyAvailable('Exposure', 'Value');
    const supportAutoExposure = supportExposure
      ? this.isPropertyAvailable('Exposure', 'Auto')
      : false;
    const exposureRange = supportExposure ? this.getPropertyValueRange('Exposure', 'Value') : null;
    // 增益相关
    const supportGain = this.isPropertyAvailable('Gain', 'Value');
    const supportAutoGain = supportGain ? this.isPropertyAvailable('Gain', 'Auto') : false;
    const gainRange = supportGain ? this.getPropertyValueRange('Gain', 'Value') : null;
    // 清晰度相关
    const supportSharpness = this.isPropertyAvailable('Sharpness', 'Value');
    const supportAutoSharpness = supportSharpness
      ? this.isPropertyAvailable('Sharpness', 'Auto')
      : false;
    const sharpnessRange = supportSharpness
      ? this.getPropertyValueRange('Sharpness', 'Value')
      : null;
    // 伽马校正相关
    const supportGamma = this.isPropertyAvailable('Gamma', 'Value');
    const supportAutoGamma = supportGamma ? this.isPropertyAvailable('Gamma', 'Auto') : false;
    const gammaRange = supportGamma ? this.getPropertyValueRange('Gamma', 'Value') : null;
    // 白平衡相关
    const supportWhiteBalance = this.isPropertyAvailable('White Balance', 'Value');
    const supportAutoWhiteBalance = supportWhiteBalance
      ? this.isPropertyAvailable('White Balance', 'Auto')
      : false;
    const whiteBalanceRange = supportWhiteBalance
      ? this.getPropertyValueRange('White Balance', 'Value')
      : null;
    // 缩放（ZOOM）相关
    const supportZoom = this.isPropertyAvailable('Zoom', 'Value');
    const supportAutoZoom = supportZoom ? this.isPropertyAvailable('Zoom', 'Auto') : false;
    const zoomRange = supportZoom ? this.getPropertyValueRange('Zoom', 'Value') : null;
    // 聚焦(FOCUS)相关
    const supportFocus = this.isPropertyAvailable('Focus', 'Value');
    const supportAutoFocus = supportFocus ? this.isPropertyAvailable('Focus', 'Auto') : false;
    const focusRange = supportFocus ? this.getPropertyValueRange('Focus', 'Value') : null;
    // 光圈(IRIS) 相关
    const supportIris = this.isPropertyAvailable('Iris', 'Value');
    const supportAutoIris = supportIris ? this.isPropertyAvailable('Iris', 'Auto') : false;
    const irisRange = supportIris ? this.getPropertyValueRange('Iris', 'Value') : null;
    // 饱和度相关
    const supportSaturation = this.isPropertyAvailable('Saturation', 'Value');
    const supportAutoSaturation = supportSaturation
      ? this.isPropertyAvailable('Saturation', 'Auto')
      : false;
    const saturationRange = supportSaturation
      ? this.getPropertyValueRange('Saturation', 'Value')
      : null;
    // 色相相关
    const supportHue = this.isPropertyAvailable('Hue', 'Value');
    const supportAutoHue = supportHue ? this.isPropertyAvailable('Hue', 'Auto') : false;
    const hueRange = supportHue ? this.getPropertyValueRange('Hue', 'Value') : null;
    // 逆光补偿相关
    const supportBacklightCompensation = this.isPropertyAvailable('BacklightCompensation', 'Value');
    const supportAutoBacklightCompensation = supportBacklightCompensation
      ? this.isPropertyAvailable('BacklightCompensation', 'Auto')
      : false;
    const backlightCompensationRange = supportBacklightCompensation
      ? this.getPropertyValueRange('BacklightCompensation', 'Value')
      : null;
    return {
      uniqueName,
      displayName,
      serialNumber,
      supprotedVideoFormats,
      supprotedVideoNorms,
      supportedInputChannels,
      supportedFrameRates,
      supportSoftwareTrigger,
      supportBrightness,
      supportAutoBrightness,
      brightnessRange,
      supportContrast,
      supportAutoContrast,
      contrastRange,
      supportExposure,
      supportAutoExposure,
      exposureRange,
      supportGain,
      supportAutoGain,
      gainRange,
      supportSharpness,
      supportAutoSharpness,
      sharpnessRange,
      supportGamma,
      supportAutoGamma,
      gammaRange,
      supportWhiteBalance,
      supportAutoWhiteBalance,
      whiteBalanceRange,
      supportZoom,
      supportAutoZoom,
      zoomRange,
      supportFocus,
      supportAutoFocus,
      focusRange,
      supportIris,
      supportAutoIris,
      irisRange,
      supportSaturation,
      supportAutoSaturation,
      saturationRange,
      supportHue,
      supportAutoHue,
      hueRange,
      supportBacklightCompensation,
      supportAutoBacklightCompensation,
      backlightCompensationRange,
    };
  }

  close() {
    if (this.state.device) {
      ICGrabber.METHODS.IC_CloseVideoCaptureDevice(this.grabber);
    }
    ICGrabber.METHODS.IC_ReleaseGrabber(this.grabber);
    if (ICGrabber.libInited) {
      ICGrabber.METHODS.IC_CloseLibrary();
    }
  }
}

export {ICGrabber};
