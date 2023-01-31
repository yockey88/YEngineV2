#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in float size;

uniform mat4 proj = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);

out float OSize;
out vec3 OPos;
out vec3 OColor;
void main() {
    OSize = size;
    OPos = position;
    OColor = color;
    gl_Position = proj * view * model * vec4(position , 1.0);
}