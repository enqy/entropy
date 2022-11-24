{
  lib,
  stdenvNoCC,
  inputs,
  zig-cc,
  zig-ld,
  zig-ar,
  zig-dlltool,
  zig-lib,
  zig-ranlib,
  zig-rc,
  cmake,
  extra-cmake-modules,
  pkg-config,
  wayland,
  wayland-protocols,
  wayland-scanner,
  libxkbcommon,
  darwin,
}: let
  stdenv = stdenvNoCC;
  apple_sdk = darwin.apple_sdk_11_0;
in
  stdenv.mkDerivation {
    pname = "glfw";
    version = inputs.glfw.shortRev;
    src = inputs.glfw;

    depsBuildBuild =
      [
        extra-cmake-modules
      ]
      ++ lib.optionals stdenv.hostPlatform.isDarwin [
        cmake
      ];

    nativeBuildInputs =
      [
        pkg-config
        zig-cc
        zig-ld
        zig-ar
        zig-dlltool
        zig-lib
        zig-ranlib
        zig-rc
      ]
      ++ lib.optionals (!stdenv.hostPlatform.isDarwin) [
        cmake
      ]
      ++ lib.optionals stdenv.hostPlatform.isLinux [
        wayland-scanner
      ];

    buildInputs = lib.optionals stdenv.hostPlatform.isLinux [
      wayland
      wayland-protocols
      libxkbcommon
    ];

    CC = "zig-cc";
    LD = "zig-ld";
    AR = "zig-ar";
    DLLTOOL = "zig-dlltool";
    LIB = "zig-lib";
    RANLIB = "zig-ranlib";
    RC = "zig-rc";

    preConfigure = let
      zigTargetMap = {
        "x86_64-unknown-linux-gnu" = "x86_64-linux-gnu";
        "aarch64-unknown-linux-gnu" = "aarch64-linux-gnu";
        "x86_64-apple-darwin" = "x86_64-macos-none";
        "aarch64-apple-darwin" = "aarch64-macos-none";
        "x86_64-w64-windows-gnu" = "x86_64-windows-gnu";
      };
    in
      ''
        export ZIG_LOCAL_CACHE_DIR="$TMPDIR/zig-cache"
        export ZIG_GLOBAL_CACHE_DIR="$ZIG_LOCAL_CACHE_DIR"

        export ZIG_CC_TARGET=${zigTargetMap."${stdenv.hostPlatform.config}"}
      ''
      + lib.optionalString stdenv.hostPlatform.isDarwin (let
        mega_hacky_link = framework: ''
          if [[ ! -L "$TMPDIR/include/${framework}" ]]; then
            ln -s "${apple_sdk.frameworks."${framework}"}/Library/Frameworks/${framework}.framework/Headers" "$TMPDIR/include/${framework}"
          fi

          for f in ${apple_sdk.frameworks."${framework}"}/Library/Frameworks/${framework}.framework/Frameworks/*; do
            local framework_name="$(basename "$f")"
            framework_name="$''\{framework_name%.framework}"
            if [[ ! -L "$f" ]]; then
              if [[ ! -L "$TMPDIR/include/$framework_name" ]]; then
                ln -s "$f/Headers" "$TMPDIR/include/$framework_name"
              fi
            fi
          done
        '';
      in ''
        # mega hacky time
        mkdir -p "$TMPDIR/include"

        # ln all the frameworks to a single directory
        ${mega_hacky_link "AppKit"}
        ${mega_hacky_link "ApplicationServices"}
        ${mega_hacky_link "CFNetwork"}
        ${mega_hacky_link "Carbon"}
        ${mega_hacky_link "CloudKit"}
        ${mega_hacky_link "Cocoa"}
        ${mega_hacky_link "ColorSync"}
        ${mega_hacky_link "CoreData"}
        ${mega_hacky_link "CoreFoundation"}
        ${mega_hacky_link "CoreGraphics"}
        ${mega_hacky_link "CoreImage"}
        ${mega_hacky_link "CoreLocation"}
        ${mega_hacky_link "CoreServices"}
        ${mega_hacky_link "CoreText"}
        ${mega_hacky_link "CoreVideo"}
        ${mega_hacky_link "DiskArbitration"}
        ${mega_hacky_link "Foundation"}
        ${mega_hacky_link "IOKit"}
        ${mega_hacky_link "IOSurface"}
        ${mega_hacky_link "ImageIO"}
        ${mega_hacky_link "Kernel"}
        ${mega_hacky_link "Metal"}
        ${mega_hacky_link "OpenGL"}
        ${mega_hacky_link "QuartzCore"}
        ${mega_hacky_link "Security"}

        export ZIG_CC_FLAGS="-I$TMPDIR/include"
      '');

    CC_FLAGS = lib.optionals stdenv.hostPlatform.isDarwin [
      "-I${apple_sdk.libs.libDER}/include"
      "-DTARGET_OS_IPHONE=0" # something is borked
    ];

    cmakeFlags = [
      "-DCMAKE_VERBOSE_MAKEFILE=ON"
      "-DBUILD_SHARED_LIBS=OFF"
      "-DGLFW_BUILD_EXAMPLES=OFF"
      "-DGLFW_BUILD_TESTS=OFF"
      "-DGLFW_BUILD_DOCS=OFF"
      "-DGLFW_BUILD_WAYLAND=ON"
      "-DGLFW_BUILD_X11=OFF"
    ];

    postInstall = lib.optional (stdenv.hostPlatform.isMinGW) ''
      ln -fs $out/lib/libglfw3dll.a $out/lib/glfw3.lib
    '';
  }
