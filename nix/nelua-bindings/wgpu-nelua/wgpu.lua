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
]=]
