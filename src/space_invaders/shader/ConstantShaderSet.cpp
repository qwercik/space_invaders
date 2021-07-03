#include <space_invaders/shader/Shader.hpp>
#include <space_invaders/shader/ConstantShaderSet.hpp>
#include <GL/glew.h>

namespace space_invaders::shader {
    ConstantShaderSet::ConstantShaderSet() {
        this->attach(Shader(GL_VERTEX_SHADER, "../shaders/constant/v_constant.glsl"));
        this->attach(Shader(GL_FRAGMENT_SHADER, "../shaders/constant/f_constant.glsl"));
        this->link();
    }
}
