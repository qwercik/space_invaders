#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <space_invaders/shader/ShaderSet.hpp>
#include <iostream>

using space_invaders::shader::Shader;
using space_invaders::shader::ShaderSet;

int main() {
    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW\n";
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwSetErrorCallback([](int error, const char *desc) {
        std::cerr << "[Error " << error << "]: " << desc << '\n';
    });

    GLFWwindow *window = glfwCreateWindow(400, 400, "Game", NULL, NULL);
    if (!window) {
        std::cerr << "Could not initialize window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK) {
        std::cerr << "Could not initialize GLEW\n";
        return EXIT_FAILURE;
    }

    if (!GLEW_VERSION_3_3) {
        std::cerr << "OpenGL 3.3 is required\n";
        return EXIT_FAILURE;
    }
    
    glClearColor(1.f, 0.5f, 0.2f, 1.f);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();





    ShaderSet shaders;
    shaders
        .attach(Shader(GL_VERTEX_SHADER, "../src/space_invaders/shader/v_lambert.glsl"))
        .attach(Shader(GL_FRAGMENT_SHADER, "../src/space_invaders/shader/f_lambert.glsl"))
        .link();
}
