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
#include <space_invaders/shader/TexturedShaderSet.hpp>
#include <space_invaders/shader/CubeMapShaderSet.hpp>
#include <space_invaders/texture/CubeMapTexture.hpp>
#include <space_invaders/model/TexturedModel.hpp>
#include <space_invaders/model/predefined/Teapot.hpp>
#include <space_invaders/model/predefined/Cube.hpp>
#include <space_invaders/model/predefined/Wall.hpp>
#include <space_invaders/model/HierarchicalModel.hpp>
#include <space_invaders/game/Squadron.hpp>
#include <space_invaders/game/Spaceship.hpp>


using space_invaders::window::Window;
using space_invaders::shader::LambertTexturedShaderSet;
using space_invaders::shader::TexturedShaderSet;
using space_invaders::shader::CubeMapShaderSet;
using space_invaders::model::HierarchicalModel;
using space_invaders::model::predefined::Cube;
using space_invaders::model::predefined::Teapot;
using space_invaders::model::predefined::Wall;
using space_invaders::model::TexturedModel;
using space_invaders::texture::CubeMapTexture;
using space_invaders::game::Squadron;
using space_invaders::game::Spaceship;

const float INITIAL_FIELD_OF_VIEW = 50.0f;
const float NEAR_CLIPPING_PANE = 0.02f;
const float FAR_CLIPPING_PANE = 20.0f;

const int NUMBER_OF_ROWS = 6;
const int INVADERS_PER_ROW = 10;
const int MARGIN = 2;
const bool UFO = true;
const float DISTANCE_FROM_CENTER = -7.0f;
const float GAME_HEIGHT = -2.0f;
const float SHIP_SIZE_MULTIPLIER = 0.5f;
const float SHIP_GAP_MULTIPLIER = 1.0f;
const float TRANSLATE_VALUE = SHIP_SIZE_MULTIPLIER * SHIP_GAP_MULTIPLIER;
const float INITIAL_SQUADRON_HEIGHT = 10.0f;
const float INVADERS_SPEED = 0.3f;
const float SPACESHIP_SPEED = 6.0f;

int main() {
    Squadron squadron(NUMBER_OF_ROWS, INVADERS_PER_ROW, UFO, MARGIN, INITIAL_SQUADRON_HEIGHT, INVADERS_SPEED);
    Spaceship spaceship(INVADERS_PER_ROW + 2 * MARGIN, SPACESHIP_SPEED);

    unsigned screenWidth = 600;
    unsigned screenHeight = 600;
    Window window("Space Invaders", &screenHeight, &screenWidth, false, true);
    const float screenRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);


    Cube cube;
    TexturedShaderSet lambertShaders;
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

    TexturedModel invader1("../models/invader_01.obj", "../textures/alien_1.png");
    TexturedModel invader2("../models/invader_02.obj", "../textures/alien_2.png");
    TexturedModel invader3("../models/invader_03.obj", "../textures/alien_3.png");
    TexturedModel ufo("../models/ufo.obj", "../textures/spaceship.png");
    TexturedModel mainShip("../models/main_ship.obj", "../textures/spaceship.png");

    float fieldOfView = INITIAL_FIELD_OF_VIEW;
    auto viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -7.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    auto perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), screenRatio, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);

    glm::mat4 gameModelMatrix = glm::mat4(1.0f);
    gameModelMatrix = glm::translate(gameModelMatrix, glm::vec3(
        -0.5f * (INVADERS_PER_ROW - 1 + 2 * MARGIN) * SHIP_SIZE_MULTIPLIER * SHIP_GAP_MULTIPLIER,
        GAME_HEIGHT,
        DISTANCE_FROM_CENTER
    ));
    gameModelMatrix = glm::rotate(gameModelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    gameModelMatrix = glm::scale(gameModelMatrix, glm::vec3(SHIP_SIZE_MULTIPLIER));

    auto viewRotationVector = glm::vec3(0.0f, 0.0f, 0.0f);
    bool viewShouldRotate = false;
    float time;

    window
        .onInit([]() {
            glClearColor(0.1f, 0.1f, 0.1f, 1.f);
            glEnable(GL_DEPTH_TEST);
        })
        .onLoop([&]() {
            time = static_cast<float>(glfwGetTime());
            glfwSetTime(0.0f);
            glDepthMask(GL_FALSE);
            cubeMapShaders.use();
            glUniformMatrix4fv(cubeMapShaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(cubeMapShaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            cube.draw(cubeMapShaders);
            glDepthMask(GL_TRUE);

            lambertShaders.use();

            glUniformMatrix4fv(lambertShaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(lambertShaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            do {
                glUniformMatrix4fv(lambertShaders.uniform("M"), 1, false, glm::value_ptr(
                    glm::translate(
                        glm::mat4(1.0f),
                        glm::vec3(TRANSLATE_VALUE * squadron.getX(), TRANSLATE_VALUE * squadron.getY(), 0.0f)
                    ) * gameModelMatrix
                ));

                switch (squadron.getType()) {
                    case 0:
                        invader1.draw(lambertShaders);
                        break;
                    case 1:
                        invader2.draw(lambertShaders);
                        break;
                    case 2:
                        invader3.draw(lambertShaders);
                        break;
                    case 3:
                        ufo.draw(lambertShaders);
                        break;
                }
            } while(squadron.nextInvader());

            glUniformMatrix4fv(lambertShaders.uniform("M"), 1, false, glm::value_ptr(
                glm::translate(
                    glm::mat4(1.0f),
                    glm::vec3(TRANSLATE_VALUE * spaceship.getX(), TRANSLATE_VALUE * -1.0f, 0.0f)
                ) * gameModelMatrix
            ));
            mainShip.draw(lambertShaders);

            if (viewShouldRotate) {
                viewMatrix = glm::rotate(viewMatrix, glm::radians(0.5f), viewRotationVector);
            }
            squadron.moveShips(time);
            spaceship.move(time);

            squadron.resetInvader();
        })
        .onKey(GLFW_KEY_LEFT, GLFW_PRESS, [&]() {
            spaceship.setDirection(-1);
        })
        .onKey(GLFW_KEY_RIGHT, GLFW_PRESS, [&]() {
            spaceship.setDirection(1);
        })
        .onKey(GLFW_KEY_RIGHT, GLFW_RELEASE, [&]() {
            spaceship.modifyDirection(-1);
        })
        .onKey(GLFW_KEY_LEFT, GLFW_RELEASE, [&]() {
            spaceship.modifyDirection(1);
        })
        .onKey(GLFW_KEY_UP, GLFW_REPEAT, [&]() {
            viewMatrix = glm::rotate(viewMatrix, glm::radians(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        })
        .onKey(GLFW_KEY_DOWN, GLFW_REPEAT, [&]() {
            viewMatrix = glm::rotate(viewMatrix, glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        })
        .onKey(GLFW_KEY_Z, GLFW_REPEAT, [&]() {
            fieldOfView += 1.0f;
            perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), screenRatio, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
        })
        .onKey(GLFW_KEY_X, GLFW_REPEAT, [&]() {
            fieldOfView -= 1.0f;
            perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), screenRatio, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
        })
        .onMouseMove([&](double y, double x) {
            viewShouldRotate = true;

            if (x < screenWidth / 4) {
                viewRotationVector = glm::vec3(0.0f, -1.0f, 0.0f);
            } else if (x > 3 * screenWidth / 4) {
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
                perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), screenRatio, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
            } else if (y > 0) {
                fieldOfView -= 1.0f;
                perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), screenRatio, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
            }
        })
        ;

    return window.run();
}
