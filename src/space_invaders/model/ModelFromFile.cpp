#include <space_invaders/model/ModelFromFile.hpp>
#include <obj_loader/obj_loader.h>
#include <string>

namespace space_invaders::model {
    ModelFromFile::ModelFromFile(const std::string& filename) {
        objl::Loader loader;
        this->ok = loader.LoadFile(filename);
        if (!this->ok) {
            return;
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

            for (int i = 0; i < 4; i++) {
                this->colors.push_back(static_cast<float>(1.0f));
            }

            this->verticesNumber++;
        }
    }
    
    ModelFromFile::operator bool() const {
        return this->ok;
    }
}
