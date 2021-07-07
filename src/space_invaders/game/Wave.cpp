#include <space_invaders/game/Wave.hpp>

namespace space_invaders::game {
    Wave::Wave(
        int invaderNumber,
        int invaderType,
        float margin,
        float positionX,
        float speedY,
        float positionY,
        bool positiveDirection
    ) :
        invaderIndex{0},
        invaderLimit{invaderNumber},
        invadersAlive{invaderNumber},
        margin{margin},
        positionX{positionX},
        speedY{speedY},
        positionY{positionY},
        positiveDirection{positiveDirection}
    {
        this->invaders = std::vector<Invader>();

        for (int i = 0; i < this->invaderLimit; ++i)
            this->invaders.emplace_back(Invader(invaderType, i));

        this->speedX = this->speedY * static_cast<float>(4 * this->margin);
    }

    bool Wave::nextInvader() {
        if (this->invaderIndex + 1 < this->invaderLimit) {
            ++this->invaderIndex;
            return true;
        }
        return false;
    }

    void Wave::resetInvader() {this->invaderIndex = 0;}

    int Wave::getType() {return this->invaders.at(this->invaderIndex).type;}

    int Wave::getAlive() {return this->invadersAlive;}

    float Wave::getX() {return static_cast<float>(this->invaders.at(this->invaderIndex).x) + this->positionX;}

    float Wave::getY() {return positionY;}

    bool Wave::isAlive() {return this->invaders.at(this->invaderIndex).alive;}

    void Wave::moveShips(float time) {
        positionX += (this->positiveDirection ? 1.0f : -1.0f) * this->speedX * time;
        if (this->margin < abs(this->positionX - this->margin)) {
            this->positiveDirection = !this->positiveDirection;
            this->positionX +=
                (this->positiveDirection ? -1.0f : 1.0f) *
                (this->margin - abs(this->positionX - this->margin));
        }
        positionY -= this->speedY * time;
    }

    int Wave::killClosest(float x) {
        for (auto &invader : this->invaders) {
            switch (Bullet::checkYCollision(x - this->positionX, static_cast<float>(invader.x))) {
                case -1:
                    return -1;
                case 0:
                    if (invader.alive) {
                        invader.alive = false;
                        --this->invadersAlive;
                        return 0;
                    }
                    break;
            }
        }
        return 1;
    }
}
