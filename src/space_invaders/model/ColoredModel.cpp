#include <space_invaders/model/ColoredModel.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <GL/glew.h>
#include <string>

namespace space_invaders::model {
    ColoredModel::ColoredModel(const std::string& filename) {
        this->ok = this->initialize(filename); 
    }

    void ColoredModel::draw(const shader::ShaderSet& shaders) const {
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

    bool ColoredModel::initialize(const std::string& filename) {
        if (!this->loadModelFromFile(filename)) {
            return false;
        }
        
        for (auto i = 0; i < this->verticesNumber; i++) {
            this->colors.push_back(1.0f);
            this->colors.push_back(0.75f);
            this->colors.push_back(0.80f);
            this->colors.push_back(1.0f);
        }

        return true;
    }
}
