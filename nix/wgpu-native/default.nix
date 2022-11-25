{
  lib,
  craneLib,
  stdenvNoCC,
  rustcTargetMap,
  zigTargetMap,
  rustPlatform,
  pkgsBuildBuild,
  inputs,
  zig-cc,
  zig-ld,
  zig-ar,
  zig-dlltool,
  zig-lib,
  zig-ranlib,
  zig-rc,
  zig,
  cargo,
  darwin,
}: let
  stdenv = stdenvNoCC;
  apple_sdk = darwin.apple_sdk;
in
  craneLib.buildPackage {
    inherit stdenv;

    pname = "wgpu-native";
    version = inputs.wgpu-native.shortRev;
    src = inputs.wgpu-native;

    nativeBuildInputs =
      [
        zig-cc
        zig-ld
        zig-ar
        zig-dlltool
        zig-lib
        zig-ranlib
        zig-rc
      ]
      # doesn't work when building for darwin from a non-darwin host
      # also doesn't work when building for wasm
      ++ lib.optionals (!stdenv.hostPlatform.isDarwin && !stdenv.hostPlatform.isWasm) [
        rustPlatform.bindgenHook
      ];

    CC = "zig-cc";
    LD = "zig-ld";
    AR = "zig-ar";
    DLLTOOL = "zig-dlltool";
    LIB = "zig-lib";
    RANLIB = "zig-ranlib";
    RC = "zig-rc";

    postPatch = ''
      patch -p1 < ${./nelua.patch} || true
      patch -p1 < ${./ffi.patch} || true
    '';

    preConfigure =
      ''
        export ZIG_LOCAL_CACHE_DIR="$TMPDIR/zig-cache"
        export ZIG_GLOBAL_CACHE_DIR="$ZIG_LOCAL_CACHE_DIR"

        export CARGO_BUILD_TARGET=${rustcTargetMap."${stdenv.hostPlatform.config}"}
        export CARGO_TARGET_${lib.stringAsChars (x:
          if x == "-"
          then "_"
          else x) (lib.toUpper rustcTargetMap."${stdenv.hostPlatform.config}")}_LINKER=zig-cc
        export CC_"${lib.stringAsChars (x:
          if x == "-"
          then "_"
          else x)
        stdenv.hostPlatform.config}"=zig-cc
        export AR_"${lib.stringAsChars (x:
          if x == "-"
          then "_"
          else x)
        stdenv.hostPlatform.config}"=zig-ar
        export ZIG_CC_TARGET=${zigTargetMap."${stdenv.hostPlatform.config}"}
        export RUSTFLAGS="-C target-feature=-crt-static"
      ''
      + lib.optionalString stdenv.hostPlatform.isWasm ''
        export CARGO_TARGET_${lib.stringAsChars (x:
          if x == "-"
          then "_"
          else x) (lib.toUpper rustcTargetMap."${stdenv.buildPlatform.config}")}_LINKER=zig-cc
        export CC_wasm32_unknown_unknown=zig-cc
        export AR_wasm32_unknown_unknown=zig-ar
        export RUSTFLAGS="-C linker-flavor=ld --cfg=web_sys_unstable_apis $''\{RUSTFLAGS}"
      '';

    ZIG_CC_FLAGS =
      lib.optionals stdenv.hostPlatform.isDarwin [
        "--sysroot=${apple_sdk.MacOSX-SDK}"
        "-L${apple_sdk.MacOSX-SDK}/usr/lib"
        "-F${apple_sdk.frameworks.CoreFoundation}/Library/Frameworks"
        "-F${apple_sdk.frameworks.CoreGraphics}/Library/Frameworks"
        "-F${apple_sdk.frameworks.Metal}/Library/Frameworks"
        "-F${apple_sdk.frameworks.QuartzCore}/Library/Frameworks"
      ]
      ++ lib.optionals stdenv.hostPlatform.isWasm [
        "-Wl,--export-dynamic"
      ];

    # manually do what rustPlatform.bindgenHook does when building for darwin and wasm
    LIBCLANG_PATH = lib.optionalString (stdenv.hostPlatform.isDarwin || stdenv.hostPlatform.isWasm) "${pkgsBuildBuild.clang.cc.lib}/lib";
    BINDGEN_EXTRA_CLANG_ARGS =
      lib.optionals stdenv.hostPlatform.isDarwin [
        "--sysroot=${apple_sdk.MacOSX-SDK}"
        "-I${apple_sdk.MacOSX-SDK}/usr/include"
        "-I${apple_sdk.frameworks.Kernel}/Library/Frameworks/Kernel.framework/Headers"
      ]
      ++ lib.optionals stdenv.hostPlatform.isWasm [
        "-I${zig}/lib/libc/include/wasm-freestanding-musl"
        "-I${zig}/lib/libc/include/generic-musl/"
        "-I${zig}/lib/libc/musl/include/"
      ];

    preInstall = ''
      mkdir -p $out/include

      install -m664 ${inputs.wgpu-native}/ffi/webgpu-headers/webgpu.h $out/include
      install -m664 ${inputs.wgpu-native}/ffi/wgpu.h $out/include
      patch -d $out/include -p2 < ${./ffi.patch}
      sed -i -e 's/#include "webgpu-headers.*/#include <webgpu.h>/' $out/include/wgpu.h
    '';

    postInstall =
      lib.optionalString (stdenv.hostPlatform.isMinGW || stdenv.hostPlatform.isDarwin) ''
        # need to remove compiler_builtins on windows and darwin because they collide with zig ones
        if [[ -f $out/lib/libwgpu_native.a ]]; then
          zig-ar t $out/lib/libwgpu_native.a | grep compiler_builtins | xargs -I % zig-ar dv $out/lib/libwgpu_native.a %
        fi
      ''
      + lib.optionalString stdenv.hostPlatform.isDarwin ''
        # if [[ -f $out/lib/libwgpu_native.dylib ]]; then
        #   rm $out/lib/libwgpu_native.dylib
        # fi
      ''
      + lib.optionalString stdenv.hostPlatform.isWasm ''
        if [[ -f $out/lib/libwgpu_native.a ]]; then
          zig-ranlib $out/lib/libwgpu_native.a
        fi
      '';

    dontStrip = stdenv.hostPlatform.isWasm;

    doCheck = false;

    CARGO_PROFILE = "dev";
  }
