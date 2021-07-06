#pragma once

#include <space_invaders/game/Wave.hpp>

namespace space_invaders::game {
    class Squadron {
    public:
        Squadron(int numberOfRows, int invadersPerRow, bool ufo, int margin, float squadronY, float descentSpeed);
        bool nextInvader();
        void resetInvader();
        int getType();
        float getX();
        float getY();
        void moveShips(float time);
        int checkState();

    private:
        int rowIndex;
        int rowLimit;
        std::vector<Wave> waves;
    };
}
