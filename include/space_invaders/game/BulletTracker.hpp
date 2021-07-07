#pragma once

#include <space_invaders/game/Bullet.hpp>
#include <space_invaders/game/Squadron.hpp>
#include <space_invaders/game/Spaceship.hpp>
#include <list>

namespace space_invaders::game {
    class BulletTracker {
    public:
        BulletTracker(float bulletSpeed, float spaceshipCooldown, float squadronCooldown);
        std::list<Bullet> *getBullets();
        void shootInvaders(Spaceship &spaceship);
        void shootSpaceship(Squadron &squadron);
        void manageCollisions(Squadron &squadron, Spaceship &spaceship);
        void moveBullets(float time);
        void clear();

    private:
        float bulletSpeed;
        float spaceshipCooldown;
        float squadronCooldown;
        std::list<Bullet> bullets;
    };
}
