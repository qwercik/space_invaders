#include <space_invaders/shader/Shader.hpp>
#include <space_invaders/shader/PhongShaderSet.hpp>
#include <GL/glew.h>

namespace space_invaders::shader {
    PhongShaderSet::PhongShaderSet() {
        this->attach(Shader(GL_VERTEX_SHADER, "../shaders/phong/v_phong.glsl"));
        this->attach(Shader(GL_FRAGMENT_SHADER, "../shaders/phong/f_phong.glsl"));
        this->link();
    }
}
