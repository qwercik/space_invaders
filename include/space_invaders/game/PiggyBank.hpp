#pragma once

#include <vector>

namespace space_invaders::game {
    class PiggyBank {
    public:
        int getPoints();
        void resetPoints();

        bool nextRow();
        void resetRow();
        void refreshRow(int current, int type);

    private:
        int rowIndex{0};
        int rowLimit{0};
        int points{0};
        std::vector<int> alivePerWave;
    };
}
