import {ICNodeResuleCode, type ICNodeStatic} from './type';

function SUCCESS_RES(v?: any) {
  return {
    code: ICNodeResuleCode.SUCCESS,
    data: v,
  };
}
let binding = {
  IC_GetDeviceCount: () => SUCCESS_RES(0),
  IC_InitLibrary: () => SUCCESS_RES(),
} as unknown as ICNodeStatic;
// 如果是 windows
if (process.platform === 'win32') {
  binding = require('../lib/binding/napi-v8/ic_node.node').ic_static;
}

const icNodeStatic: ICNodeStatic = {
  isGrabberEqual: (...args) => binding.isGrabberEqual(...args),
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
  IC_SetDeviceLostCallback: (...args) => binding.IC_SetDeviceLostCallback(...args),
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
  IC_UnsetDeviceLostCallback: (...args) => binding.IC_UnsetDeviceLostCallback(...args),
  IC_GetPropertyAbsoluteValueRange: (...args) => binding.IC_GetPropertyAbsoluteValueRange(...args),
  IC_IsLive: (...args) => binding.IC_IsLive(...args),
  IC_PrepareLive: (...args) => binding.IC_PrepareLive(...args),
  IC_StartLive: (...args) => binding.IC_StartLive(...args),
  IC_StopLive: (...args) => binding.IC_StopLive(...args),
  IC_IsDevValid: (...args) => binding.IC_IsDevValid(...args),
} as ICNodeStatic;

export default icNodeStatic;
