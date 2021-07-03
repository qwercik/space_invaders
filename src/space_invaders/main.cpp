#define GLM_FORCE_RADIANS

#include <space_invaders/Window.hpp>
#include <space_invaders/shader/LambertShaderSet.hpp>
#include <iostream>

using space_invaders::Window;
using space_invaders::shader::LambertShaderSet;

int main() {
    Window window("Space Invaders", 400, 400, false);

    window
        .onInit([]() {
            LambertShaderSet shaders;

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
