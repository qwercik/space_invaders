#define GLM_FORCE_RADIANS

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <space_invaders/Window.hpp>
#include <space_invaders/shader/LambertShaderSet.hpp>
#include <space_invaders/model/Teapot.hpp>

using space_invaders::Window;
using space_invaders::shader::LambertShaderSet;
using space_invaders::model::Teapot;

int main() {
    Window window("Space Invaders", 400, 400, false);
    LambertShaderSet shaders;
    Teapot teapot;

    int counter = 0;

    window
        .onInit([&]() {
            glClearColor(1.f, 0.5f, 0.2f, 1.f);
            glEnable(GL_DEPTH_TEST);
        })
        .onLoop([&]() {
            auto mMatrix = glm::rotate(glm::mat4(1.0f), counter * 2.0f * 3.14159f / 180.0f, glm::vec3(0.0f, 1.0f, 1.0f));
            auto vMatrix = glm::lookAt(
                glm::vec3(0.0f, 0.0f, -5.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
            );
            auto pMatrix = glm::perspective(50.0f * 3.14159f / 180.0f, 1.0f, 1.0f, 50.0f);

            shaders.use();
            glUniformMatrix4fv(shaders.uniform("P"), 1, false, glm::value_ptr(pMatrix)); 
            glUniformMatrix4fv(shaders.uniform("V"), 1, false, glm::value_ptr(vMatrix)); 
            glUniformMatrix4fv(shaders.uniform("M"), 1, false, glm::value_ptr(mMatrix));

            teapot.draw();

            counter++;
        });

    return window.run();
}
