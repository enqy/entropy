local nldecl = require("nldecl")

nldecl.include_names = {
    "^WGPU",
    "^wgpu",
}

nldecl.prepend_code = [=[
##[[
cinclude '<webgpu.h>'
cinclude '<wgpu.h>'
linklib 'wgpu_native'
]]

global WGPU_LIMIT_U32_UNDEFINED: uint32 = 0xffffffff
global WGPU_LIMIT_U64_UNDEFINED: uint64 = 0xffffffffffffffff
]=]
