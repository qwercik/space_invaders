#include <space_invaders/game/BulletTracker.hpp>
#include <list>

namespace space_invaders::game {
    BulletTracker::BulletTracker(float bulletSpeed, float spaceshipCooldown, float squadronCooldown) :
        bulletSpeed{bulletSpeed},
        spaceshipCooldown{spaceshipCooldown},
        squadronCooldown{squadronCooldown}
    {}

    std::list<Bullet> *BulletTracker::getBullets() {return &this->bullets;}

    void BulletTracker::shootInvaders(Spaceship &spaceship) {
        if (spaceship.getCooldown() == 0.0f) {
            this->bullets.emplace_back(Bullet(spaceship.getX(), spaceship.getY(), 1));
            spaceship.setCooldown(this->spaceshipCooldown);
        }
    }

    void BulletTracker::shootSpaceship(Squadron &squadron) {
        Bullet bullet(0.0f, 0.0f, 0);
        if (squadron.getCooldown() == 0.0f) {
            bullet = squadron.randomShot();
            if (bullet.getTarget() != 0) {
                this->bullets.push_back(bullet);
                squadron.setCooldown(this->squadronCooldown);
            }
        }
    }

    void BulletTracker::manageCollisions(Squadron &squadron, Spaceship &spaceship) {
        for (auto &bullet : this->bullets) {
            if (bullet.getTarget() == -1) {
                switch (Bullet::checkYCollision(bullet.getY(), spaceship.getY())) {
                    case 0:
                        if (Bullet::checkXCollision(bullet.getX(), spaceship.getX()) == 0) {
                            spaceship.modifyHealth(-1);
                            bullet.invalidate();
                        }
                        break;
                    case -1:
                        bullet.invalidate();
                        break;
                }
            }
            else {
                if (squadron.killClosest(bullet.getX(), bullet.getY()) >= 0) bullet.invalidate();
            }
        }
        this->bullets.remove_if([](Bullet b){return !b.isValid();});
    }

    void BulletTracker::moveBullets(float time) {
        for (auto &bullet : this->bullets) {
            bullet.setY(bullet.getY() + static_cast<float>(bullet.getTarget()) * this->bulletSpeed * time);
        }
    }

    void BulletTracker::clear() {this->bullets = std::list<Bullet>();}
}
