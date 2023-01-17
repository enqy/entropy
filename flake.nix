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
    nelua-decl = {
      url = "git+https://github.com/edubart/nelua-decl.git?submodules=1";
      flake = false;
    };
    wgpu-native = {
      url = "git+https://github.com/wozeparrot/wgpu-native.git?submodules=1";
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
      # "x86_64-darwin" # currently broken
    ]
    (
      system: let
        zig_overlay = final: prev: {
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
                -lgcc_s)
                  if [[ "$ZIG_CC_TARGET" != "wasm32-freestanding" ]]; then
                    args+=("-lunwind")
                  fi
                ;;
                -liconv) ;;
                --gc-sections) ;;
                *) args+=("$arg") ;;
              esac
            done

            # cursed hack to use stdenv cc for rust build scripts so that they can run properly on the host system
            if printf '%s\0' "$''\{args[@]}" | grep -qz -- 'build[_-]script'; then
              ${final.stdenv.cc}/bin/cc "$@"
            elif printf '%s\0' "$''\{args[@]}" | grep -qz -- 'symbols\.o' && [[ "$ZIG_CC_TARGET" == "wasm32-freestanding" ]]; then
              # cursed hack for wasm
              ${final.zigpkgs.master}/bin/zig cc $ZIG_CC_FLAGS $NIX_LDFLAGS $CC_FLAGS $NIX_CFLAGS_COMPILE "$''\{args[@]}"
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
          zig_overlay
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
              crossSystem = "x86_64-linux";
            };
            aarch64 = import nixpkgs {
              inherit overlays;
              localSystem = system;
              crossSystem = "aarch64-linux";
            };
          };
          windowsPkgs = {
            x86_64 = import nixpkgs {
              inherit overlays;
              localSystem = system;
              crossSystem = "x86_64-w64-mingw32";
              config.allowUnsupportedSystem = true;
            };
          };
          darwinPkgs = let
            darwinOverlays =
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
              crossSystem = "x86_64-darwin";
              config.allowUnsupportedSystem = true;
              overlays = darwinOverlays;
            };
            aarch64 = import nixpkgs {
              localSystem = system;
              crossSystem = "aarch64-darwin";
              config.allowUnsupportedSystem = true;
              overlays = darwinOverlays;
            };
          };
          wasmPkgs = import nixpkgs {
            inherit overlays;
            localSystem = system;
            crossSystem = {config = "wasm32-unknown-wasi";};
          };
          rustToolchain = pkgs.rust-bin.nightly.latest.default.override {
            targets = [
              "x86_64-unknown-linux-gnu"
              "aarch64-unknown-linux-gnu"
              "x86_64-pc-windows-gnu"
              "x86_64-apple-darwin"
              "aarch64-apple-darwin"
              "wasm32-unknown-unknown"
            ];
          };
          zigTargetMap = {
            "x86_64-unknown-linux-gnu" = "x86_64-linux-gnu";
            "aarch64-unknown-linux-gnu" = "aarch64-linux-gnu";
            "x86_64-apple-darwin" = "x86_64-macos-none";
            "aarch64-apple-darwin" = "aarch64-macos-none";
            "x86_64-w64-windows-gnu" = "x86_64-windows-gnu";
            "wasm32-unknown-wasi" = "wasm32-freestanding";
          };
          rustcTargetMap = {
            "x86_64-unknown-linux-gnu" = "x86_64-unknown-linux-gnu";
            "aarch64-unknown-linux-gnu" = "aarch64-unknown-linux-gnu";
            "x86_64-apple-darwin" = "x86_64-apple-darwin";
            "aarch64-apple-darwin" = "aarch64-apple-darwin";
            "x86_64-w64-windows-gnu" = "x86_64-pc-windows-gnu";
            "wasm32-unknown-wasi" = "wasm32-unknown-unknown";
          };
        in
          flattenTree rec {
            app = recurseIntoAttrs {
              linux = recurseIntoAttrs {
                x86_64 = linuxPkgs.x86_64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs zigTargetMap;
                  glfw = glfw.linux.x86_64;
                  wgpu-native = wgpu-native.linux.x86_64;
                } {};
                aarch64 = linuxPkgs.aarch64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs zigTargetMap;
                  glfw = glfw.linux.aarch64;
                  wgpu-native = wgpu-native.linux.aarch64;
                } {};
              };
              nixos = recurseIntoAttrs {
                x86_64 =
                  linuxPkgs.x86_64.callPackage ./nix/app {
                    inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs zigTargetMap;
                    glfw = glfw.linux.x86_64;
                    wgpu-native = wgpu-native.linux.x86_64;
                  } {
                    nixos = true;
                  };
                aarch64 =
                  linuxPkgs.aarch64.callPackage ./nix/app {
                    inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs zigTargetMap;
                    glfw = glfw.linux.aarch64;
                    wgpu-native = wgpu-native.linux.aarch64;
                  } {
                    nixos = true;
                  };
              };
              windows = recurseIntoAttrs {
                x86_64 = windowsPkgs.x86_64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy windows-nelua inputs zigTargetMap;
                  glfw = glfw.windows.x86_64;
                  wgpu-native = wgpu-native.windows.x86_64;
                } {};
              };
              darwin = recurseIntoAttrs {
                x86_64 = darwinPkgs.x86_64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs zigTargetMap;
                  glfw = glfw.darwin.x86_64;
                  wgpu-native = wgpu-native.darwin.x86_64;
                } {};
                aarch64 = darwinPkgs.aarch64.callPackage ./nix/app {
                  inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs zigTargetMap;
                  glfw = glfw.darwin.aarch64;
                  wgpu-native = wgpu-native.darwin.aarch64;
                } {};
              };
              wasm = wasmPkgs.callPackage ./nix/app {
                inherit nelua glfw-nelua glfwnative-nelua wgpu-nelua entropy inputs zigTargetMap;
                wgpu-native = wgpu-native.wasm;
                zig = pkgs.zigpkgs.master;
              } {};
            };

            # ===== REQUIRED LIBS/BUILD STUFF BELOW =====
            glfw = recurseIntoAttrs {
              linux = recurseIntoAttrs {
                x86_64 = linuxPkgs.x86_64.callPackage ./nix/glfw {
                  inherit inputs zigTargetMap;
                };
                aarch64 = linuxPkgs.aarch64.callPackage ./nix/glfw {
                  inherit inputs zigTargetMap;
                };
              };
              windows = recurseIntoAttrs {
                x86_64 = windowsPkgs.x86_64.callPackage ./nix/glfw {
                  inherit inputs zigTargetMap;
                };
              };
              darwin = recurseIntoAttrs {
                x86_64 = darwinPkgs.x86_64.callPackage ./nix/glfw {
                  inherit inputs zigTargetMap;
                };
                aarch64 = darwinPkgs.aarch64.callPackage ./nix/glfw {
                  inherit inputs zigTargetMap;
                };
              };
            };

            wgpu-native = recurseIntoAttrs {
              linux = recurseIntoAttrs {
                x86_64 = let
                  craneLib = (crane.mkLib linuxPkgs.x86_64).overrideToolchain rustToolchain;
                in
                  linuxPkgs.x86_64.callPackage ./nix/wgpu-native {
                    inherit craneLib inputs zigTargetMap rustcTargetMap;
                  };
                aarch64 = let
                  craneLib = (crane.mkLib linuxPkgs.aarch64).overrideToolchain rustToolchain;
                in
                  linuxPkgs.aarch64.callPackage ./nix/wgpu-native {
                    inherit craneLib inputs zigTargetMap rustcTargetMap;
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
                    inherit craneLib inputs rustPlatform zigTargetMap rustcTargetMap;
                  };
              };
              darwin = recurseIntoAttrs {
                x86_64 = let
                  craneLib = (crane.mkLib pkgs).overrideToolchain rustToolchain;
                in
                  darwinPkgs.x86_64.callPackage ./nix/wgpu-native {
                    inherit craneLib inputs zigTargetMap rustcTargetMap;
                  };
                aarch64 = let
                  craneLib = (crane.mkLib pkgs).overrideToolchain rustToolchain;
                in
                  darwinPkgs.aarch64.callPackage ./nix/wgpu-native {
                    inherit craneLib inputs zigTargetMap rustcTargetMap;
                  };
              };
              wasm = let
                craneLib = (crane.mkLib pkgs).overrideToolchain rustToolchain;
              in
                wasmPkgs.callPackage ./nix/wgpu-native {
                  inherit craneLib inputs zigTargetMap rustcTargetMap;
                  zig = pkgs.zigpkgs.master;
                };
            };

            # this is broken because they don't include Cargo.lock
            # needs a patch
            # naga = recurseIntoAttrs {
            #   linux = recurseIntoAttrs {
            #     x86_64 = let
            #       craneLib = (crane.mkLib linuxPkgs.x86_64).overrideToolchain rustToolchain;
            #     in
            #       linuxPkgs.x86_64.callPackage ./nix/naga {
            #         inherit craneLib inputs rustcTargetMap;
            #       };
            #   };
            # };

            # ===== NELUA =====
            nelua = pkgs.callPackage ./nix/nelua {inherit inputs;};

            nelua-decl = pkgs.callPackage ./nix/nelua-decl {inherit inputs;};

            # ===== NELUA BINDINGS =====
            glfw-nelua = pkgs.callPackage ./nix/nelua-bindings/glfw-nelua {
              inherit inputs nelua-decl;
            };

            glfwnative-nelua = pkgs.callPackage ./nix/nelua-bindings/glfwnative-nelua {};

            wgpu-nelua = pkgs.callPackage ./nix/nelua-bindings/wgpu-nelua {
              inherit inputs nelua-decl;
            };

            windows-nelua = pkgs.callPackage ./nix/nelua-bindings/windows-nelua {
              inherit nelua-decl;
            };

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
