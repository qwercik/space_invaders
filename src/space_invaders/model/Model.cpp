#include <space_invaders/model/Model.hpp>
#include <GL/glew.h>

namespace space_invaders::model {
    void Model::drawOutline() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        this->draw();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
