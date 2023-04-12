var ICNodeResuleCode;
(function (ICNodeResuleCode) {
    ICNodeResuleCode[ICNodeResuleCode["SUCCESS"] = 1] = "SUCCESS";
    ICNodeResuleCode[ICNodeResuleCode["ERROR"] = 0] = "ERROR";
    ICNodeResuleCode[ICNodeResuleCode["NO_HANDLE"] = -1] = "NO_HANDLE";
    ICNodeResuleCode[ICNodeResuleCode["NO_DEVICE"] = -2] = "NO_DEVICE";
    ICNodeResuleCode[ICNodeResuleCode["NOT_AVAILABLE"] = -3] = "NOT_AVAILABLE";
    ICNodeResuleCode[ICNodeResuleCode["NO_PROPERTYSET"] = -3] = "NO_PROPERTYSET";
    ICNodeResuleCode[ICNodeResuleCode["DEFAULT_WINDOW_SIZE_SET"] = -3] = "DEFAULT_WINDOW_SIZE_SET";
    ICNodeResuleCode[ICNodeResuleCode["NOT_IN_LIVEMODE"] = -3] = "NOT_IN_LIVEMODE";
    ICNodeResuleCode[ICNodeResuleCode["PROPERTY_ITEM_NOT_AVAILABLE"] = -4] = "PROPERTY_ITEM_NOT_AVAILABLE";
    ICNodeResuleCode[ICNodeResuleCode["PROPERTY_ELEMENT_NOT_AVAILABLE"] = -5] = "PROPERTY_ELEMENT_NOT_AVAILABLE";
    ICNodeResuleCode[ICNodeResuleCode["PROPERTY_ELEMENT_WRONG_INTERFACE"] = -6] = "PROPERTY_ELEMENT_WRONG_INTERFACE";
    ICNodeResuleCode[ICNodeResuleCode["INDEX_OUT_OF_RANGE"] = -7] = "INDEX_OUT_OF_RANGE";
    ICNodeResuleCode[ICNodeResuleCode["WRONG_XML_FORMAT"] = -1] = "WRONG_XML_FORMAT";
    ICNodeResuleCode[ICNodeResuleCode["WRONG_INCOMPATIBLE_XML"] = -3] = "WRONG_INCOMPATIBLE_XML";
    ICNodeResuleCode[ICNodeResuleCode["NOT_ALL_PROPERTIES_RESTORED"] = -4] = "NOT_ALL_PROPERTIES_RESTORED";
    ICNodeResuleCode[ICNodeResuleCode["DEVICE_NOT_FOUND"] = -5] = "DEVICE_NOT_FOUND";
    ICNodeResuleCode[ICNodeResuleCode["FILE_NOT_FOUND"] = 35] = "FILE_NOT_FOUND";
})(ICNodeResuleCode || (ICNodeResuleCode = {}));
var ICNodeColorFormat;
(function (ICNodeColorFormat) {
    ICNodeColorFormat[ICNodeColorFormat["Y800"] = 0] = "Y800";
    ICNodeColorFormat[ICNodeColorFormat["RGB24"] = 1] = "RGB24";
    ICNodeColorFormat[ICNodeColorFormat["RGB32"] = 2] = "RGB32";
    ICNodeColorFormat[ICNodeColorFormat["UYVY"] = 3] = "UYVY";
    ICNodeColorFormat[ICNodeColorFormat["Y16"] = 4] = "Y16";
    ICNodeColorFormat[ICNodeColorFormat["NONE"] = 5] = "NONE";
    ICNodeColorFormat[ICNodeColorFormat["COLORFORMAT_MEGA"] = 65536] = "COLORFORMAT_MEGA";
})(ICNodeColorFormat || (ICNodeColorFormat = {}));
var ICNodeImgFileType;
(function (ICNodeImgFileType) {
    ICNodeImgFileType[ICNodeImgFileType["FILETYPE_BMP"] = 0] = "FILETYPE_BMP";
    ICNodeImgFileType[ICNodeImgFileType["FILETYPE_JPEG"] = 1] = "FILETYPE_JPEG";
    ICNodeImgFileType[ICNodeImgFileType["FILETYPE_MEGA"] = 65536] = "FILETYPE_MEGA";
})(ICNodeImgFileType || (ICNodeImgFileType = {}));
var ICNodeVideoProperty;
(function (ICNodeVideoProperty) {
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_BRIGHTNESS"] = 0] = "PROP_VID_BRIGHTNESS";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_CONTRAST"] = 1] = "PROP_VID_CONTRAST";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_HUE"] = 2] = "PROP_VID_HUE";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_SATURATION"] = 3] = "PROP_VID_SATURATION";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_SHARPNESS"] = 4] = "PROP_VID_SHARPNESS";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_GAMMA"] = 5] = "PROP_VID_GAMMA";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_COLORENABLE"] = 6] = "PROP_VID_COLORENABLE";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_WHITEBALANCE"] = 7] = "PROP_VID_WHITEBALANCE";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_BLACKLIGHTCOMPENSATION"] = 8] = "PROP_VID_BLACKLIGHTCOMPENSATION";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_GAIN"] = 9] = "PROP_VID_GAIN";
    ICNodeVideoProperty[ICNodeVideoProperty["PROP_VID_MEGA"] = 65536] = "PROP_VID_MEGA";
})(ICNodeVideoProperty || (ICNodeVideoProperty = {}));
var ICNodeCameraProperty;
(function (ICNodeCameraProperty) {
    ICNodeCameraProperty[ICNodeCameraProperty["PROP_CAM_PAN"] = 0] = "PROP_CAM_PAN";
    ICNodeCameraProperty[ICNodeCameraProperty["PROP_CAM_TILT"] = 1] = "PROP_CAM_TILT";
    ICNodeCameraProperty[ICNodeCameraProperty["PROP_CAM_ROLL"] = 2] = "PROP_CAM_ROLL";
    ICNodeCameraProperty[ICNodeCameraProperty["PROP_CAM_ZOOM"] = 3] = "PROP_CAM_ZOOM";
    ICNodeCameraProperty[ICNodeCameraProperty["PROP_CAM_EXPOSURE"] = 4] = "PROP_CAM_EXPOSURE";
    ICNodeCameraProperty[ICNodeCameraProperty["PROP_CAM_IRIS"] = 5] = "PROP_CAM_IRIS";
    ICNodeCameraProperty[ICNodeCameraProperty["PROP_CAM_FOCUS"] = 6] = "PROP_CAM_FOCUS";
    ICNodeCameraProperty[ICNodeCameraProperty["PROP_CAM_MEGA"] = 65536] = "PROP_CAM_MEGA";
})(ICNodeCameraProperty || (ICNodeCameraProperty = {}));

