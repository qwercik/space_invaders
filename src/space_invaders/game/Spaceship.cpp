#include <space_invaders/game/Spaceship.hpp>
#include <algorithm>

namespace space_invaders::game {
    Spaceship::Spaceship(int health, int gridWidth, float speed) :
        gridWidth(gridWidth),
        x{static_cast<float>(gridWidth) / 2.0f},
        y{-1.0},
        health{health},
        speed{speed},
        direction{0},
        cooldown{0.0f}
{}

    float Spaceship::getX() {return this->x;}

    float Spaceship::getY() {return this->y;}

    float Spaceship::getCooldown() {return this->cooldown;}

    void Spaceship::setCooldown(float cooldown) {this->cooldown = cooldown;}

    int Spaceship::getHealth() {return this->health;}

    void Spaceship::setHealth(int value) {this->health = value;}

    void Spaceship::modifyHealth(int value) {
        if (this->health != -1) this->health = std::max(this->health + value, 0);
    }

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
        this->cooldown = std::max(this->cooldown - time, 0.0f);
    }
}
