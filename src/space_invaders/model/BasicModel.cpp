#include <space_invaders/model/BasicModel.hpp>
#include <GL/glew.h>

namespace space_invaders::model {
    void BasicModel::draw() const {
        for (int i = 0; i < 4; i++) {
            glEnableVertexAttribArray(i);
        }

        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, this->getVerticesArray());
        glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, this->getNormalVectorsArray());
        glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, this->getTexturingCoordinatesArray());
        glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, this->getColorsArray());

        glDrawArrays(GL_TRIANGLES, 0, this->getVerticesNumber());
        
        for (int i = 0; i < 4; i++) {
            glDisableVertexAttribArray(i);
        }
    }
}