const binding = require('../lib/binding/napi-v8/ic_node.node').ic_static;
const icNodeStatic = {
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
};
const DEFAULT_OPTIONS = {
    licenseKey: '0',
    autoOpenDevice: true,
};
function SUCCESS(res) {
    return res.code === ICNodeResuleCode.SUCCESS;
}
function MESSAGE(res) {
    return `error code: ${res.code}` + res.message ? `, message: ${res.message}` : '';
}
function CODE(res) {
    return res.code;
}
function FORCE_DATA(res) {
    if (SUCCESS(res)) {
        return res.data;
    }
    else {
        throw new Error(MESSAGE(res));
    }
}
class ICGrabber {
    _options;
    static METHODS = icNodeStatic;
    static libInited = false;
    static init(licenseKey = DEFAULT_OPTIONS.licenseKey) {
        if (!ICGrabber.libInited) {
            const initLibResult = ICGrabber.METHODS.IC_InitLibrary(licenseKey);
            if (SUCCESS(initLibResult)) {
                ICGrabber.libInited = true;
            }
            else {
                throw new Error(MESSAGE(initLibResult));
            }
        }
        ICGrabber.getDeviceCount();
    }
    static getDeviceCount() {
        return FORCE_DATA(ICGrabber.METHODS.IC_GetDeviceCount());
    }
    static listDevicePreviewInfo() {
        const deviceInfoList = [];
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
    grabber;
    state = {
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
    constructor(_options) {
        this._options = _options;
        Object.assign(this._options, DEFAULT_OPTIONS);
        ICGrabber.init(this.options.licenseKey);
        this.grabber = FORCE_DATA(ICGrabber.METHODS.IC_CreateGrabber());
        if (this.options.autoOpenDevice) {
            this.openDevice();
        }
        this.loadState();
    }
    get options() {
        return this._options;
    }
    /**
     * 从持久化存储中加载上次的状态，如果没有则使用默认值
     */
    loadState() {
        // TODO: 完善这里的逻辑
        this.loadVideoFormat();
        this.loadVideoNorm();
        this.loadInputChannel();
    }
    loadVideoFormat() {
        // TODO: 完善这里的逻辑
        const supprotedVideoFormats = this.getSupprotedVideoFormats();
        if (supprotedVideoFormats.length <= 0) {
            throw new Error('no supproted video format');
        }
        const state = supprotedVideoFormats[supprotedVideoFormats.length - 1];
        this.setVideoFormat(state);
    }
    loadVideoNorm() {
        // TODO: 完善这里的逻辑
        const supprotedVideoNorms = this.getSupprotedVideoNorms();
        if (supprotedVideoNorms.length <= 0) ;
        else {
            const videoNorm = supprotedVideoNorms[supprotedVideoNorms.length - 1];
            this.setVideoNorm(videoNorm);
        }
    }
    loadInputChannel() {
        const supportedInputChannels = this.getSupprotedInputChannels();
        if (supportedInputChannels.length <= 0) ;
        else {
            const inputChannel = supportedInputChannels[supportedInputChannels.length - 1];
            this.setInputChannel(inputChannel);
        }
    }
    setVideoFormat(videoFormat) {
        FORCE_DATA(ICGrabber.METHODS.IC_SetVideoFormat(this.grabber, videoFormat));
        this.state.videoFormat = videoFormat;
    }
    getVideoFormat() {
        return this.state.videoFormat;
    }
    setVideoNorm(videoNorm) {
        FORCE_DATA(ICGrabber.METHODS.IC_SetVideoNorm(this.grabber, videoNorm));
        this.state.videoNorm = videoNorm;
    }
    getVideoNorm() {
        return this.state.videoNorm;
    }
    setInputChannel(inputChannel) {
        FORCE_DATA(ICGrabber.METHODS.IC_SetInputChannel(this.grabber, inputChannel));
        this.state.inputChannel = inputChannel;
    }
    getInputChannel() {
        return this.state.inputChannel;
    }
    setFrameRate(frameRate) {
        FORCE_DATA(ICGrabber.METHODS.IC_SetFrameRate(this.grabber, frameRate));
    }
    getFrameRate() {
        return FORCE_DATA(ICGrabber.METHODS.IC_GetFrameRate(this.grabber));
    }
    setBrightness(brightness) {
        if (this.state.device?.supportBrightness) {
            const { min, max } = FORCE_DATA(ICGrabber.METHODS.IC_GetPropertyValueRange(this.grabber, 'Brightness', 'Value'));
            if (min)
                this.state.brightness = brightness;
        }
    }
    openDevice() {
        if (!this.state.device) {
            const { deviceUniqueName } = this.options;
            FORCE_DATA(ICGrabber.METHODS.IC_OpenDevByUniqueName(this.grabber, deviceUniqueName));
            this.state.device = this.loadDeviceMeta();
        }
    }
    getUniqueName() {
        return FORCE_DATA(ICGrabber.METHODS.IC_GetUniqueName(this.grabber));
    }
    getDeviceName() {
        return FORCE_DATA(ICGrabber.METHODS.IC_GetDeviceName(this.grabber));
    }
    getSerialNumber() {
        const res = ICGrabber.METHODS.IC_GetSerialNumber(this.grabber);
        const code = CODE(res);
        if (code === ICNodeResuleCode.NOT_AVAILABLE) {
            return '';
        }
        else {
            return FORCE_DATA(res);
        }
    }
    getSupprotedVideoFormats() {
        const count = FORCE_DATA(ICGrabber.METHODS.IC_GetVideoFormatCount(this.grabber));
        const formats = [];
        for (let i = 0; i < count; i++) {
            formats.push(FORCE_DATA(ICGrabber.METHODS.IC_GetVideoFormat(this.grabber, i)));
        }
        return formats;
    }
    getSupprotedVideoNorms() {
        const count = FORCE_DATA(ICGrabber.METHODS.IC_GetVideoNormCount(this.grabber));
        const norms = [];
        for (let i = 0; i < count; i++) {
            norms.push(FORCE_DATA(ICGrabber.METHODS.IC_GetVideoNorm(this.grabber, i)));
        }
        return norms;
    }
    getSupprotedInputChannels() {
        const count = FORCE_DATA(ICGrabber.METHODS.IC_GetInputChannelCount(this.grabber));
        const channels = [];
        for (let i = 0; i < count; i++) {
            channels.push(FORCE_DATA(ICGrabber.METHODS.IC_GetInputChannel(this.grabber, i)));
        }
        return channels;
    }
    getSupportedFrameRates() {
        return FORCE_DATA(ICGrabber.METHODS.IC_GetAvailableFrameRates(this.grabber));
    }
    isPropertyAvailable(property, element) {
        return FORCE_DATA(ICGrabber.METHODS.IC_IsPropertyAvailable(this.grabber, property, element));
    }
    propertyOnePlus(property, element) {
        return FORCE_DATA(ICGrabber.METHODS.IC_PropertyOnePush(this.grabber, property, element));
    }
    getAvailablePropertyElements() {
        const properties = [];
        const enumPropertyCb = (property) => {
            properties.push(property);
        };
        FORCE_DATA(ICGrabber.METHODS.IC_enumProperties(this.grabber, enumPropertyCb));
        const results = [];
        for (const property of properties) {
            const enumElementCb = (element) => {
                results.push([property, element]);
            };
            FORCE_DATA(ICGrabber.METHODS.IC_enumPropertyElements(this.grabber, property, enumElementCb));
        }
        return results;
    }
    loadDeviceMeta() {
        const uniqueName = this.getUniqueName();
        const displayName = this.getDeviceName();
        const serialNumber = this.getSerialNumber();
        const supprotedVideoFormats = this.getSupprotedVideoFormats();
        const supprotedVideoNorms = this.getSupprotedVideoNorms();
        const supportedInputChannels = this.getSupprotedInputChannels();
        const supportedFrameRates = this.getSupportedFrameRates();
        const supportSoftwareTrigger = this.isPropertyAvailable('Trigger', 'Software Trigger');
        const supportBrightness = this.isPropertyAvailable('Brightness', 'Value');
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

export { ICGrabber };
