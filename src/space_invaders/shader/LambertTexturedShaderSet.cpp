#include <space_invaders/shader/Shader.hpp>
#include <space_invaders/shader/LambertTexturedShaderSet.hpp>
#include <GL/glew.h>

namespace space_invaders::shader {
    LambertTexturedShaderSet::LambertTexturedShaderSet() {
        this->attach(Shader(GL_VERTEX_SHADER, "../shaders/lambert_textured/v_lamberttextured.glsl"));
        this->attach(Shader(GL_FRAGMENT_SHADER, "../shaders/lambert_textured/f_lamberttextured.glsl"));
        this->link();
    }
}
