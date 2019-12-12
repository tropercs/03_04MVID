#include "engine/quad.hpp"

Quad::Quad(float size): _size(size) {
    _nVerts = 6;

    float positions[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    float uvs[] = {
         1.0f, 1.0f,
         1.0f, 0.0f,
         0.0f, 0.0f,
         0.0f, 1.0f
    };

    float normals[]{
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };

    uint32_t indices[] = {
        0, 3, 1,
        1, 3, 2
    };

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(4, _VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Quad::render() const {
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _nVerts, GL_UNSIGNED_INT, nullptr);
}
