import type { DevicePreviewInfo, ICNodeButtonPropertyElement, ICNodeInputChannel, ICNodePropertyElement, ICNodeVideoFormat, ICNodeVideoNorm } from './type';
import { type ICGrabberInitOptions } from './type';
declare class ICGrabber {
    private _options;
    private static METHODS;
    static libInited: boolean;
    static init(licenseKey?: string): void;
    static getDeviceCount(): number;
    static listDevicePreviewInfo(): DevicePreviewInfo[];
    private grabber;
    private state;
    constructor(_options: ICGrabberInitOptions);
    get options(): Required<ICGrabberInitOptions>;
    /**
     * 从持久化存储中加载上次的状态，如果没有则使用默认值
     */
    private loadState;
    private loadVideoFormat;
    private loadVideoNorm;
    private loadInputChannel;
    setVideoFormat(videoFormat: ICNodeVideoFormat): void;
    getVideoFormat(): ICNodeVideoFormat;
    setVideoNorm(videoNorm: ICNodeVideoNorm): void;
    getVideoNorm(): ICNodeVideoNorm | null;
    setInputChannel(inputChannel: ICNodeInputChannel): void;
    getInputChannel(): ICNodeInputChannel | null;
    setFrameRate(frameRate: number): void;
    getFrameRate(): number;
    setBrightness(brightness: number): void;
    openDevice(): void;
    getUniqueName(): string;
    getDeviceName(): string;
    getSerialNumber(): string;
    getSupprotedVideoFormats(): ICNodeVideoFormat[];
    getSupprotedVideoNorms(): ICNodeVideoNorm[];
    getSupprotedInputChannels(): ICNodeInputChannel[];
    getSupportedFrameRates(): number[];
    isPropertyAvailable<T extends ICNodePropertyElement>(property: T[0], element: T[1]): boolean;
    propertyOnePlus<T extends ICNodeButtonPropertyElement>(property: T[0], element: T[1]): undefined;
    getAvailablePropertyElements(): ICNodePropertyElement[];
    private loadDeviceMeta;
    close(): void;
}
export { ICGrabber };
