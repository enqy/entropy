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
    zig = {
      url = "github:mitchellh/zig-overlay";
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
      url = "github:glfw/glfw";
      flake = false;
    };
    naga = {
      url = "github:gfx-rs/naga";
      flake = false;
    };
  };

  outputs = inputs @ {
    self,
    nixpkgs,
    rust-overlay,
    zig,
    flake-utils,
    gitignore,
    crane,
    ...
  }: let
    inherit (nixpkgs.lib) recursiveUpdate recurseIntoAttrs;
    inherit (flake-utils.lib) eachSystem flattenTree;
    inherit (gitignore.lib) gitignoreSource;
  in
    # supported systems that we can run builds from
    eachSystem [
      "x86_64-linux"
    ]
    (
      system: let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [(import rust-overlay) zig.overlays.default];
        };
      in rec {
        packages = let
          linuxPkgs = {
            x86_64 = import nixpkgs {
              localSystem = system;
              crossSystem =
                if (system == "x86_64-linux")
                then null
                else {config = "x86_64-unknown-linux-gnu";};
              overlays = [(import rust-overlay)];
            };
            aarch64 = import nixpkgs {
              localSystem = system;
              crossSystem = {config = "aarch64-unknown-linux-gnu";};
              overlays = [(import rust-overlay)];
            };
          };
          windowsPkgs = {
            x86_64 = import nixpkgs {
              localSystem = system;
              crossSystem = {config = "x86_64-w64-mingw32";};
              overlays = [(import rust-overlay)];
            };
          };
        in
          flattenTree rec {
            game = let
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

                nativeBuildInputs = with pkgs;
                  [
                    nelua
                    zigpkgs.master
                  ]
                  ++ nelua_modules;

                # build NELUA_PATH so that nelua can find all of our modules
                preBuild = let
                  nelua_path = "./?.nelua;${nelua}/lib/nelua/lib/?.nelua;" + (nixpkgs.lib.foldr (module: path: "${module}/nelua/?.nelua;" + path) ";" (nelua_modules ++ extraModules));
                in ''
                  export HOME=$TMPDIR
                  export NELUA_PATH="${nelua_path}"
                '';

                # add all the nelua modules to the include path because they may contain headers
                CFLAGS = builtins.map (module: "-I${module}/include") (nelua_modules ++ extraModules);

                buildPhase = ''
                  runHook preBuild

                  nelua main.nelua --release --print-code > main.c

                  runHook postBuild
                '';

                installPhase = ''
                  runHook preInstall

                  mkdir -p $out/bin
                  zig cc -O3 -target $ZCC_TARGET main.c -o $out/bin/game $NIX_LDFLAGS $NIX_CFLAGS_COMPILE -lwgpu_native -lglfw3 -lunwind $ZCC_FLAGS

                  runHook postInstall
                '';
              };
            in
              recurseIntoAttrs rec {
                linux = recurseIntoAttrs {
                  x86_64 = linuxPkgs.x86_64.stdenv.mkDerivation (recursiveUpdate (baseDrv []) {
                    buildInputs = with linuxPkgs.x86_64;
                      [
                        wayland
                      ]
                      ++ [
                        glfw.linux.x86_64
                        wgpu-native.linux.x86_64
                      ];

                    postBuild = ''
                      export ZCC_TARGET=x86_64-linux-gnu.2.27
                      export ZCC_FLAGS="-lwayland-client"
                    '';
                  });
                  aarch64 = linuxPkgs.aarch64.stdenv.mkDerivation (recursiveUpdate (baseDrv []) {
                    buildInputs = with linuxPkgs.aarch64;
                      [
                        wayland
                      ]
                      ++ [
                        glfw.linux.aarch64
                        wgpu-native.linux.aarch64
                      ];

                    postBuild = ''
                      export ZCC_TARGET=aarch64-linux-gnu.2.27
                      export ZCC_FLAGS="-lwayland-client"
                    '';
                  });
                };
                nixos = recurseIntoAttrs {
                  x86_64 = linux.x86_64.overrideAttrs (old: {
                    nativeBuildInputs = old.nativeBuildInputs ++ [pkgs.makeWrapper];

                    postInstall = ''
                      patchelf --set-interpreter "$(cat $NIX_CC/nix-support/dynamic-linker)" $out/bin/game

                      wrapProgram $out/bin/game \
                        --prefix LD_LIBRARY_PATH : ${pkgs.lib.makeLibraryPath (with linuxPkgs.x86_64; [wayland libxkbcommon vulkan-loader])}
                    '';
                  });
                  aarch64 = linux.aarch64.overrideAttrs (old: {
                    nativeBuildInputs = old.nativeBuildInputs ++ [pkgs.makeWrapper];

                    postInstall = ''
                      patchelf --set-interpreter "$(cat $NIX_CC/nix-support/dynamic-linker)" $out/bin/game

                      wrapProgram $out/bin/game \
                        --prefix LD_LIBRARY_PATH : ${pkgs.lib.makeLibraryPath (with linuxPkgs.aarch64; [wayland libxkbcommon vulkan-loader])}
                    '';
                  });
                };
                windows = recurseIntoAttrs {
                  x86_64 = windowsPkgs.x86_64.stdenv.mkDerivation (recursiveUpdate (baseDrv [windows-nelua]) {
                    buildInputs = [
                      glfw.windows.x86_64
                      wgpu-native.windows.x86_64
                    ];

                    postBuild = ''
                      export ZCC_TARGET=x86_64-windows-gnu
                      export ZCC_FLAGS="-lc++ -lgdi32 -ld3dcompiler_47 -luserenv -lbcrypt -lws2_32"
                    '';

                    postInstall = ''
                      mv $out/bin/game $out/bin/game.exe
                    '';
                  });
                };
              };

            # ===== REQUIRED LIBS/BUILD STUFF BELOW =====
            glfw = let
              baseDrv = {
                pname = "glfw";
                version = inputs.glfw.shortRev;
                src = inputs.glfw;

                nativeBuildInputs = with pkgs; [cmake extra-cmake-modules];

                cmakeFlags = ["-DBUILD_SHARED_LIBS=OFF" "-DGLFW_BUILD_EXAMPLES=OFF" "-DGLFW_BUILD_TESTS=OFF" "-DGLFW_BUILD_DOCS=OFF" "-DGLFW_BUILD_WAYLAND=ON" "-DGLFW_BUILD_X11=OFF"];
              };
            in
              recurseIntoAttrs {
                linux = recurseIntoAttrs {
                  x86_64 = linuxPkgs.x86_64.stdenv.mkDerivation (recursiveUpdate baseDrv {
                    buildInputs = with linuxPkgs.x86_64; [wayland wayland-protocols libxkbcommon];
                  });
                  aarch64 = linuxPkgs.aarch64.stdenv.mkDerivation (recursiveUpdate baseDrv {
                    buildInputs = with linuxPkgs.aarch64; [wayland wayland-protocols libxkbcommon];
                  });
                };
                windows = recurseIntoAttrs {
                  x86_64 = windowsPkgs.x86_64.stdenv.mkDerivation (recursiveUpdate baseDrv {
                    # this is needed because some compilers look for .lib files to link for when compiling for windows
                    postInstall = ''
                      ln -fs $out/lib/libglfw3dll.a $out/lib/glfw3.lib
                    '';
                  });
                };
              };

            wgpu-native = let
              baseDrv = rustPlatform: {
                pname = "wgpu-native";
                version = inputs.wgpu-native.shortRev;
                src = inputs.wgpu-native;

                nativeBuildInputs = [
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

                doCheck = false;

                CARGO_PROFILE = "dev";
              };
            in
              recurseIntoAttrs {
                linux = recurseIntoAttrs {
                  x86_64 = let
                    rustToolchain = linuxPkgs.x86_64.pkgsBuildHost.rust-bin.stable.latest.default.override {
                      targets = [
                        "x86_64-unknown-linux-gnu"
                      ];
                    };
                    rustPlatform = linuxPkgs.x86_64.pkgsBuildHost.makeRustPlatform {
                      rustc = rustToolchain;
                      cargo = rustToolchain;
                    };
                    craneLib = (crane.mkLib pkgs).overrideToolchain rustToolchain;
                  in
                    craneLib.buildPackage (recursiveUpdate (baseDrv rustPlatform) {
                      CARGO_BUILD_TARGET = "x86_64-unknown-linux-gnu";
                    });
                  aarch64 = let
                    rustToolchain = linuxPkgs.aarch64.pkgsBuildHost.rust-bin.stable.latest.default.override {
                      targets = [
                        "aarch64-unknown-linux-gnu"
                      ];
                    };
                    rustPlatform = linuxPkgs.aarch64.pkgsBuildHost.makeRustPlatform {
                      rustc = rustToolchain;
                      cargo = rustToolchain;
                    };
                    craneLib = (crane.mkLib pkgs).overrideToolchain rustToolchain;
                  in
                    craneLib.buildPackage (recursiveUpdate (baseDrv rustPlatform) {
                      CARGO_BUILD_TARGET = "aarch64-unknown-linux-gnu";
                      CARGO_TARGET_AARCH64_UNKNOWN_LINUX_GNU_LINKER = "${linuxPkgs.aarch64.pkgsBuildHost.gcc}/bin/aarch64-unknown-linux-gnu-gcc";
                    });
                };
                windows = recurseIntoAttrs {
                  x86_64 = let
                    rustToolchain = windowsPkgs.x86_64.pkgsBuildHost.rust-bin.stable.latest.default.override {
                      targets = [
                        "x86_64-pc-windows-gnu"
                      ];
                    };
                    rustPlatform = pkgs.makeRustPlatform {
                      rustc = rustToolchain;
                      cargo = rustToolchain;
                    };
                    craneLib = (crane.mkLib pkgs).overrideToolchain rustToolchain;
                  in
                    craneLib.buildPackage (recursiveUpdate (baseDrv rustPlatform) (let
                      zcc = pkgs.writeShellScriptBin "zcc" ''
                        set -x

                        # remove specific args from arg list
                        declare -a args=()
                        for arg in "$@"; do
                          case "$arg" in
                            *compiler_builtins*) ;;
                            -lwindows) ;;
                            -l:libpthread.a) ;;
                            -lgcc) ;;
                            -lgcc_eh) args+=("-lc++") ;;
                            -lgcc_s) args+=("-lunwind") ;;
                            *) args+=("$arg") ;;
                          esac
                        done

                        ${pkgs.zigpkgs.master}/bin/zig cc -target x86_64-windows-gnu $NIX_CFLAGS_COMPILE $NIX_LDFLAGS "$''\{args[@]}" -v
                      '';
                    in {
                      CARGO_BUILD_TARGET = "x86_64-pc-windows-gnu";
                      CARGO_TARGET_X86_64_PC_WINDOWS_GNU_LINKER = "${zcc}/bin/zcc";

                      preBuild = ''
                        export HOME=$TMPDIR
                      '';

                      postInstall = ''
                        if [ -f $out/lib/libwgpu_native.a ]; then
                          # objcopy --weaken $out/lib/libwgpu_native.a
                          ar t $out/lib/libwgpu_native.a | grep compiler_builtins | xargs -I % ar dv $out/lib/libwgpu_native.a %
                        fi
                      '';
                    }));
                };
              };

            naga = let
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
                  x86_64 = let
                    rustToolchain = linuxPkgs.x86_64.pkgsBuildHost.rust-bin.stable.latest.default.override {
                      targets = [
                        "x86_64-unknown-linux-gnu"
                      ];
                    };
                    craneLib = (crane.mkLib linuxPkgs.x86_64).overrideToolchain rustToolchain;
                  in
                    craneLib.buildPackage (recursiveUpdate baseDrv {
                      CARGO_BUILD_TARGET = "x86_64-unknown-linux-gnu";
                    });
                };
              };

            # ===== NELUA =====
            nelua = pkgs.stdenv.mkDerivation {
              pname = "nelua";
              version = inputs.nelua.shortRev;
              src = inputs.nelua;

              patchPhase = ''
                # patch out hardcoded CC
                sed -i -e 's/CC=.*//' Makefile
              '';

              makeFlags = ["PREFIX=$(out)"];
            };

            nelua-decl = pkgs.stdenv.mkDerivation rec {
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
            glfw-nelua = pkgs.runCommand "glfw-nelua" {} ''
              mkdir -p $out/nelua
              cp ${nelua-decl}/nelua/glfw.nelua $out/nelua
              sed -i -e 's/linklib .GL.//' $out/nelua/glfw.nelua
              sed -i -e 's/linklib .opengl32.//' $out/nelua/glfw.nelua
              sed -i -e '1s;^;## cdefine "GLFW_INCLUDE_NONE"\n;' $out/nelua/glfw.nelua
              sed -i -e 's/linklib .glfw.$/linklib "glfw3"/' $out/nelua/glfw.nelua
            '';

            glfwnative-nelua = let
              glfwnative_nelua = pkgs.writeText "glfwnative.nelua" ''
                ##[[
                if ccinfo.is_windows then
                  cdefine 'GLFW_EXPOSE_NATIVE_WIN32'
                else
                  cdefine 'GLFW_EXPOSE_NATIVE_WAYLAND'
                end
                cinclude '<GLFW/glfw3native.h>'
                ]]

                ## if ccinfo.is_windows then
                  require 'windows'

                  global function glfwGetWin32Adapter(monitor: *GLFWmonitor): cstring <cimport,nodecl> end
                  global function glfwGetWin32Monitor(monitor: *GLFWmonitor): cstring <cimport,nodecl> end
                  global function glfwGetWin32Window(window: *GLFWwindow): HWND <cimport,nodecl> end
                ## else
                  global wl_display: type <cimport,nodecl> = @record{}
                  global wl_output: type <cimport,nodecl> = @record{}
                  global wl_surface: type <cimport,nodecl> = @record{}

                  global function glfwGetWaylandDisplay(): *wl_display <cimport,nodecl> end
                  global function glfwGetWaylandMonitor(monitor: *GLFWmonitor): *wl_output <cimport,nodecl> end
                  global function glfwGetWaylandWindow(window: *GLFWwindow): *wl_surface <cimport,nodecl> end
                ## end
              '';
            in
              pkgs.runCommand "glfwnative-nelua" {} ''
                mkdir -p $out/nelua
                cp ${glfwnative_nelua} $out/nelua/glfwnative.nelua
              '';

            wgpu-nelua = let
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
              pkgs.runCommandCC "wgpu-nelua" {} ''
                cp ${wgpu-native.linux.x86_64}/include/*.h .
                cp ${wgpu_lua} wgpu.lua
                cp ${wgpu_c} wgpu.c

                mkdir -p $out/nelua/
                export LUA_PATH="${nelua-decl}/lib/?.lua;;"
                gcc -fplugin=${nelua-decl}/lib/gcclua.so -fplugin-arg-gcclua-script=wgpu.lua -S wgpu.c -I. > $out/nelua/wgpu.nelua

                mkdir -p $out/include
                cp *.h $out/include
              '';

            windows-nelua = pkgs.runCommand "windows-nelua" {} ''
              mkdir -p $out/nelua
              cp ${nelua-decl}/nelua/windows.nelua $out/nelua
            '';

            # ===== ACTUAL ENTROPY ENGINE =====
            entropy = let
              src = gitignoreSource ./entropy;
            in
              pkgs.runCommand "entropy" {} ''
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
                gdb
                libxkbcommon
                pkg-config
                renderdoc
                valgrind
                vulkan-tools
                vulkan-tools-lunarg
                vulkan-validation-layers
                wayland
                wine64
                zigpkgs.master
              ]
              ++ [
                # need to wrap nelua here to pass correct LD_LIBRARY_PATH
                (packages.nelua.overrideAttrs (old: {
                  nativeBuildInputs = [pkgs.makeWrapper];

                  postInstall = ''
                    wrapProgram $out/bin/nelua \
                      --prefix LD_LIBRARY_PATH : ${pkgs.lib.makeLibraryPath (with pkgs; [wayland libxkbcommon vulkan-loader])}
                  '';
                }))
                packages."glfw/linux/x86_64"
                packages."wgpu-native/linux/x86_64"
                # packages."naga/linux/x86_64"
              ];
          };
      }
    );
}
