{stdenvNoCC}:
stdenvNoCC.mkDerivation {
  name = "glfwnative-nelua";

  src = ./.;

  installPhase = ''
    mkdir -p $out/nelua
    install -Dm644 glfwnative.nelua $out/nelua/glfwnative.nelua
  '';
}
