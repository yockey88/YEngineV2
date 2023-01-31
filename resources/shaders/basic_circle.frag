#version 460 core
in float OSize;
in vec3 OPos;
in vec3 OColor;
 

out vec4 outColor;
void main() {
    if (length(OPos) > OSize) discard;
    outColor = vec4(OColor , 1.0);
}