#include <space_invaders/model/TexturedModel.hpp>
#include <GL/glew.h>

namespace space_invaders::model {
    TexturedModel::TexturedModel(const std::string& modelFilename, const std::string& textureFilename) {
        this->ok = this->initialize(modelFilename, textureFilename);
    }
    
    TexturedModel::TexturedModel(BasicModel&& model, const std::string& textureFilename) :
        BasicModel(std::move(model))
    {
        this->texture = std::make_unique<texture::Texture>(textureFilename);
        this->ok = static_cast<bool>(this->texture);
    }
    
    void TexturedModel::draw(const shader::ShaderSet& shaders) const {
        glEnableVertexAttribArray(shaders.attribute("vertex"));
        glEnableVertexAttribArray(shaders.attribute("texCoord"));
        glEnableVertexAttribArray(shaders.attribute("normal"));

        glVertexAttribPointer(shaders.attribute("vertex"), 4, GL_FLOAT, false, 0, this->vertices.data());
        glVertexAttribPointer(shaders.attribute("normal"), 4, GL_FLOAT, false, 0, this->normalVectors.data());
        glVertexAttribPointer(shaders.attribute("texCoord"), 2, GL_FLOAT, false, 0, this->texturingCoordinates.data());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture->getHandle());
        glUniform1i(shaders.uniform("tex"), 0);

        glDrawArrays(GL_TRIANGLES, 0, this->verticesNumber);
        
        glDisableVertexAttribArray(shaders.attribute("vertex"));
        glDisableVertexAttribArray(shaders.attribute("texCoord"));
        glDisableVertexAttribArray(shaders.attribute("normal"));
    }

    bool TexturedModel::initialize(const std::string& modelFilename, const std::string& textureFilename) {
        this->texture = std::make_unique<texture::Texture>(textureFilename);
        if (!this->texture) {
            return false;
        }

        return this->loadModelFromFile(modelFilename);
    }
}
