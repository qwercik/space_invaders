#pragma once

#include <space_invaders/game/Wave.hpp>
#include <space_invaders/game/Bullet.hpp>

namespace space_invaders::game {
    class Squadron {
    public:
        Squadron(
            int numberOfRows,
            int invadersPerRow,
            bool ufo,
            int margin,
            float squadronY,
            float descentSpeed
        );
        bool nextInvader();
        void resetInvader();
        int getType();
        float getX();
        float getY();
        bool isAlive();
        void moveShips(float time);
        int checkState();
        int killClosest(float x, float y);

    private:
        int rowIndex;
        int rowLimit;
        std::vector<Wave> waves;
    };
}
