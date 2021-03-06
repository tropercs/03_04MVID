#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdint>

void onChangeFrameBufferSize(GLFWwindow*, const int32_t width, const int32_t height) noexcept {
    glViewport(0, 0, width, height);
    std::cout << width << " " << height << std::endl;
}

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
}


int main(int, char*[]) {
    if (!glfwInit()) {
        std::cout << "Error Initializing GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "04MVID", nullptr, nullptr);
    if (!window) {
        std::cout << "Error Creating Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Error Initializing GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, onChangeFrameBufferSize);

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    while(!glfwWindowShouldClose(window)) {
        handleInput(window);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}