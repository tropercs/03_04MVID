#version 330 core

in vec3 myColor;
in vec3 myPos;
out vec4 FragColor;

void main() {
    FragColor = vec4(myPos, 1.0f);
}