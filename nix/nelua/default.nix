{
  lib,
  stdenv,
  inputs,
}:
stdenv.mkDerivation {
  pname = "nelua";
  version = inputs.nelua.shortRev;
  src = inputs.nelua;

  postPatch = ''
    # patch out hardcoded CC
    sed -i -e 's/CC=.*//' Makefile
  '';

  makeFlags = ["PREFIX=$(out)"];
}
