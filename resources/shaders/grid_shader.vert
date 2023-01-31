#version 460
layout (location = 0) in vec3 position;

uniform mat4 proj = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);

out vec4 OColor;
void main() {
    // float r = x - y * floor(x / y);
    // if (r == 0) {
    //     OColor = vec4(0.f , 0.f , 0.f , 1.f);
    // } else {
    //     OColor = vec4(1.f , 1.f , 1.f , 0.5f); 
    // }
    OColor = vec4(1.f);
    gl_Position = proj * view * model * vec4(position , 1.0);
}