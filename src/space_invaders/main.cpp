#define GLM_FORCE_RADIANS

#include <space_invaders/Window.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <iostream>

using space_invaders::Window;
using space_invaders::shader::Shader;
using space_invaders::shader::ShaderSet;

int main() {
    Window window("Space Invaders", 400, 400, false);

    window
        .onInit([]() {
            ShaderSet shaders;
            shaders
                .attach(Shader(GL_VERTEX_SHADER, "../src/space_invaders/shader/v_lambert.glsl"))
                .attach(Shader(GL_FRAGMENT_SHADER, "../src/space_invaders/shader/f_lambert.glsl"))
                .link();

            glClearColor(1.f, 0.5f, 0.2f, 1.f);
            glEnable(GL_DEPTH_TEST);

            std::cout << "Początek\n";
        })
        .onLoop([]() {
            std::cout << "Pęęętla\n";
        })
        .onExit([]() {
            std::cout << "Koniec\n";
        });

    return window.run();
}
