#define GLM_FORCE_RADIANS

#include <iostream>
#include <memory>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <space_invaders/window/Window.hpp>
#include <space_invaders/shader/ConstantShaderSet.hpp>
#include <space_invaders/shader/LambertTexturedShaderSet.hpp>
#include <space_invaders/model/TexturedModel.hpp>
#include <space_invaders/model/Teapot.hpp>
#include <space_invaders/model/Cube.hpp>
#include <space_invaders/model/HierarchicalModel.hpp>

using space_invaders::window::Window;
using space_invaders::shader::LambertTexturedShaderSet;
using space_invaders::model::HierarchicalModel;
using space_invaders::model::Cube;
using space_invaders::model::Teapot;
using space_invaders::model::TexturedModel;

int main() {
    Window window("Space Invaders", 400, 400, true);
    LambertTexturedShaderSet shaders;
    // TexturedModel minicooper("../models/minicooper.obj", "../textures/bricks.png");
    TexturedModel minicooper(Teapot(), "../textures/bricks.png");

    if (!minicooper) {
        std::cerr << "Could not read obj file\n";
        return 1;
    }
    
    auto viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 2.0f, -5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    auto perspectiveMatrix = glm::perspective(50.0f * 3.14159f / 180.0f, 1.0f, 1.0f, 10.f);

    int counter = 0;

    window
        .onInit([]() {
            glClearColor(1.f, 0.5f, 0.2f, 1.f);
            glEnable(GL_DEPTH_TEST);
        })
        .onLoop([&]() {
            HierarchicalModel(glm::rotate(glm::rotate(glm::mat4(1.0f), -3.14159f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f)), 3 * counter / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f)), [&](const HierarchicalModel& model) {
                shaders.use();
                glUniform4f(shaders.uniform("color"), 0, 1, 0, 1);
                glUniformMatrix4fv(shaders.uniform("M"), 1, false, glm::value_ptr(model.calculateEffectiveModelMatrix()));
                glUniformMatrix4fv(shaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
                glUniformMatrix4fv(shaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
                glUniform4f(shaders.uniform("color"), 0.0f, 1.0f, 0.0f, 1.0f);
                minicooper.draw(shaders);
            }).draw(shaders);

            counter++;
        });

    return window.run();
}
