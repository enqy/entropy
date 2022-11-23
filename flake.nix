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
    inherit (nixpkgs.lib) recurseIntoAttrs;
    inherit (flake-utils.lib) eachSystem flattenTree;
    inherit (gitignore.lib) gitignoreSource;
  in
    # supported systems that we can run builds from
    eachSystem [
      "x86_64-linux"
      "aarch64-linux"
      "x86_64-darwin"
    ]
    (
      system: let
        overlay = final: prev: {
          zig-cc = final.writeShellScriptBin "zig-cc" ''
            set -x
            # remove specific args from host cc arg list
            declare -a args=()
            for arg in "$@"; do
              case "$arg" in
                *compiler_builtins*)
                  if [[ "$ZIG_CC_TARGET" != "x86_64-windows-gnu" ]]; then
                    args+=("$arg")
                  fi
                ;;
                -lwindows) ;;
                -l:libpthread.a) ;;
                -lgcc) ;;
                -lgcc_eh) args+=("-lc++") ;;
                -lgcc_s) args+=("-lunwind") ;;
                -liconv) ;;
                *) args+=("$arg") ;;
              esac
            done

            # cursed hack to use stdenv cc for rust build scripts so that they can run properly on the host system
            if printf '%s\0' "$''\{args[@]}" | grep -qz -- 'build[_-]script'; then
              ${final.stdenv.cc}/bin/cc "$@"
            else
              ${final.zigpkgs.master}/bin/zig cc $ZIG_CC_FLAGS -target $ZIG_CC_TARGET $CC_FLAGS $NIX_CFLAGS_COMPILE "$''\{args[@]}"
            fi
          '';
          zig-ld = final.writeShellScriptBin "zig-ld" ''
            exec ${final.zig-cc}/bin/zig-cc $NIX_LDFLAGS "$@"
          '';
          zig-ar = final.writeShellScriptBin "zig-ar" ''
            if [[ "$ZIG_CC_TARGET" == "x86_64-apple-none" ]] || [[ "$ZIG_CC_TARGET" == "aarch64-apple-none" ]]; then
              exec ${final.zigpkgs.master}/bin/zig ar --format=darwin "$@"
            else
              exec ${final.zigpkgs.master}/bin/zig ar "$@"
            fi
          '';
          zig-dlltool = final.writeShellScriptBin "zig-dlltool" ''
            exec ${final.zigpkgs.master}/bin/zig dlltool "$@"
          '';
          zig-lib = final.writeShellScriptBin "zig-lib" ''
            exec ${final.zigpkgs.master}/bin/zig lib "$@"
          '';
          zig-ranlib = final.writeShellScriptBin "zig-ranlib" ''
            exec ${final.zigpkgs.master}/bin/zig ranlib "$@"
          '';
          zig-rc = final.writeShellScriptBin "zig-rc" ''
            exec ${final.zig-cc}/bin/zig-cc "$@"
          '';
        };
        overlays = [
          overlay
          (import rust-overlay)
          zig.overlays.default
        ];
        pkgs = import nixpkgs {
          inherit system overlays;
        };
      in rec {
        packages = let
          linuxPkgs = {
            x86_64 = import nixpkgs {
              inherit overlays;
              localSystem = system;
              crossSystem =
                if (system == "x86_64-linux")
                then null
                else {config = "x86_64-unknown-linux-gnu";};
              config.allowUnsupportedSystem = true;
              config.allowBroken = true;
            };
            aarch64 = import nixpkgs {
              inherit overlays;
              localSystem = system;
              crossSystem = {config = "aarch64-unknown-linux-gnu";};
              config.allowUnsupportedSystem = true;
              config.allowBroken = true;
            };
          };
          windowsPkgs = {
            x86_64 = import nixpkgs {
              inherit overlays;
              localSystem = system;
              crossSystem = {config = "x86_64-w64-mingw32";};
              config.allowUnsupportedSystem = true;
            };
          };
          darwinPkgs = let
            overlays' =
              overlays
              ++ [
                (final: prev: {
                  darwin =
                    prev.darwin
                    // {
                      rewrite-tbd =
                        (prev.darwin.rewrite-tbd.override {
                          stdenv = final.llvmPackages.stdenv;
                        })
                        .overrideAttrs (old: {
                          patches = [
                            (final.fetchpatch {
                              url = "https://patch-diff.githubusercontent.com/raw/thefloweringash/rewrite-tbd/pull/1.patch";
                              sha256 = "sha256-YYU7EfA4vIUAhvSxiuiOvpHLIJjT46aIdnpWvU5YJnE=";
                            })
                          ];
                        });
                      apple_sdk = prev.pkgsBuildBuild.darwin.apple_sdk_11_0;
                      LibsystemCross = prev.pkgsBuildBuild.darwin.apple_sdk_11_0.Libsystem;
                    };
                })
              ];
          in {
            x86_64 = import nixpkgs {
              localSystem = system;
              crossSystem = {config = "x86_64-apple-darwin";};
              config.allowUnsupportedSystem = true;
              overlays = overlays';
            };
            aarch64 = import nixpkgs {
              localSystem = system;
              crossSystem = {config = "aarch64-apple-darwin";};
              config.allowUnsupportedSystem = true;
              overlays = overlays';
            };
          };
          rustToolchain = pkgs.rust-bin.stable.latest.default.override {
            targets = [
              "x86_64-unknown-linux-gnu"
              "aarch64-unknown-linux-gnu"
              "x86_64-pc-windows-gnu"
              "x86_64-apple-darwin"
              "aarch64-apple-darwin"
            ];
          };
        in
          flattenTree rec {
            app = recurseIntoAttrs {
              linux = recurseIntoAttrs {
                x86_64 = linuxPkgs.x86_64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs;
                  glfw = glfw.linux.x86_64;
                  wgpu-native = wgpu-native.linux.x86_64;
                } {};
                aarch64 = linuxPkgs.aarch64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs;
                  glfw = glfw.linux.aarch64;
                  wgpu-native = wgpu-native.linux.aarch64;
                } {};
              };
              nixos = recurseIntoAttrs {
                x86_64 =
                  linuxPkgs.x86_64.callPackage ./nix/app {
                    inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs;
                    glfw = glfw.linux.x86_64;
                    wgpu-native = wgpu-native.linux.x86_64;
                  } {
                    nixos = true;
                  };
                aarch64 =
                  linuxPkgs.aarch64.callPackage ./nix/app {
                    inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs;
                    glfw = glfw.linux.aarch64;
                    wgpu-native = wgpu-native.linux.aarch64;
                  } {
                    nixos = true;
                  };
              };
              windows = recurseIntoAttrs {
                x86_64 = windowsPkgs.x86_64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy windows-nelua inputs;
                  glfw = glfw.windows.x86_64;
                  wgpu-native = wgpu-native.windows.x86_64;
                } {};
              };
              darwin = recurseIntoAttrs {
                x86_64 = darwinPkgs.x86_64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs;
                  glfw = glfw.darwin.x86_64;
                  wgpu-native = wgpu-native.darwin.x86_64;
                } {};
                aarch64 = darwinPkgs.aarch64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs;
                  glfw = glfw.darwin.aarch64;
                  wgpu-native = wgpu-native.darwin.aarch64;
                } {};
              };
            };

            # ===== REQUIRED LIBS/BUILD STUFF BELOW =====
            glfw = recurseIntoAttrs {
              linux = recurseIntoAttrs {
                x86_64 = linuxPkgs.x86_64.callPackage ./nix/glfw {inherit inputs;};
                aarch64 = linuxPkgs.aarch64.callPackage ./nix/glfw {inherit inputs;};
              };
              windows = recurseIntoAttrs {
                x86_64 = windowsPkgs.x86_64.callPackage ./nix/glfw {inherit inputs;};
              };
              darwin = recurseIntoAttrs {
                x86_64 = darwinPkgs.x86_64.callPackage ./nix/glfw {inherit inputs;};
                aarch64 = darwinPkgs.aarch64.callPackage ./nix/glfw {inherit inputs;};
              };
            };

            wgpu-native = recurseIntoAttrs {
              linux = recurseIntoAttrs {
                x86_64 = let
                  craneLib = (crane.mkLib linuxPkgs.x86_64).overrideToolchain rustToolchain;
                in
                  linuxPkgs.x86_64.callPackage ./nix/wgpu-native {
                    inherit craneLib inputs;
                  };
                aarch64 = let
                  craneLib = (crane.mkLib linuxPkgs.aarch64).overrideToolchain rustToolchain;
                in
                  linuxPkgs.aarch64.callPackage ./nix/wgpu-native {
                    inherit craneLib inputs;
                  };
              };
              windows = recurseIntoAttrs {
                x86_64 = let
                  rustPlatform = pkgs.makeRustPlatform {
                    rustc = rustToolchain;
                    cargo = rustToolchain;
                  };
                  craneLib = (crane.mkLib windowsPkgs.x86_64).overrideToolchain rustToolchain;
                in
                  windowsPkgs.x86_64.callPackage ./nix/wgpu-native {
                    inherit craneLib inputs rustPlatform;
                  };
              };
              darwin = recurseIntoAttrs {
                x86_64 = let
                  craneLib = (crane.mkLib pkgs).overrideToolchain rustToolchain;
                in
                  darwinPkgs.x86_64.callPackage ./nix/wgpu-native {
                    inherit craneLib inputs;
                  };
                aarch64 = let
                  craneLib = (crane.mkLib pkgs).overrideToolchain rustToolchain;
                in
                  darwinPkgs.aarch64.callPackage ./nix/wgpu-native {
                    inherit craneLib inputs;
                  };
              };
            };

            naga = recurseIntoAttrs {
              linux = recurseIntoAttrs {
                x86_64 = let
                  craneLib = (crane.mkLib linuxPkgs.x86_64).overrideToolchain rustToolchain;
                in
                  linuxPkgs.x86_64.callPackage ./nix/naga {
                    inherit craneLib inputs;
                  };
              };
            };

            # ===== NELUA =====
            nelua = pkgs.callPackage ./nix/nelua {inherit inputs;};

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
                gcc
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

              mkdir -p $out/include/GLFW
              cp ${inputs.glfw}/include/GLFW/glfw3.h $out/include/GLFW
              cp ${inputs.glfw}/include/GLFW/glfw3native.h $out/include/GLFW
            '';

            glfwnative-nelua = let
              glfwnative_nelua = pkgs.writeText "glfwnative.nelua" ''
                ##[[
                if ccinfo.is_windows then
                  cdefine 'GLFW_EXPOSE_NATIVE_WIN32'
                elseif ccinfo.is_linux then
                  cdefine 'GLFW_EXPOSE_NATIVE_WAYLAND'
                elseif ccinfo.is_apple then
                  cdefine 'GLFW_EXPOSE_NATIVE_COCOA'
                  cinclude '<QuartzCore/CAMetalLayer.h>'
                end
                cinclude '<GLFW/glfw3native.h>'
                ]]

                ## if ccinfo.is_windows then
                  require 'windows'

                  global function glfwGetWin32Adapter(monitor: *GLFWmonitor): cstring <cimport,nodecl> end
                  global function glfwGetWin32Monitor(monitor: *GLFWmonitor): cstring <cimport,nodecl> end
                  global function glfwGetWin32Window(window: *GLFWwindow): HWND <cimport,nodecl> end
                ## elseif ccinfo.is_linux then
                  global wl_display: type <cimport,nodecl> = @record{}
                  global wl_output: type <cimport,nodecl> = @record{}
                  global wl_surface: type <cimport,nodecl> = @record{}

                  global function glfwGetWaylandDisplay(): *wl_display <cimport,nodecl> end
                  global function glfwGetWaylandMonitor(monitor: *GLFWmonitor): *wl_output <cimport,nodecl> end
                  global function glfwGetWaylandWindow(window: *GLFWwindow): *wl_surface <cimport,nodecl> end
                ## elseif ccinfo.is_apple then
                  global CGDirectDisplayID: type <cimport,nodecl> = @record{}
                  global NSWindow: type <cimport,nodecl> = @record{}

                  global function glfwGetCocoaMonitor(monitor: *GLFWmonitor): CGDirectDisplayID <cimport,nodecl> end
                  global function glfwGetCocoaWindow(window: *GLFWwindow): NSWindow <cimport,nodecl> end
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
              pkgs.runCommand "wgpu-nelua" {
                nativeBuildInputs = with pkgs; [
                  gcc
                ];
              } ''
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
