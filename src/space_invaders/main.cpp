#define GLM_FORCE_RADIANS

#include <iostream>
#include <memory>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <space_invaders/window/Window.hpp>
#include <space_invaders/shader/ConstantShaderSet.hpp>
#include <space_invaders/shader/LambertShaderSet.hpp>
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
#include <space_invaders/game/Squadron.hpp>
#include <space_invaders/game/Spaceship.hpp>
#include <space_invaders/game/BulletTracker.hpp>
#include <space_invaders/game/PiggyBank.hpp>


using space_invaders::window::Window;
using space_invaders::shader::ConstantShaderSet;
using space_invaders::shader::LambertShaderSet;
using space_invaders::shader::LambertTexturedShaderSet;
using space_invaders::shader::TexturedShaderSet;
using space_invaders::shader::PhongShaderSet;
using space_invaders::shader::CubeMapShaderSet;
using space_invaders::model::HierarchicalModel;
using space_invaders::model::predefined::Cube;
using space_invaders::model::predefined::Teapot;
using space_invaders::model::predefined::Wall;
using space_invaders::model::BasicModel;
using space_invaders::model::TexturedModel;
using space_invaders::texture::CubeMapTexture;
using space_invaders::game::Squadron;
using space_invaders::game::Spaceship;
using space_invaders::game::Bullet;
using space_invaders::game::BulletTracker;
using space_invaders::game::PiggyBank;

const float INITIAL_FIELD_OF_VIEW = 55.0f;
const float NEAR_CLIPPING_PANE = 0.02f;
const float FAR_CLIPPING_PANE = 100.0f;

const int NUMBER_OF_ROWS = 6;
const int INVADERS_PER_ROW = 10;
const int MARGIN = 2;
const bool UFO = true;
const float DISTANCE_FROM_CENTER = 2.0f;
const float GAME_HEIGHT = -0.5f;
const float SHIP_SIZE_MULTIPLIER = 0.5f;
const float SHIP_GAP_MULTIPLIER = 1.0f;
const float TRANSLATE_VALUE = SHIP_SIZE_MULTIPLIER * SHIP_GAP_MULTIPLIER;
const float INITIAL_SQUADRON_HEIGHT = 10.0f;
const float INVADERS_SPEED = 0.3f;
const int SPACESHIP_HEALTH = 3; // -1 to activate god mode
const float SPACESHIP_SPEED = 6.0f;
const float SHOT_SPEED = 6.0f;
const float SPACESHIP_SHOT_COOLDOWN = 1.0f;
const float SQUADRON_SHOT_COOLDOWN = 1.0f;

