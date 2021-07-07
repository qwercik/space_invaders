#include <space_invaders/game/Bullet.hpp>

namespace space_invaders::game {
    Bullet::Bullet(float x, float y, int target) : x{x}, y{y}, target{target}, valid{true} {}

    float Bullet::getX() {return this->x;}

    float Bullet::getY() {return this->y;}

    void Bullet::setY(float y) {this->y = y;}

    int Bullet::getTarget() {return this->target;}

    bool Bullet::isValid() {return this->valid;}

    void Bullet::invalidate() {this->valid = false;}

    bool Bullet::operator==(Bullet &other) {return this->x == other.x && this->y == other.y;}

    int Bullet::checkXCollision(float x, float targetX) {
        if (x < targetX - 0.5f) return -1;
        else if (x <= targetX + 0.5f) return 0;
        else return 1;
    }

    int Bullet::checkYCollision(float y, float targetY) {
        if (y < targetY - 0.5f) return -1;
        else if (y <= targetY + 0.5f) return 0;
        else return 1;
    }
}
