#include <space_invaders/shader/Shader.hpp>
#include <space_invaders/shader/LambertShaderSet.hpp>
#include <GL/glew.h>

namespace space_invaders::shader {
    LambertShaderSet::LambertShaderSet() {
        this->attach(Shader(GL_VERTEX_SHADER, "../shaders/lambert/v_lambert.glsl"));
        this->attach(Shader(GL_FRAGMENT_SHADER, "../shaders/lambert/f_lambert.glsl"));
        this->link();
    }
}
