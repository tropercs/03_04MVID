#include "engine/texture.hpp"
#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>
#include "engine/shader.hpp"

Texture::Texture(const char* path, Format format, const std::string& name) : _name(name) , _format(format){
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path, &_width, &_height, &_depth, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cout << "Error loading texture " << path << std::endl;
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
}

void Texture::activate(const Shader& shader, uint32_t unit, const char* name) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, _id);
    if (name) {
        shader.set(name, static_cast<int32_t>(unit));
    } else {
        shader.set(_name.c_str(), static_cast<int32_t>(unit));
    }
}
