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
#include <space_invaders/shader/CubeMapShaderSet.hpp>
#include <space_invaders/texture/CubeMapTexture.hpp>
#include <space_invaders/model/TexturedModel.hpp>
#include <space_invaders/model/predefined/Teapot.hpp>
#include <space_invaders/model/predefined/Cube.hpp>
#include <space_invaders/model/predefined/Wall.hpp>
#include <space_invaders/model/HierarchicalModel.hpp>

using space_invaders::window::Window;
using space_invaders::shader::LambertTexturedShaderSet;
using space_invaders::shader::CubeMapShaderSet;
using space_invaders::model::HierarchicalModel;
using space_invaders::model::predefined::Cube;
using space_invaders::model::predefined::Teapot;
using space_invaders::model::predefined::Wall;
using space_invaders::model::TexturedModel;
using space_invaders::texture::CubeMapTexture;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const float SCREEN_RATIO = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);


int main() {
    Window window("Space Invaders", SCREEN_WIDTH, SCREEN_HEIGHT, true);
    LambertTexturedShaderSet shaders;
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

    Cube cube;


    auto viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 0.5f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    auto perspectiveMatrix = glm::perspective(glm::radians(50.0f), SCREEN_RATIO, 0.1f, 10.0f);
    auto modelMatrix = glm::mat4(1.0f);

    window
        .onInit([]() {
            glClearColor(0.1f, 0.1f, 0.1f, 1.f);
            glEnable(GL_DEPTH_TEST);
        })
        .onLoop([&]() {
            glDepthMask(GL_FALSE);
            cubeMapShaders.use();
            glUniformMatrix4fv(shaders.uniform("M"), 1, false, glm::value_ptr(modelMatrix));
            glUniformMatrix4fv(shaders.uniform("V"), 1, false, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(shaders.uniform("P"), 1, false, glm::value_ptr(perspectiveMatrix));
            cube.draw(cubeMapShaders);
            glDepthMask(GL_TRUE);

            modelMatrix = glm::rotate(modelMatrix, 3 / 180.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        });

    return window.run();
}
