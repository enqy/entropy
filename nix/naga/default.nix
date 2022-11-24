{
  lib,
  craneLib,
  stdenv,
  rustcTargetMap,
  inputs,
}:
craneLib.buildPackage {
  pname = "naga";
  version = inputs.naga.shortRev;
  src = inputs.naga;

  cargoLock = ./Cargo.lock;
  cargoExtraArgs = "--all-features";

  CARGO_BUILD_TARGET = rustcTargetMap."${stdenv.hostPlatform.config}";

  doCheck = false;
}
