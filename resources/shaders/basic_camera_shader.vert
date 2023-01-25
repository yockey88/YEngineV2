#version 410 core
layout (location = 0) in vec3 position;

uniform mat4 proj = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);
void main() {
    gl_Position = proj * view * model * vec4(position , 1.0);
}