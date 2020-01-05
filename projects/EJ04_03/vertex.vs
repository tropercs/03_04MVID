#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aUV;

out vec2 UV;

void main() {
    UV = aUV;
    gl_Position = vec4(aPos, 1.0);
}