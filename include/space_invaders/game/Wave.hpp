#pragma once

#include <space_invaders/game/Invader.hpp>

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
        float getX();
        float getY();
        void moveShips(float time);

    private:
        int invaderIndex;
        int invaderLimit;
        float margin;
        float speedX;
        float positionX;
        float speedY;
        float positionY;
        bool positiveDirection;
        std::vector<Invader> invaders;
    };
}
