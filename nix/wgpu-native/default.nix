{
  lib,
  craneLib,
  stdenvNoCC,
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
      ++ lib.optionals (!stdenv.hostPlatform.isDarwin) [
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

    preConfigure = let
      rustcTargetMap = {
        "x86_64-unknown-linux-gnu" = "x86_64-unknown-linux-gnu";
        "aarch64-unknown-linux-gnu" = "aarch64-unknown-linux-gnu";
        "x86_64-apple-darwin" = "x86_64-apple-darwin";
        "aarch64-apple-darwin" = "aarch64-apple-darwin";
        "x86_64-w64-windows-gnu" = "x86_64-pc-windows-gnu";
      };
      zigTargetMap = {
        "x86_64-unknown-linux-gnu" = "x86_64-linux-gnu";
        "aarch64-unknown-linux-gnu" = "aarch64-linux-gnu";
        "x86_64-apple-darwin" = "x86_64-macos-none";
        "aarch64-apple-darwin" = "aarch64-macos-none";
        "x86_64-w64-windows-gnu" = "x86_64-windows-gnu";
      };
    in ''
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
    '';

    ZIG_CC_FLAGS = lib.optionals stdenv.hostPlatform.isDarwin [
      "--sysroot=${apple_sdk.MacOSX-SDK}"
      "-L${apple_sdk.MacOSX-SDK}/usr/lib"
      "-F${apple_sdk.frameworks.CoreFoundation}/Library/Frameworks"
      "-F${apple_sdk.frameworks.CoreGraphics}/Library/Frameworks"
      "-F${apple_sdk.frameworks.Metal}/Library/Frameworks"
      "-F${apple_sdk.frameworks.QuartzCore}/Library/Frameworks"
    ];

    # manually do what rustPlatform.bindgenHook does when building for darwin
    LIBCLANG_PATH = lib.optionalString stdenv.hostPlatform.isDarwin "${pkgsBuildBuild.clang.cc.lib}/lib";
    BINDGEN_EXTRA_CLANG_ARGS = lib.optionals stdenv.hostPlatform.isDarwin [
      "--sysroot=${apple_sdk.MacOSX-SDK}"
      "-I${apple_sdk.MacOSX-SDK}/usr/include"
      "-I${apple_sdk.frameworks.Kernel}/Library/Frameworks/Kernel.framework/Headers"
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
        # need to remove compiler_builtins on windows because they collide with zig ones
        if [[ -f $out/lib/libwgpu_native.a ]]; then
          zig-ar t $out/lib/libwgpu_native.a | grep compiler_builtins | xargs -I % zig-ar dv $out/lib/libwgpu_native.a %
        fi
      ''
      + lib.optionalString stdenv.hostPlatform.isDarwin ''
        # if [[ -f $out/lib/libwgpu_native.dylib ]]; then
        #   rm $out/lib/libwgpu_native.dylib
        # fi
      '';

    doCheck = false;

    CARGO_PROFILE = "dev";
  }
