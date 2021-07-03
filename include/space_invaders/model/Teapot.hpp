#pragma once

#include <space_invaders/model/BasicModel.hpp>
#include <vector>

namespace space_invaders::model {
    class Teapot : public BasicModel {
    protected:
        virtual unsigned getVerticesNumber() const override {
            return Teapot::verticesNumber;
        }

        virtual const float *getVerticesArray() const override {
            return Teapot::verticesArray.data();
        }

        virtual const float *getNormalVectorsArray() const override {
            return Teapot::normalVectorsArray.data();
        }

        virtual const float *getTexturingCoordinatesArray() const override {
            return Teapot::texturingCoordinatesArray.data();
        }

        virtual const float *getColorsArray() const override {
            return Teapot::colorsArray.data();
        }

    private:
        static const unsigned verticesNumber;
        static const std::vector<float> verticesArray;
        static const std::vector<float> normalVectorsArray;
        static const std::vector<float> texturingCoordinatesArray;
        static const std::vector<float> colorsArray;
    };
}
