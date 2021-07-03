#pragma once

#include <space_invaders/model/Model.hpp>

namespace space_invaders::model {
    class BasicModel : public Model {
    public:
        virtual void draw() const override;

    protected:
        virtual unsigned getVerticesNumber() const = 0;
        virtual const float *getVerticesArray() const = 0;
        virtual const float *getNormalVectorsArray() const = 0;
        virtual const float *getTexturingCoordinatesArray() const = 0;
        virtual const float *getColorsArray() const = 0;
    };
}
