#include <space_invaders/model/BasicModel.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <obj_loader/obj_loader.h>
#include <GL/glew.h>

namespace space_invaders::model {
    BasicModel::BasicModel(const std::string& modelFilename) {
        this->ok = this->loadModelFromFile(modelFilename);
    }

    BasicModel::BasicModel(BasicModel&& model) {
        this->verticesNumber = model.verticesNumber;
        this->vertices = std::move(model.vertices);
        this->normalVectors = std::move(model.normalVectors);
        this->texturingCoordinates = std::move(model.texturingCoordinates);
    }
    
    void BasicModel::draw(const shader::ShaderSet& shaders) const {
        for (int i = 0; i < 3; i++) {
            glEnableVertexAttribArray(i);
        }

        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, this->vertices.data());
        glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, this->normalVectors.data());
        glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, this->texturingCoordinates.data());

        glDrawArrays(GL_TRIANGLES, 0, this->verticesNumber);
        
        for (int i = 0; i < 3; i++) {
            glDisableVertexAttribArray(i);
        }
    }

    BasicModel::operator bool() const {
        return this->ok;
    }

    bool BasicModel::loadModelFromFile(const std::string& filename) {
        objl::Loader loader;
        if (!loader.LoadFile(filename)) {
            return false;
        }

        this->verticesNumber = 0;
        for (const auto& vertex : loader.LoadedVertices) {
            this->vertices.push_back(vertex.Position.X);
            this->vertices.push_back(vertex.Position.Y);
            this->vertices.push_back(vertex.Position.Z);
            this->vertices.push_back(1.0f);

            this->normalVectors.push_back(vertex.Normal.X);
            this->normalVectors.push_back(vertex.Normal.Y);
            this->normalVectors.push_back(vertex.Normal.Z);
            this->normalVectors.push_back(0.0f);

            this->texturingCoordinates.push_back(vertex.TextureCoordinate.X);
            this->texturingCoordinates.push_back(vertex.TextureCoordinate.Y);
            this->verticesNumber++;
        }

        return true;
    }
}
