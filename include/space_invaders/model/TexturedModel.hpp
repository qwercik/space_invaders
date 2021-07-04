#pragma once

#include <space_invaders/model/BasicModel.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <space_invaders/texture/Texture.hpp>
#include <vector>
#include <memory>
#include <string>

namespace space_invaders::model {
    class TexturedModel : public BasicModel {
    public:
        TexturedModel(const std::string& modelFilename, const std::string& textureFilename);
        TexturedModel(BasicModel&& model, const std::string& textureFilename);

        virtual void draw(const shader::ShaderSet& shaders) const override;

    protected:
        TexturedModel() = default;
        bool initialize(const std::string& modelFilename, const std::string& textureFilename);

        std::unique_ptr<texture::Texture> texture;
    };
}
