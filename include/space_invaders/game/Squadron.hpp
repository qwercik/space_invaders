#pragma once

#include <space_invaders/game/Wave.hpp>
#include <space_invaders/game/Bullet.hpp>
#include <space_invaders/game/PiggyBank.hpp>
#include <algorithm>
#include <random>

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
        float getCooldown();
        void setCooldown(float cooldown);

        void moveShips(float time);
        int checkState();
        void analyze(PiggyBank &piggyBank);
        int killClosest(float x, float y);
        Bullet randomShot();

    private:
        int rowIndex;
        int rowLimit;
        std::vector<Wave> waves;
        float cooldown;
    };
}
