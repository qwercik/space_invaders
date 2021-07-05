#include <space_invaders/model/predefined/Wall.hpp>

namespace space_invaders::model::predefined {
    Wall::Wall() {
        this->verticesNumber = 6;

        this->vertices = {
            -1.0f, -1.0f, 0.0f, 1.0f, // Bottom left
            -1.0f,  1.0f, 0.0f, 1.0f, // Top left
             1.0f,  1.0f, 0.0f, 1.0f, // Top right

            -1.0f, -1.0f, 0.0f, 1.0f, // Bottom left
             1.0f, -1.0f, 0.0f, 1.0f, // Bottom right
             1.0f,  1.0f, 0.0f, 1.0f, // Top right
        };

        this->normalVectors = {
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
        };

        this->texturingCoordinates = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
        };
    }
}

