#pragma once

#include <space_invaders/model/Model.hpp>
#include <vector>

namespace space_invaders::model {
    class BasicModel : public Model {
    public:
        virtual void draw() const override;

    protected:
        unsigned verticesNumber;
        std::vector<float> vertices;
        std::vector<float> normalVectors;
        std::vector<float> texturingCoordinates;
        std::vector<float> colors;
    };
}
