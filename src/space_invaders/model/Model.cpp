#include <space_invaders/model/Model.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <GL/glew.h>

namespace space_invaders::model {
    void Model::drawOutline(const shader::ShaderSet& shader) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        this->draw(shader);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
