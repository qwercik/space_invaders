#pragma once

#include <space_invaders/game/Bullet.hpp>
#include <space_invaders/game/Squadron.hpp>
#include <space_invaders/game/Spaceship.hpp>
#include <list>

namespace space_invaders::game {
    class BulletTracker {
    public:
        BulletTracker(float bulletSpeed, float shotCooldown);
        std::list<Bullet> *getBullets();
        void shootInvaders(Spaceship *spaceship, float time);
        void shootSpaceship(Squadron *squadron, float time);
        void manageCollisions(Squadron *squadron, Spaceship *spaceship);
        void moveBullets(float time);

    private:
        float bulletSpeed;
        float shotCooldown;
        std::list<Bullet> bullets;
    };
}
