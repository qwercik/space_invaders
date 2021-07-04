#include <space_invaders/shader/Shader.hpp>
#include <space_invaders/shader/TexturedShaderSet.hpp>
#include <GL/glew.h>

namespace space_invaders::shader {
    TexturedShaderSet::TexturedShaderSet() {
        this->attach(Shader(GL_VERTEX_SHADER, "../shaders/textured/v_textured.glsl"));
        this->attach(Shader(GL_FRAGMENT_SHADER, "../shaders/textured/f_textured.glsl"));
        this->link();
    }
}
