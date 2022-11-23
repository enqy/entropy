{
  lib,
  craneLib,
  stdenv,
  inputs,
}:
craneLib.buildPackage {
  pname = "naga";
  version = inputs.naga.shortRev;
  src = inputs.naga;

  cargoLock = ./Cargo.lock;
  cargoExtraArgs = "--all-features";

  CARGO_BUILD_TARGET = let
    rustcTargetMap = {
      "x86_64-unknown-linux-gnu" = "x86_64-unknown-linux-gnu";
      "aarch64-unknown-linux-gnu" = "aarch64-unknown-linux-gnu";
      "x86_64-apple-darwin" = "x86_64-apple-darwin";
      "aarch64-apple-darwin" = "aarch64-apple-darwin";
      "x86_64-w64-mingw32" = "x86_64-pc-windows-gnu";
    };
  in
    rustcTargetMap."${stdenv.hostPlatform.config}";

  doCheck = false;
}
