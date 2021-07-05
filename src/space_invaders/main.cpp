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
#include <space_invaders/shader/PhongShaderSet.hpp>
#include <space_invaders/shader/TexturedShaderSet.hpp>
#include <space_invaders/shader/CubeMapShaderSet.hpp>
#include <space_invaders/texture/CubeMapTexture.hpp>
#include <space_invaders/model/TexturedModel.hpp>
#include <space_invaders/model/predefined/Teapot.hpp>
#include <space_invaders/model/predefined/Cube.hpp>
#include <space_invaders/model/predefined/Wall.hpp>
#include <space_invaders/model/HierarchicalModel.hpp>

using space_invaders::window::Window;
using space_invaders::shader::LambertTexturedShaderSet;
using space_invaders::shader::TexturedShaderSet;
using space_invaders::shader::PhongShaderSet;
using space_invaders::shader::CubeMapShaderSet;
using space_invaders::model::HierarchicalModel;
using space_invaders::model::predefined::Cube;
using space_invaders::model::predefined::Teapot;
using space_invaders::model::predefined::Wall;
using space_invaders::model::TexturedModel;
using space_invaders::texture::CubeMapTexture;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const float INITIAL_FIELD_OF_VIEW = 50.0f;
const float SCREEN_RATIO = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);
const float NEAR_CLIPPING_PANE = 0.02f;
const float FAR_CLIPPING_PANE = 20.0f;

int main() {
    Window window("Space Invaders", SCREEN_WIDTH, SCREEN_HEIGHT, true);

    Cube cube;
    LambertTexturedShaderSet lambertShaders;
    PhongShaderSet phongShaders;
    CubeMapShaderSet cubeMapShaders;
    CubeMapTexture cubeMapTexture({
        "../textures/skybox/right.png",
        "../textures/skybox/left.png",
        "../textures/skybox/top.png",
        "../textures/skybox/bottom.png",
        "../textures/skybox/front.png",
        "../textures/skybox/back.png"
    }); 

    if (!cubeMapTexture) {
        std::cerr << "Texture loading error\n";
        return 1;
    }



    float fieldOfView = INITIAL_FIELD_OF_VIEW;
    auto viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    auto perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), SCREEN_RATIO, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
    auto modelMatrix = glm::rotate(glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2, 0.2f)), glm::vec3(0.0f, 0.0f, 2.0f)), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    auto viewRotationVector = glm::vec3(0.0f, 0.0f, 0.0f);
    bool viewShouldRotate = false;
    
    // I don't check whether textured model was read correctly intentionally
    TexturedModel mainShip("../models/main_ship.obj", "../textures/spaceship.png");
    TexturedModel ufo("../models/ufo.obj", "../textures/spaceship.png");
    TexturedModel invader1("../models/invader_01.obj", "../textures/alien_1.png");
    TexturedModel invader2("../models/invader_02.obj", "../textures/alien_2.png");
    TexturedModel invader3("../models/invader_03.obj", "../textures/alien_3.png");
    TexturedModel teapot(Teapot(), "../textures/spaceship.png");

    window
        .onInit([]() {
            glClearColor(0.1f, 0.1f, 0.1f, 1.f);
            glEnable(GL_DEPTH_TEST);
        })
        .onLoop([&]() {
            glDepthMask(GL_FALSE);
            cubeMapShaders.use();
            glUniformMatrix4fv(cubeMapShaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(cubeMapShaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            cube.draw(cubeMapShaders);
            glDepthMask(GL_TRUE);

            phongShaders.use();
            glUniformMatrix4fv(phongShaders.uniform("M"), 1, false, glm::value_ptr(modelMatrix));
            glUniformMatrix4fv(phongShaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(phongShaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            mainShip.draw(phongShaders);

            modelMatrix = glm::rotate(modelMatrix, glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

            if (viewShouldRotate) {
                viewMatrix = glm::rotate(viewMatrix, glm::radians(0.5f), viewRotationVector);
            }
        })
        .onKey(GLFW_KEY_LEFT, GLFW_REPEAT, [&]() {
            viewMatrix = glm::rotate(viewMatrix, glm::radians(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        })
        .onKey(GLFW_KEY_RIGHT, GLFW_REPEAT, [&]() {
            viewMatrix = glm::rotate(viewMatrix, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        })
        .onKey(GLFW_KEY_UP, GLFW_REPEAT, [&]() {
            viewMatrix = glm::rotate(viewMatrix, glm::radians(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        })
        .onKey(GLFW_KEY_DOWN, GLFW_REPEAT, [&]() {
            viewMatrix = glm::rotate(viewMatrix, glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        })
        .onKey(GLFW_KEY_Z, GLFW_REPEAT, [&]() {
            fieldOfView += 1.0f;
            perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), SCREEN_RATIO, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
        })
        .onKey(GLFW_KEY_X, GLFW_REPEAT, [&]() {
            fieldOfView -= 1.0f;
            perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), SCREEN_RATIO, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
        })
        .onMouseMove([&](double y, double x) {
            viewShouldRotate = true;

            if (x < SCREEN_WIDTH / 4) {
                viewRotationVector = glm::vec3(0.0f, -1.0f, 0.0f);
            } else if (x > 3 * SCREEN_WIDTH / 4) {
                viewRotationVector = glm::vec3(0.0f, 1.0f, 0.0f);
            } else {
                viewRotationVector = glm::vec3(0.0f, 0.0f, 0.0f);
                viewShouldRotate = false;
            }
        })
        .onMouseLeave([]() {
            std::cout << "Mouse has left window area\n";
        })
        .onMouseEnter([]() {
            std::cout << "Mouse has came back to window area\n";
        })
        .onMouseButton(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, []() {
            std::cout << "Left mouse button clicked\n";
        })
        .onMouseButton(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, []() {
            std::cout << "Right mouse button clicked\n";
        })
        .onScroll([&](double y, double x) {
            if (y < 0) {
                fieldOfView += 1.0f;
                perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), SCREEN_RATIO, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
            } else if (y > 0) {
                fieldOfView -= 1.0f;
                perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), SCREEN_RATIO, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
            }
        })
        ;

    return window.run();
}
