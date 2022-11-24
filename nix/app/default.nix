{
  lib,
  stdenv,
  stdenvNoCC,
  zigTargetMap,
  inputs,
  makeWrapper,
  zig-cc,
  zig-ld,
  zig-ar,
  zig-dlltool,
  zig-lib,
  zig-ranlib,
  zig-rc,
  zig ? null,
  nelua,
  glfw-nelua,
  glfwnative-nelua,
  wgpu-nelua,
  entropy,
  windows-nelua ? null,
  glfw ? null,
  wgpu-native,
  libxkbcommon,
  wayland,
  vulkan-loader,
  darwin,
}: let
  stdenv' = stdenv;
in let
  stdenv = stdenvNoCC;
  apple_sdk = darwin.apple_sdk_11_0;
in
  {
    pname ? "app",
    version ? "0.1.0",
    src ? ../../.,
    extraNeluaModules ? [],
    nixos ? false,
  }: let
    neluaModules =
      extraNeluaModules
      ++ [
        wgpu-nelua
        entropy
      ]
      ++ lib.optionals (!stdenv.hostPlatform.isWasm) [
        glfw-nelua
        glfwnative-nelua
      ]
      ++ lib.optionals stdenv.hostPlatform.isMinGW [
        windows-nelua
      ];
  in
    stdenv.mkDerivation {
      inherit pname version src;

      nativeBuildInputs =
        [
          nelua
          zig-cc
          zig-ld
          zig-ar
          zig-dlltool
          zig-lib
          zig-ranlib
          zig-rc
        ]
        ++ lib.optionals nixos [makeWrapper];

      CC = "zig-cc";
      LD = "zig-ld";
      AR = "zig-ar";
      DLLTOOL = "zig-dlltool";
      LIB = "zig-lib";
      RANLIB = "zig-ranlib";
      RC = "zig-rc";

      preConfigure = let
        neluaPath = "./?.nelua;${nelua}/lib/nelua/lib/?.nelua;" + (lib.foldr (module: path: "${module}/nelua/?.nelua;" + path) ";" neluaModules);
      in
        ''
          export ZIG_LOCAL_CACHE_DIR="$TMPDIR/zig-cache"
          export ZIG_GLOBAL_CACHE_DIR="$ZIG_LOCAL_CACHE_DIR"

          export ZIG_CC_TARGET=${zigTargetMap."${stdenv.hostPlatform.config}"}

          export NELUA_PATH="${neluaPath}"
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

          export ZIG_CC_FLAGS="-I$TMPDIR/include $''\{ZIG_CC_FLAGS}"
        '');

      configurePhase = ''
        runHook preConfigure

        nelua ${
          if stdenv.hostPlatform.isWasm
          then "main_wasm.nelua"
          else "main.nelua"
        } --release --print-code > ${
          if stdenv.hostPlatform.isDarwin
          then "main.m"
          else "main.c"
        }

        runHook postConfigure
      '';

      CC_FLAGS =
        builtins.map (module: "-I${module}/include") neluaModules
        ++ lib.optionals stdenv.hostPlatform.isDarwin [
          "-I${apple_sdk.libs.libDER}/include"
        ];

      ZIG_CC_FLAGS =
        [
          "-L${wgpu-native}/lib"
        ]
        ++ lib.optionals (!stdenv.hostPlatform.isWasm) [
          "-L${glfw}/lib"
        ]
        ++ lib.optionals stdenv.hostPlatform.isLinux [
          "-I${wayland.dev}/include"
          "-L${wayland}/lib"
          "-lwayland-client"
        ]
        ++ lib.optionals stdenv.hostPlatform.isMinGW [
          "-lc++"
          "-lgdi32"
          "-ld3dcompiler_47"
          "-luserenv"
          "-lbcrypt"
          "-lws2_32"
        ]
        ++ lib.optionals stdenv.hostPlatform.isDarwin [
          "-L${apple_sdk.MacOSX-SDK}/usr/lib"
          "-lobjc"
          "-F${apple_sdk.frameworks.CoreFoundation}/Library/Frameworks"
          "-framework CoreFoundation"
          "-F${apple_sdk.frameworks.CoreGraphics}/Library/Frameworks"
          "-framework CoreGraphics"
          "-F${apple_sdk.frameworks.CoreVideo}/Library/Frameworks"
          "-framework CoreVideo"
          "-F${apple_sdk.frameworks.CoreServices}/Library/Frameworks"
          "-framework CoreServices"
          "-F${apple_sdk.frameworks.IOKit}/Library/Frameworks"
          "-framework IOKit"
          "-F${apple_sdk.frameworks.Cocoa}/Library/Frameworks"
          "-framework Cocoa"
          "-F${apple_sdk.frameworks.QuartzCore}/Library/Frameworks"
          "-framework QuartzCore"
          "-F${apple_sdk.frameworks.Metal}/Library/Frameworks"
          "-framework Metal"
          "-F${apple_sdk.frameworks.AppKit}/Library/Frameworks"
          "-framework AppKit"
          "-F${apple_sdk.frameworks.Foundation}/Library/Frameworks"
          "-framework Foundation"
        ]
        ++ lib.optionals stdenv.hostPlatform.isWasm [
          "-I${zig}/lib/libc/include/wasm-freestanding-musl"
          "-I${zig}/lib/libc/include/generic-musl/"
          "-I${zig}/lib/libc/musl/include/"
          "-shared"
          "-Wl,--export=onInit"
        ];

      buildPhase = ''
        runHook preBuild

        $CC -O3 -o ${pname} ${
          if stdenv.hostPlatform.isDarwin
          then "main.m"
          else "main.c"
        } -lwgpu_native ${
          if stdenv.hostPlatform.isWasm
          then ""
          else "-lglfw3 -lunwind"
        }

        runHook postBuild
      '';

      installPhase = ''
        runHook preInstall

        mkdir -p $out/bin
        install -m755 ${pname} $out/bin/${pname}

        runHook postInstall
      '';

      # patch the built binaries if targetting NixOS
      # we use the normal stdenv here instead of stdenvNoCC because we require access to the NixOS C compiler
      # we also do some renaming here just to make the final binaries nicer
      postInstall =
        lib.optionalString nixos ''
          patchelf --set-interpreter $(cat ${stdenv'.cc}/nix-support/dynamic-linker) $out/bin/${pname}
          wrapProgram $out/bin/${pname} \
            --prefix LD_LIBRARY_PATH : ${lib.makeLibraryPath [wayland libxkbcommon vulkan-loader]}
        ''
        + lib.optionalString stdenv.hostPlatform.isMinGW ''
          mv $out/bin/${pname} $out/bin/${pname}.exe
        ''
        + lib.optionalString stdenv.hostPlatform.isWasm ''
          mv $out/bin/${pname} $out/bin/${pname}.wasm
        '';
    }
