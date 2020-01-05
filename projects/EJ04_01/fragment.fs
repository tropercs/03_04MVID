#version 330 core

in vec2 UV;
in vec3 Color;
out vec4 FragColor;

uniform sampler2D tex_1;
uniform sampler2D tex_2;

void main() {
    FragColor = mix(texture(tex_1, UV),vec4(Color, 1.0), 0.7);
}