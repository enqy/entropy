{
  stdenvNoCC,
  inputs,
  nelua-decl,
}:
stdenvNoCC.mkDerivation {
  name = "glfw-nelua";

  src = ./.;

  buildPhase = ''
    cp ${nelua-decl}/nelua/glfw.nelua glfw.nelua
    sed -i -e 's/linklib .GL.//' glfw.nelua
    sed -i -e 's/linklib .opengl32.//' glfw.nelua
    sed -i -e '1s;^;## cdefine "GLFW_INCLUDE_NONE"\n;' glfw.nelua
    sed -i -e 's/linklib .glfw.$/linklib "glfw3"/' glfw.nelua
  '';

  installPhase = ''
    mkdir -p $out/nelua $out/include/GLFW
    install -Dm644 glfw.nelua $out/nelua/glfw.nelua
    install -Dm644 ${inputs.glfw}/include/GLFW/glfw3.h $out/include/GLFW/glfw3.h
    install -Dm644 ${inputs.glfw}/include/GLFW/glfw3native.h $out/include/GLFW/glfw3native.h
  '';
}
