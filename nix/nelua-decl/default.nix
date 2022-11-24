{
  stdenv,
  inputs,
  fetchFromGitHub,
  pkg-config,
  gcc,
  gmp,
  lua,
}:
stdenv.mkDerivation {
  pname = "nelua-decl";
  version = inputs.nelua-decl.shortRev;
  src = inputs.nelua-decl;

  nativeBuildInputs = [
    pkg-config
    gcc
  ];

  buildInputs = [
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
}
