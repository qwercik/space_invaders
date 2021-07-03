#pragma once

#include <space_invaders/model/BasicModel.hpp>
#include <vector>

namespace space_invaders::model {
    class Cube : public BasicModel {
    protected:
        virtual unsigned getVerticesNumber() const override {
            return Cube::verticesNumber;
        }

        virtual const float *getVerticesArray() const override {
            return Cube::verticesArray.data();
        }

        virtual const float *getNormalVectorsArray() const override {
            return Cube::normalVectorsArray.data();
        }

        virtual const float *getTexturingCoordinatesArray() const override {
            return Cube::texturingCoordinatesArray.data();
        }

        virtual const float *getColorsArray() const override {
            return Cube::colorsArray.data();
        }

    private:
        static const unsigned verticesNumber;
        static const std::vector<float> verticesArray;
        static const std::vector<float> normalVectorsArray;
        static const std::vector<float> texturingCoordinatesArray;
        static const std::vector<float> colorsArray;
    };
}
