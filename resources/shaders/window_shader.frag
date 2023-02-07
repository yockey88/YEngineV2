#version 460 core
out vec4 oCol;
in vec4 uvs;

uniform sampler2D tex;
void main() {
    oCol = texture(tex , uvs);
}