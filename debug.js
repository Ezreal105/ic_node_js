console.log('hahaha')
const binding = require('./lib/binding/napi-v8/ic_node.node');
const icNode = binding.ic_static;
icNode.IC_InitLibrary('0')
icNode.IC_GetDeviceCount();
const grabber = icNode.IC_CreateGrabber().data;
const name = icNode.IC_GetDevice(0).data
const uniqueName = icNode.IC_GetUniqueNamefromList(0).data
console.log('[wsttest] uniqueName', uniqueName)
icNode.IC_OpenDevByUniqueName(grabber, uniqueName).data
console.log(icNode.IC_IsPropertyAvailable(grabber, "Brightness", "Auto").data)
console.log(icNode.IC_IsVideoPropertyAutoAvailable(grabber, 0).data)
console.log(icNode.IC_GetUniqueName(grabber).data)
// if (icNode.IC_IsDevValid(grabber)) {
    
// }