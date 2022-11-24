{
  stdenv,
  inputs,
  nelua-decl,
  gcc,
}:
stdenv.mkDerivation {
  name = "wgpu-nelua";

  src = ./.;

  nativeBuildInputs = [gcc];

  patchPhase = ''
    cp ${inputs.wgpu-native}/ffi/wgpu.h wgpu.h
    cp ${inputs.wgpu-native}/ffi/webgpu-headers/webgpu.h webgpu.h
    patch -p2 < ${./ffi.patch}
    sed -i -e 's/#include "webgpu-headers.*/#include <webgpu.h>/' wgpu.h
  '';

  buildPhase = ''
    export LUA_PATH="${nelua-decl}/lib/?.lua;;"
    gcc -fplugin=${nelua-decl}/lib/gcclua.so -fplugin-arg-gcclua-script=wgpu.lua -S wgpu.c -I. > wgpu.nelua
  '';

  installPhase = ''
    mkdir -p $out/nelua $out/include
    install -Dm644 wgpu.nelua $out/nelua/wgpu.nelua
    install -Dm644 wgpu.h $out/include/wgpu.h
    install -Dm644 webgpu.h $out/include/webgpu.h
  '';
}
