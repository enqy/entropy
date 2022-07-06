{
  description = "entropy: A nix + nelua 3d/vr experience framework";

  inputs = {
    # nixpkgs and other packages
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    rust-overlay = {
      url = "github:oxalica/rust-overlay";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-utils.follows = "flake-utils";
      };
    };

    # utils
    flake-utils = {
      url = "github:numtide/flake-utils";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    gitignore = {
      url = "github:hercules-ci/gitignore.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    crane = {
      url = "github:ipetkov/crane";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-utils.follows = "flake-utils";
      };
    };

    # dependencies
    nelua = {
      url = "github:edubart/nelua-lang";
      flake = false;
    };
    wgpu-native = {
      url = "git+https://github.com/gfx-rs/wgpu-native?submodules=1";
      flake = false;
    };
    glfw = {
      url = "github:glfw/glfw/3.3-stable";
      flake = false;
    };
  };

  outputs = inputs@{ self, nixpkgs, rust-overlay, flake-utils, gitignore, crane, ... }:
    let
      inherit (nixpkgs.lib) recursiveUpdate recurseIntoAttrs optional;
      inherit (flake-utils.lib) eachSystem flattenTree;
      inherit (gitignore.lib) gitignoreSource;
    in
    # supported systems that we can run builds from
    eachSystem [
      "x86_64-linux"
    ]
      (
        system:
        let
          pkgs = import nixpkgs {
            inherit system;
            overlays = [ (import rust-overlay) ];
          };
        in
        rec {
          packages =
            let
              linuxPkgs = import nixpkgs {
                inherit system;
                crossSystem = if (system != "x86_64-linux") then { config = "x86_64-linux"; } else null;
                overlays = [ (import rust-overlay) ];
              };
              windowsPkgs = import nixpkgs {
                inherit system;
                crossSystem = { config = "x86_64-w64-mingw32"; };
                overlays = [ (import rust-overlay) ];
              };
            in
            flattenTree rec {
              game =
                let
                  nelua_modules = [
                    glfw-nelua
                    glfwnative-nelua
                    wgpu-nelua

                    entropy
                  ];

                  baseDrv = extraModules: {
                    pname = "game";
                    version = "0.1.0";

                    src = gitignoreSource ./.;

                    nativeBuildInputs = [
                      nelua
                    ] ++ nelua_modules;

                    # build NELUA_PATH so that nelua can find all of our modules
                    preBuild =
                      let
                        nelua_path = "./?.nelua;${nelua}/lib/nelua/lib/?.nelua;" + (nixpkgs.lib.foldr (module: path: "${module}/nelua/?.nelua;" + path) ";" (nelua_modules ++ extraModules));
                      in
                      ''
                        export HOME=$TMPDIR
                        export NELUA_PATH="${nelua_path}"
                      '';

                    # add all the nelua modules to the include path because they may contain headers
                    CFLAGS = builtins.map (module: "-I${module}/include") (nelua_modules ++ extraModules);

                    installPhase = ''
                      mkdir -p $out/bin
                      nelua --cc $CC main.nelua -o $out/bin/game

                      runHook postInstall
                    '';
                  };
                in
                recurseIntoAttrs {
                  linux = linuxPkgs.stdenv.mkDerivation (recursiveUpdate (baseDrv [ ]) {
                    buildInputs = with linuxPkgs; [
                      xorg.libX11
                      xorg.libXrandr
                    ] ++ [
                      glfw.linux
                      wgpu-native.linux
                    ];
                  });
                  windows = windowsPkgs.stdenv.mkDerivation (recursiveUpdate (baseDrv [ windows-nelua ]) {
                    buildInputs = with windowsPkgs; [
                    ] ++ [
                      glfw.windows
                      wgpu-native.windows
                    ];

                    postInstall = ''
                      cp ${glfw.windows}/bin/glfw3.dll $out/bin
                      cp ${wgpu-native.windows}/bin/wgpu_native.dll $out/bin
                    '';
                  });
                };

              # ===== REQUIRED LIBS/BUILD STUFF BELOW =====
              glfw =
                let
                  baseDrv = {
                    pname = "glfw";
                    version = inputs.glfw.rev;
                    src = inputs.glfw;

                    nativeBuildInputs = with pkgs; [ cmake ];

                    cmakeFlags = [ "-DBUILD_SHARED_LIBS=ON" "-DGLFW_BUILD_EXAMPLES=OFF" "-DGLFW_BUILD_TESTS=OFF" ];
                  };
                in
                recurseIntoAttrs {
                  linux = linuxPkgs.stdenv.mkDerivation (recursiveUpdate baseDrv {
                    patches =
                      let
                        x11_patch = pkgs.writeText "x11.patch" ''
                          diff --git a/src/CMakeLists.txt b/src/CMakeLists.txt
                          index a0be580e..ba143851 100644
                          --- a/src/CMakeLists.txt
                          +++ b/src/CMakeLists.txt
                          @@ -219,6 +219,13 @@ if (GLFW_BUILD_X11)
                               if (NOT X11_Xshape_INCLUDE_PATH)
                                   message(FATAL_ERROR "X Shape headers not found; install libxext development package")
                               endif()
                          +
                          +    target_link_libraries(glfw PRIVATE ''\${X11_Xrandr_LIB}
                          +                                       ''\${X11_Xinerama_LIB}
                          +                                       ''\${X11_Xkb_LIB}
                          +                                       ''\${X11_Xcursor_LIB}
                          +                                       ''\${X11_Xi_LIB}
                          +                                       ''\${X11_Xshape_LIB})
                           endif()

                           if (UNIX AND NOT APPLE)
                        '';
                      in
                      [ x11_patch ];

                    buildInputs = with linuxPkgs; [ xorg.libX11 xorg.libXrandr xorg.libXinerama xorg.libXcursor xorg.libXi xorg.libXext ];
                  });
                  windows = windowsPkgs.stdenv.mkDerivation (recursiveUpdate baseDrv {
                    # this is needed because some compilers look for .lib files to link for when compiling for windows
                    postInstall = ''
                      ln -fs $out/lib/libglfw3dll.a $out/lib/glfw3.lib
                    '';
                  });
                };

              wgpu-native =
                let
                  baseDrv = {
                    pname = "wgpu-native";
                    version = inputs.wgpu-native.rev;
                    src = inputs.wgpu-native;

                    nativeBuildInputs = with pkgs; [
                      rustPlatform.bindgenHook
                    ];

                    preInstall = ''
                      mkdir -p $out/include

                      cp ${inputs.wgpu-native}/ffi/webgpu-headers/webgpu.h $out/include
                      cp ${inputs.wgpu-native}/ffi/wgpu.h $out/include
                      sed -i -e 's/#include "webgpu-headers.*/#include <webgpu.h>/' $out/include/wgpu.h
                    '';
                  };
                in
                recurseIntoAttrs {
                  linux =
                    let
                      rustToolchain = pkgs.pkgsBuildHost.rust-bin.stable.latest.default.override {
                        targets = [
                          "x86_64-unknown-linux-gnu"
                        ];
                      };
                      rustPlatform = linuxPkgs.makeRustPlatform {
                        rustc = rustToolchain;
                        cargo = rustToolchain;
                      };
                      craneLib = (crane.mkLib linuxPkgs).overrideToolchain rustToolchain;
                    in
                    craneLib.buildPackage (recursiveUpdate baseDrv { });
                  windows =
                    let
                      rustToolchain = windowsPkgs.pkgsBuildHost.rust-bin.stable.latest.default.override {
                        targets = [
                          "x86_64-pc-windows-gnu"
                        ];
                      };
                      rustPlatform = windowsPkgs.makeRustPlatform {
                        rustc = rustToolchain;
                        cargo = rustToolchain;
                      };
                      craneLib = (crane.mkLib windowsPkgs).overrideToolchain rustToolchain;
                    in
                    craneLib.buildPackage (recursiveUpdate baseDrv {
                      # this is needed because some compilers look for .lib files to link for when compiling for windows
                      postInstall = ''
                        ln -fs $out/lib/libwgpu_native.a $out/lib/wgpu_native.lib
                      '';
                    });
                };

              # ===== NELUA =====
              nelua =
                pkgs.stdenv.mkDerivation rec {
                  pname = "nelua";
                  version = inputs.nelua.rev;
                  src = inputs.nelua;

                  patchPhase = ''
                    # patch out hardcoded CC
                    sed -i -e 's/CC=.*//' Makefile
                  '';

                  makeFlags = [ "PREFIX=$(out)" ];
                };

              nelua-decl =
                pkgs.stdenv.mkDerivation rec {
                  pname = "nelua-decl";
                  version = "63b4b40a582d9e6ceb697d6e58220e164ffd91fc";

                  src = pkgs.fetchFromGitHub {
                    owner = "edubart";
                    repo = "nelua-decl";
                    rev = version;
                    fetchSubmodules = true;
                    sha256 = "sha256-Kh1HeTz4AFCoZeeIbrxtLR5bGJtSDECjxTZImIH5kPg=";
                  };

                  nativeBuildInputs = with pkgs; [
                    pkg-config
                  ];

                  buildInputs = with pkgs; [
                    gmp
                    lua
                  ];

                  buildPhase = ''
                    make -C gcc-lua
                  '';

                  installPhase = ''
                    mkdir -p $out/lib
                    cp gcc-lua/gcc/gcclua.so $out/lib/
                    cp *.lua $out/lib/

                    mkdir -p $out/nelua
                    shopt -s globstar
                    for f in **/*.nelua; do
                      cp "$f" $out/nelua
                    done
                  '';
                };

              # ===== NELUA BINDINGS =====
              glfw-nelua =
                pkgs.runCommand "glfw-nelua" { } ''
                  mkdir -p $out/nelua
                  cp ${nelua-decl}/nelua/glfw.nelua $out/nelua
                  sed -i -e 's/linklib .GL.//' $out/nelua/glfw.nelua
                  sed -i -e 's/linklib .opengl32.//' $out/nelua/glfw.nelua
                  sed -i -e '1s;^;## cdefine "GLFW_INCLUDE_NONE"\n;' $out/nelua/glfw.nelua
                '';

              glfwnative-nelua =
                let
                  glfwnative_nelua = pkgs.writeText "glfwnative.nelua" ''
                    ##[[
                    if ccinfo.is_windows then
                      cdefine 'GLFW_EXPOSE_NATIVE_WIN32'
                    else
                      cdefine 'GLFW_EXPOSE_NATIVE_X11'
                    end
                    cinclude '<GLFW/glfw3native.h>'
                    ]]

                    ## if ccinfo.is_windows then
                      require 'windows'

                      global function glfwGetWin32Adapter(monitor: *GLFWmonitor): cstring <cimport,nodecl> end
                      global function glfwGetWin32Monitor(monitor: *GLFWmonitor): cstring <cimport,nodecl> end
                      global function glfwGetWin32Window(window: *GLFWwindow): HWND <cimport,nodecl> end
                    ## else
                      global Display: type <cimport,nodecl> = @record{}

                      global function glfwGetX11Display(): *Display <cimport,nodecl> end
                      global function glfwGetX11Adapter(monitor: *GLFWmonitor): culong <cimport,nodecl> end
                      global function glfwGetX11Monitor(monitor: *GLFWmonitor): culong <cimport,nodecl> end
                      global function glfwGetX11Window(window: *GLFWwindow): culong <cimport,nodecl> end
                      global function glfwSetX11SelectionString(string: cstring): void <cimport,nodecl> end
                      global function glfwGetX11SelectionString(): cstring <cimport,nodecl> end
                    ## end
                  '';
                in
                pkgs.runCommand "glfwnative-nelua" { } ''
                  mkdir -p $out/nelua
                  cp ${glfwnative_nelua} $out/nelua/glfwnative.nelua
                '';

              wgpu-nelua =
                let
                  wgpu_lua = pkgs.writeText "wgpu.lua" ''
                    local nldecl = require 'nldecl'

                    nldecl.include_names = {
                      '^WGPU',
                      '^wgpu',
                    }

                    nldecl.prepend_code = [=[
                    ##[[
                    cinclude '<webgpu.h>'
                    cinclude '<wgpu.h>'
                    linklib 'wgpu_native'
                    ]]
                    ]=]
                  '';
                  wgpu_c = pkgs.writeText "wgpu.c" ''
                    #include "webgpu.h"
                    #include "wgpu.h"
                  '';
                in
                pkgs.runCommandCC "wgpu-nelua" { } ''
                  cp ${wgpu-native.linux}/include/*.h .
                  cp ${wgpu_lua} wgpu.lua
                  cp ${wgpu_c} wgpu.c

                  mkdir -p $out/nelua/
                  export LUA_PATH="${nelua-decl}/lib/?.lua;;"
                  gcc -fplugin=${nelua-decl}/lib/gcclua.so -fplugin-arg-gcclua-script=wgpu.lua -S wgpu.c -I. > $out/nelua/wgpu.nelua

                  mkdir -p $out/include
                  cp *.h $out/include
                '';

              windows-nelua =
                pkgs.runCommand "windows-nelua" { } ''
                  mkdir -p $out/nelua
                  cp ${nelua-decl}/nelua/windows.nelua $out/nelua
                '';

              # ===== ACTUAL ENTROPY ENGINE =====
              entropy =
                let
                  src = gitignoreSource ./entropy;
                in
                pkgs.runCommand "entropy" { } ''
                  mkdir -p $out/nelua
                  cp -R ${src} $out/nelua/entropy
                '';
            };

          devShells.default =
            pkgs.mkShell
              {
                nativeBuildInputs = with pkgs;
                  [
                    gcc
                    xorg.libX11
                    xorg.libXrandr
                    wine64
                  ] ++ [
                    packages.nelua
                    packages."glfw/linux"
                    packages."wgpu-native/linux"
                  ];

                LD_LIBRARY_PATH = [ "${pkgs.vulkan-loader}/lib" ];
              };
        }
      );
}
