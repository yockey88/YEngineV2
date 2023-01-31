#version 460 core
in vec3 OColor;
out vec4 outColor;
void main() {
    outColor = vec4(OColor.x , OColor.y , OColor.z , 1.0);
}