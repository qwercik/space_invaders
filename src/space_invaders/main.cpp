#include <space_invaders/shader/ShaderSet.hpp>
#include <iostream>
#include <GL/glew.h>

using space_invaders::shader::Shader;
using space_invaders::shader::ShaderSet;

int main() {
    ShaderSet shaders;
    shaders
        .attach(Shader(GL_VERTEX_SHADER, "../src/space_invaders/shader/v_lambert.glsl"))
        .attach(Shader(GL_FRAGMENT_SHADER, "../src/space_invaders/shader/f_lambert.glsl"))
        .link();
}
