#version 460 core
in vec3 OColor;
 
out vec4 outColor;
void main() {
    outColor = vec4(OColor , 1.0);
}