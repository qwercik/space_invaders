#pragma once

#include <space_invaders/model/Model.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <vector>
#include <string>

namespace space_invaders::model {
    class BasicModel : public Model {
    public:
        BasicModel(const std::string& modelFilename);
        BasicModel(BasicModel&& model);

        virtual void draw(const shader::ShaderSet& shaders) const override;
        operator bool() const;

    protected:
        BasicModel() = default;
        bool loadModelFromFile(const std::string& filename);

        unsigned verticesNumber;
        std::vector<float> vertices;
        std::vector<float> normalVectors;
        std::vector<float> texturingCoordinates;
        bool ok;
    };
}
