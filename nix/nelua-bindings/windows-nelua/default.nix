{
  stdenvNoCC,
  nelua-decl,
}:
stdenvNoCC.mkDerivation {
  name = "windows-nelua";

  src = ./.;

  installPhase = ''
    mkdir -p $out/nelua
    install -Dm644 ${nelua-decl}/nelua/windows.nelua $out/nelua/windows.nelua
  '';
}
