#pragma once

#include <space_invaders/game/Invader.hpp>
#include <space_invaders/game/Bullet.hpp>

namespace space_invaders::game {
    class Wave {
    public:
        Wave(
            int invaderNumber,
            int invaderType,
            float margin,
            float positionX,
            float speedY,
            float positionY,
            bool positiveDirection
        );
        bool nextInvader();
        void resetInvader();
        int getType();
        int getAlive();
        float getX();
        float getY();
        bool isAlive();
        void moveShips(float time);
        int killClosest(float x);

    private:
        int invaderIndex;
        int invaderLimit;
        int invadersAlive;
        float margin;
        float speedX;
        float positionX;
        float speedY;
        float positionY;
        bool positiveDirection;
        std::vector<Invader> invaders;
    };
}
