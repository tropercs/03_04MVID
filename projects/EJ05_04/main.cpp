#include <glad/glad.h>

#include "engine/window.hpp"
#include "engine/shader.hpp"

#include "engine/texture.hpp"
#include "engine/geometry/cube.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <engine\geometry\quad.hpp>

void handleInput() {/*Intentionally Left BLank*/ }

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, -20.0f),
    glm::vec3(-2.0f, 0.0f, -2.0f),
    glm::vec3(-4.0f, 0.0f, -10.0f),
    glm::vec3(3.0f, 0.0f, -4.0f),
    glm::vec3(-2.0f, 0.0f, -8.0f),
    glm::vec3(2.0f, 0.0f, -3.0f),
    glm::vec3(1.0f, 0.0f, -2.0f),
    glm::vec3(1.0f, 0.0f, -2.0f),
    glm::vec3(-1.0f, 0.0f, -1.0f)
};

float cubeSizes[] = { 1.38f, 0.4f, 1.78f, 0.72f, 1.4f, 0.31f, 0.85f, 0.11f, 0.27f, 1.1f };

void render(const Geometry& geom, const Geometry& suelo, const Shader& shader, Texture& tex) {
    glClear(GL_COLOR_BUFFER_BIT);

    

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model);
    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4

    suelo.render();

    for (int i = 0; i < 10; i++) {

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        
        model = glm::scale(model, glm::vec3(cubeSizes[i]));

        shader.use();

        tex.use(shader, "tex", 0);

        shader.set("model", model);
        shader.set("view", view);
        shader.set("proj", proj);  //TODO const mat4

        geom.render();
    }

    
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader shader("../projects/AG05/vertex.vs", "../projects/AG05/fragment.fs");
    const Cube cube(1.0f);
    const Quad suelo(1.0f);

    Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glDepthFunc(GL_LESS);
    //glEnable(GL_DEPTH_TEST);
    

    while (window->alive()) {
        handleInput();
        
        render(cube, suelo, shader, tex);
        
        
        window->frame();
    }

    return 0;
}