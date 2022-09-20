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
    naga = {
      url = "github:gfx-rs/naga";
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
              linuxPkgs = {
                x86_64 = import nixpkgs {
                  localSystem = system;
                  crossSystem = if (system == "x86_64-linux") then null else { config = "x86_64-unknown-linux-gnu"; };
                  overlays = [ (import rust-overlay) ];
                };
                aarch64 = import nixpkgs {
                  localSystem = system;
                  crossSystem = { config = "aarch64-unknown-linux-gnu"; };
                  overlays = [ (import rust-overlay) ];
                };
              };
              windowsPkgs = import nixpkgs {
                localSystem = system;
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
                      runHook preInstall

                      mkdir -p $out/bin
                      nelua --cc $CC --release main.nelua -o $out/bin/game

                      runHook postInstall
                    '';
                  };
                in
                recurseIntoAttrs {
                  linux = recurseIntoAttrs {
                    x86_64 = linuxPkgs.x86_64.stdenv.mkDerivation (recursiveUpdate (baseDrv [ ]) {
                      buildInputs = with linuxPkgs.x86_64; [
                        xorg.libX11
                        xorg.libXrandr
                      ] ++ [
                        glfw.linux.x86_64
                        wgpu-native.linux.x86_64
                      ];
                    });
                    aarch64 = linuxPkgs.aarch64.stdenv.mkDerivation (recursiveUpdate (baseDrv [ ]) {
                      buildInputs = with linuxPkgs.aarch64; [
                        xorg.libX11
                        xorg.libXrandr
                      ] ++ [
                        glfw.linux.aarch64
                        wgpu-native.linux.aarch64
                      ];
                    });
                  };
                  windows = windowsPkgs.stdenv.mkDerivation (recursiveUpdate (baseDrv [ windows-nelua ]) {
                    buildInputs = with windowsPkgs; [
                    ] ++ [
                      glfw.windows
                      wgpu-native.windows
                    ];

                    postInstall = ''
                      cp ${glfw.windows}/bin/glfw3.dll $out/bin
                      cp ${wgpu-native.windows}/lib/wgpu_native.dll $out/bin
                    '';
                  });
                };

              # ===== REQUIRED LIBS/BUILD STUFF BELOW =====
              glfw =
                let
                  baseDrv = {
                    pname = "glfw";
                    version = inputs.glfw.shortRev;
                    src = inputs.glfw;

                    nativeBuildInputs = with pkgs; [ cmake ];

                    patches = [
                      ./nix/patches/glfw-x11.patch
                    ];

                    cmakeFlags = [ "-DBUILD_SHARED_LIBS=ON" "-DGLFW_BUILD_EXAMPLES=OFF" "-DGLFW_BUILD_TESTS=OFF" ];
                  };
                in
                recurseIntoAttrs {
                  linux = recurseIntoAttrs {
                    x86_64 = linuxPkgs.x86_64.stdenv.mkDerivation (recursiveUpdate baseDrv {
                      buildInputs = with linuxPkgs.x86_64; [ xorg.libX11 xorg.libXrandr xorg.libXinerama xorg.libXcursor xorg.libXi xorg.libXext ];
                    });
                    aarch64 = linuxPkgs.aarch64.stdenv.mkDerivation (recursiveUpdate baseDrv {
                      buildInputs = with linuxPkgs.aarch64; [ xorg.libX11 xorg.libXrandr xorg.libXinerama xorg.libXcursor xorg.libXi xorg.libXext ];
                    });
                  };
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
                    version = inputs.wgpu-native.shortRev;
                    src = inputs.wgpu-native;

                    nativeBuildInputs = with pkgs; [
                      rustPlatform.bindgenHook
                    ];

                    postPatch = ''
                      patch -p1 < ${./nix/patches/wgpu-native-nelua.patch} || true
                      patch -p1 < ${./nix/patches/wgpu-native-ffi.patch} || true
                    '';

                    preInstall = ''
                      mkdir -p $out/include

                      install -m664 ${inputs.wgpu-native}/ffi/webgpu-headers/webgpu.h $out/include
                      install -m664 ${inputs.wgpu-native}/ffi/wgpu.h $out/include
                      patch -d $out/include -p2 < ${./nix/patches/wgpu-native-ffi.patch}
                      sed -i -e 's/#include "webgpu-headers.*/#include <webgpu.h>/' $out/include/wgpu.h
                    '';

                    CARGO_PROFILE = "dev";
                  };
                in
                recurseIntoAttrs {
                  linux = recurseIntoAttrs {
                    x86_64 =
                      let
                        rustToolchain = linuxPkgs.x86_64.pkgsBuildHost.rust-bin.stable.latest.default.override {
                          targets = [
                            "x86_64-unknown-linux-gnu"
                          ];
                        };
                        rustPlatform = linuxPkgs.x86_64.makeRustPlatform {
                          rustc = rustToolchain;
                          cargo = rustToolchain;
                        };
                        craneLib = (crane.mkLib linuxPkgs.x86_64).overrideToolchain rustToolchain;
                      in
                      craneLib.buildPackage (recursiveUpdate baseDrv {
                        CARGO_BUILD_TARGET = "x86_64-unknown-linux-gnu";
                      });
                    aarch64 =
                      let
                        rustToolchain = linuxPkgs.aarch64.pkgsBuildHost.rust-bin.stable.latest.default.override {
                          targets = [
                            "aarch64-unknown-linux-gnu"
                          ];
                        };
                        rustPlatform = linuxPkgs.aarch64.makeRustPlatform {
                          rustc = rustToolchain;
                          cargo = rustToolchain;
                        };
                        craneLib = (crane.mkLib linuxPkgs.aarch64).overrideToolchain rustToolchain;
                      in
                      craneLib.buildPackage (recursiveUpdate baseDrv {
                        CARGO_BUILD_TARGET = "aarch64-unknown-linux-gnu";
                      });
                  };
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
                      CARGO_BUILD_TARGET = "x86_64-pc-windows-gnu";

                      buildInputs = with windowsPkgs; [ stdenv.cc windows.pthreads ];
                    });
                };
              naga =
                let
                  baseDrv = {
                    pname = "naga";
                    version = inputs.naga.shortRev;
                    src = inputs.naga;

                    cargoLock = ./nix/naga-cargo.lock;
                    cargoExtraArgs = "--all-features";

                    doCheck = false;
                  };
                in
                recurseIntoAttrs {
                  linux = recurseIntoAttrs {
                    x86_64 =
                      let
                        rustToolchain = linuxPkgs.x86_64.pkgsBuildHost.rust-bin.stable.latest.default.override {
                          targets = [
                            "x86_64-unknown-linux-gnu"
                          ];
                        };
                        rustPlatform = linuxPkgs.x86_64.makeRustPlatform {
                          rustc = rustToolchain;
                          cargo = rustToolchain;
                        };
                        craneLib = (crane.mkLib linuxPkgs.x86_64).overrideToolchain rustToolchain;
                      in
                      craneLib.buildPackage (recursiveUpdate baseDrv {
                        CARGO_BUILD_TARGET = "x86_64-unknown-linux-gnu";
                      });
                    aarch64 =
                      let
                        rustToolchain = linuxPkgs.aarch64.pkgsBuildHost.rust-bin.stable.latest.default.override {
                          targets = [
                            "aarch64-unknown-linux-gnu"
                          ];
                        };
                        rustPlatform = linuxPkgs.aarch64.makeRustPlatform {
                          rustc = rustToolchain;
                          cargo = rustToolchain;
                        };
                        craneLib = (crane.mkLib linuxPkgs.aarch64).overrideToolchain rustToolchain;
                      in
                      craneLib.buildPackage (recursiveUpdate baseDrv {
                        CARGO_BUILD_TARGET = "aarch64-unknown-linux-gnu";
                      });
                  };
                };

              # ===== NELUA =====
              nelua =
                pkgs.stdenv.mkDerivation rec {
                  pname = "nelua";
                  version = inputs.nelua.shortRev;
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
                  cp ${wgpu-native.linux.x86_64}/include/*.h .
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
                    zig
                    vulkan-validation-layers
                    vulkan-tools
                    vulkan-tools-lunarg
                  ] ++ [
                    packages.nelua
                    packages."glfw/linux/x86_64"
                    packages."wgpu-native/linux/x86_64"
                    packages."naga/linux/x86_64"
                  ];

                LD_LIBRARY_PATH = [ "${pkgs.vulkan-loader}/lib" ];
              };
        }
      );
}
