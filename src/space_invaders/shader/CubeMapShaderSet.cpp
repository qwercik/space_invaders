#include <space_invaders/shader/Shader.hpp>
#include <space_invaders/shader/CubeMapShaderSet.hpp>
#include <GL/glew.h>

namespace space_invaders::shader {
    CubeMapShaderSet::CubeMapShaderSet() {
        this->attach(Shader(GL_VERTEX_SHADER, "../shaders/cube_map/v_cube_map.glsl"));
        this->attach(Shader(GL_FRAGMENT_SHADER, "../shaders/cube_map/f_cube_map.glsl"));
        this->link();
    }
}

