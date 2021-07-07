#include <space_invaders/game/BulletTracker.hpp>
#include <list>

namespace space_invaders::game {
    BulletTracker::BulletTracker(float bulletSpeed, float shotCooldown) :
        bulletSpeed{bulletSpeed},
        shotCooldown{shotCooldown}
    {}

    std::list<Bullet> *BulletTracker::getBullets() {return &this->bullets;}

    void BulletTracker::shootInvaders(Spaceship* spaceship, float time) {
        if (spaceship->getCooldown() == 0.0f) {
            this->bullets.emplace_back(Bullet(spaceship->getX(), spaceship->getY(), 1));
            spaceship->setCooldown(this->shotCooldown);
        }
    }

    void BulletTracker::shootSpaceship(Squadron* squadron, float time) {
        this->bullets.emplace_back(Bullet(0.0f, 0.0f, -1));
    }

    void BulletTracker::manageCollisions(Squadron *squadron, Spaceship *spaceship) {
        for (auto &bullet : this->bullets) {
            if (bullet.getTarget() == -1) {
                switch (Bullet::checkYCollision(bullet.getY(), spaceship->getY())) {
                    case 0:
                        if (Bullet::checkXCollision(bullet.getX(), spaceship->getX()) == 0) {
                            spaceship->modifyHealth(-1);
                            bullet.invalidate();
                        }
                        break;
                    case -1:
                        bullet.invalidate();
                        break;
                }
            }
            else {
                if (squadron->killClosest(bullet.getX(), bullet.getY()) >= 0) bullet.invalidate();
            }
        }
        this->bullets.remove_if([](Bullet b){return !b.isValid();});
    }

    void BulletTracker::moveBullets(float time) {
        for (auto &bullet : this->bullets) {
            bullet.setY(bullet.getY() + static_cast<float>(bullet.getTarget()) * this->bulletSpeed * time);
        }
    }
}
