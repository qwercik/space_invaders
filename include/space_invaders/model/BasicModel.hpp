#pragma once

#include <space_invaders/model/Model.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <vector>

namespace space_invaders::model {
    class BasicModel : public Model {
    public:
        virtual void draw(const shader::ShaderSet& shaders) const override;

    protected:
        unsigned verticesNumber;
        std::vector<float> vertices;
        std::vector<float> normalVectors;
        std::vector<float> texturingCoordinates;
        std::vector<float> colors;
    };
}
