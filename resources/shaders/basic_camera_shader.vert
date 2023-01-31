#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 proj = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);

out vec3 OColor;
void main() {
    OColor = color;
    gl_Position = proj * view * model * vec4(position , 1.0);
}