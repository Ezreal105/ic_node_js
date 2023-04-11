console.log('hahaha')
const binding = require('./lib/binding/napi-v8/ic_node.node');
const icNode = binding.ic_static;
icNode.IC_InitLibrary('0')
icNode.IC_GetDeviceCount();
const grabber = icNode.IC_CreateGrabber().data;
const name = icNode.IC_GetDevice(0).data
const uniqueName = icNode.IC_GetUniqueNamefromList(0).data
console.log('[wsttest] name', name)
icNode.IC_OpenVideoCaptureDevice(grabber, name).data
if (icNode.IC_IsDevValid(grabber)) {
    icNode.IC_StartLive(grabber, 0);
}