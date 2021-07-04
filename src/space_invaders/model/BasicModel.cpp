#include <space_invaders/model/BasicModel.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <GL/glew.h>

namespace space_invaders::model {
    void BasicModel::draw(const shader::ShaderSet& shaders) const {
        for (int i = 0; i < 4; i++) {
            glEnableVertexAttribArray(i);
        }

        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, this->vertices.data());
        glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, this->normalVectors.data());
        glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, this->texturingCoordinates.data());
        glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, this->colors.data());

        glDrawArrays(GL_TRIANGLES, 0, this->verticesNumber);
        
        for (int i = 0; i < 4; i++) {
            glDisableVertexAttribArray(i);
        }
    }
}