int main() {
    Squadron squadronTemplate(
        NUMBER_OF_ROWS,
        INVADERS_PER_ROW,
        UFO,
        MARGIN,
        INITIAL_SQUADRON_HEIGHT,
        INVADERS_SPEED
    );
    Squadron squadron = squadronTemplate;
    Spaceship spaceship(SPACESHIP_HEALTH, INVADERS_PER_ROW - 1 + 2 * MARGIN, SPACESHIP_SPEED);
    BulletTracker bulletTracker(SHOT_SPEED, SPACESHIP_SHOT_COOLDOWN, SQUADRON_SHOT_COOLDOWN);
    PiggyBank piggyBank;

    unsigned screenWidth = 600;
    unsigned screenHeight = 600;
    Window window("Space Invaders", &screenHeight, &screenWidth, false, true);
    const float screenRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);


    Cube cube;
    ConstantShaderSet constantShaders;
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

    TexturedModel invader1("../models/invader_01.obj", "../textures/alien_1.png");
    TexturedModel invader2("../models/invader_02.obj", "../textures/alien_2.png");
    TexturedModel invader3("../models/invader_03.obj", "../textures/alien_3.png");
    TexturedModel ufo("../models/ufo.obj", "../textures/spaceship.png");
    TexturedModel mainShip("../models/main_ship.obj", "../textures/spaceship.png");
    BasicModel projectile("../models/projectile.obj");

    auto viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -TRANSLATE_VALUE),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    auto viewRotationVector = glm::vec3(0.0f, 0.0f, 0.0f);
    bool viewShouldRotate = false;
    
    auto sunPosition = glm::vec3(0.0f, 10.0f, 0.0f);
    auto moonPosition = glm::vec3(0.0f, 1.0f, -10.0f);

    auto sunModel = glm::translate(glm::mat4(1.0f), sunPosition);
    auto moonModel = glm::scale(glm::translate(glm::mat4(1.0f), moonPosition), glm::vec3(0.2f, 0.2f, 0.2f));

    float fieldOfView = INITIAL_FIELD_OF_VIEW;
    auto perspectiveMatrix = glm::perspective(glm::radians(INITIAL_FIELD_OF_VIEW), screenRatio, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);

    auto gameModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(
        0.0f,
        GAME_HEIGHT,
        -DISTANCE_FROM_CENTER
    ));
    auto squadronModelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    auto modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(SHIP_SIZE_MULTIPLIER));
    auto spaceshipMatrix = glm::mat4(1.0f);
    auto cubeMapModel = glm::mat4(1.0f);

    auto worldModelMatrix = glm::mat4(1.0f);

    float time;
    int directionY = 0;

    window
        .onInit([]() {
            glClearColor(0.1f, 0.1f, 0.1f, 1.f);
            glEnable(GL_DEPTH_TEST);
        })
        .onLoop([&]() {
            time = static_cast<float>(glfwGetTime());
            glfwSetTime(0.0f);

            if (directionY != 0) {
                viewMatrix = glm::rotate(viewMatrix, glm::radians(0.1f), glm::vec3(
                    directionY,
                    0.0f,
                    0.0f
                ));
                gameModelMatrix = glm::translate(gameModelMatrix, glm::vec3(
                    0.0f,
                    0.0f,
                    static_cast<float>(directionY) * 0.01f
                ));
            }

            worldModelMatrix = glm::translate(
                glm::mat4(1.0f),
                glm::vec3(-spaceship.getX() * TRANSLATE_VALUE, 0.0f, 0.0f)
            );

            glDepthMask(GL_FALSE);
            cubeMapShaders.use();
            glUniformMatrix4fv(cubeMapShaders.uniform("M"), 1, false, glm::value_ptr(cubeMapModel));
            glUniformMatrix4fv(cubeMapShaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(cubeMapShaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            cube.draw(cubeMapShaders);
            
            constantShaders.use();
            glUniformMatrix4fv(constantShaders.uniform("M"), 1, false, glm::value_ptr(sunModel));
            glUniformMatrix4fv(constantShaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(constantShaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            glUniform4f(constantShaders.uniform("color"), 0.98f, 0.99f, 0.38f, 1.0f);
            cube.draw(constantShaders);
            
            constantShaders.use();
            glUniformMatrix4fv(constantShaders.uniform("M"), 1, false, glm::value_ptr(moonModel));
            glUniformMatrix4fv(constantShaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(constantShaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            glUniform4f(constantShaders.uniform("color"), 0.71f, 0.71f, 0.68f, 1.0f);
            cube.draw(constantShaders);
            glDepthMask(GL_TRUE);

            phongShaders.use();
            glUniformMatrix4fv(phongShaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(phongShaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            glUniform3fv(phongShaders.uniform("sun"), 1, glm::value_ptr(sunPosition));
            glUniform3fv(phongShaders.uniform("moon"), 1, glm::value_ptr(moonPosition));

            squadron.resetInvader();
            do {
                if (!squadron.isAlive()) continue;
                glUniformMatrix4fv(lambertShaders.uniform("M"), 1, false, glm::value_ptr(
                    glm::translate(
                        glm::mat4(1.0f),
                        glm::vec3(TRANSLATE_VALUE * squadron.getX(), 0.0f, -TRANSLATE_VALUE * squadron.getY())
                    ) * worldModelMatrix * gameModelMatrix * squadronModelMatrix * modelMatrix
                ));

                switch (squadron.getType()) {
                    case 0:
                        invader1.draw(phongShaders);
                        break;
                    case 1:
                        invader2.draw(phongShaders);
                        break;
                    case 2:
                        invader3.draw(phongShaders);
                        break;
                    case 3:
                        ufo.draw(phongShaders);
                        break;
                }
            } while(squadron.nextInvader());

            glUniformMatrix4fv(lambertShaders.uniform("M"), 1, false, glm::value_ptr(
                glm::translate(glm::mat4(1.0f),
                    glm::vec3(0.0f, 0.0f, -TRANSLATE_VALUE * spaceship.getY())
                ) * gameModelMatrix * spaceshipMatrix * modelMatrix
            ));
            mainShip.draw(phongShaders);

            constantShaders.use();

            glUniformMatrix4fv(constantShaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(constantShaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            glUniform4f(constantShaders.uniform("color"), 1.0f, 1.0f, 0.0f, 1.0f);

            for (auto &bullet : *bulletTracker.getBullets()) {
                glUniformMatrix4fv(constantShaders.uniform("M"), 1, false, glm::value_ptr(
                    glm::translate(
                        glm::mat4(1.0f),
                        glm::vec3(TRANSLATE_VALUE * bullet.getX(), 0.0f, -TRANSLATE_VALUE * bullet.getY())
                    ) * worldModelMatrix * gameModelMatrix * modelMatrix
                ));
                projectile.draw(constantShaders);
            }

            squadron.moveShips(time);
            spaceship.move(time);
            bulletTracker.moveBullets(time);

            bulletTracker.manageCollisions(squadron, spaceship);
            bulletTracker.shootSpaceship(squadron);

            squadron.analyze(piggyBank);

            int result = squadron.checkState();
            if (result == 1 || spaceship.getHealth() == 0) {
                squadron = squadronTemplate;
                spaceship.setHealth(SPACESHIP_HEALTH);
                bulletTracker.clear();
                piggyBank.resetPoints();
                std::cout << std::endl << "Game over" << std::endl;
            }
            if (result == 2) squadron = squadronTemplate;
            std::cout << "\rPoints: " << piggyBank.getPoints() << " | Lives: " << spaceship.getHealth();

            if (viewShouldRotate) {
                cubeMapModel = glm::rotate(cubeMapModel, glm::radians(1.0f), viewRotationVector);
                sunModel = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), viewRotationVector) * sunModel;
                moonModel = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), viewRotationVector) * moonModel;
                sunPosition = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), viewRotationVector) * glm::vec4(sunPosition, 1.0f));
                moonPosition = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), viewRotationVector) * glm::vec4(moonPosition, 1.0f));
            }
        })
        .onKey(GLFW_KEY_A, GLFW_REPEAT, [&]() {
            spaceshipMatrix = glm::rotate(spaceshipMatrix, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.f));
        })
        .onKey(GLFW_KEY_D, GLFW_REPEAT, [&]() {
            spaceshipMatrix = glm::rotate(spaceshipMatrix, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, -1.f));
        })
        .onScroll([&](double y, double x) {
            if (y > 0) {
                fieldOfView += 1.0f;
            } else if (y < 0) {
                fieldOfView -= 1.0f;
            }

            perspectiveMatrix = glm::perspective(glm::radians(fieldOfView), screenRatio, NEAR_CLIPPING_PANE, FAR_CLIPPING_PANE);
        })
        .onMouseMove([&](double y, double x) {
            viewShouldRotate = true;
            if (x < screenWidth / 4) {
                if (y < screenHeight / 4) {
                    viewRotationVector = glm::vec3(-1.0f, -1.0f, 0.0f);
                } else if (y > 3 * screenHeight / 4) {
                    viewRotationVector = glm::vec3(1.0f, -1.0f, 0.0f);
                } else {
                    viewRotationVector = glm::vec3(0.0f, -1.0f, 0.0f);
                }
            } else if (x > 3 * screenWidth / 4) {
                if (y < screenHeight / 4) {
                    viewRotationVector = glm::vec3(-1.0f, 1.0f, 0.0f);
                } else if (y > 3 * screenHeight / 4) {
                    viewRotationVector = glm::vec3(1.0f, 1.0f, 0.0f);
                } else {
                    viewRotationVector = glm::vec3(0.0f, 1.0f, 0.0f);
                }
            } else {
                if (y < screenHeight / 4) {
                    viewRotationVector = glm::vec3(-1.0f, 0.0f, 0.0f);
                } else if (y > 3 * screenHeight / 4) {
                    viewRotationVector = glm::vec3(1.0f, 0.0f, 0.0f);
                } else {
                    viewRotationVector = glm::vec3(0.0f, 0.0f, 0.0f);
                    viewShouldRotate = false;
                }
            }
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
        .onKey(GLFW_KEY_SPACE, GLFW_PRESS, [&]() {
            bulletTracker.shootInvaders(spaceship);
        })
        .onKey(GLFW_KEY_UP, GLFW_PRESS, [&]() {directionY = 1;})
        .onKey(GLFW_KEY_DOWN, GLFW_PRESS, [&]() {directionY = -1;})
        .onKey(GLFW_KEY_UP, GLFW_RELEASE, [&]() {
            directionY -= 1;
            if (directionY < -1) directionY = -1;
        })
        .onKey(GLFW_KEY_DOWN, GLFW_RELEASE, [&]() {
            directionY += 1;
            if (directionY > 1) directionY = 1;
        })
        ;

    return window.run();
}
