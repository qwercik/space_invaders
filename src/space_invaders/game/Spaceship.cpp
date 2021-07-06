#include <space_invaders/game/Spaceship.hpp>
#include <algorithm>

namespace space_invaders::game {
    Spaceship::Spaceship(int gridWidth, float speed) :
        gridWidth(gridWidth),
        x{static_cast<float>(gridWidth) / 2.0f},
        health{3},
        speed{speed},
        direction{0}
{}

    float Spaceship::getX() {return this->x;}

    void Spaceship::setDirection(int direction) {this->direction = direction;}

    void Spaceship::modifyDirection(int modificator) {
        this->direction += modificator;
        if (this->direction < -1) this->direction = -1;
        if (this->direction > 1) this->direction = 1;
    }

    void Spaceship::move(float time) {
        this->x = std::max(0.0f, std::min(
            this->x + time * this->speed * static_cast<float>(this->direction),
            static_cast<float>(this->gridWidth)
        ));
    }
}
