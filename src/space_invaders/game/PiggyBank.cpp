#include <space_invaders/game/PiggyBank.hpp>

namespace space_invaders::game {
    int PiggyBank::getPoints() {return this->points;}

    void PiggyBank::resetPoints() {this->points = 0;}

    bool PiggyBank::nextRow() {
        if (this->rowIndex + 1 < this->rowLimit) {
            ++this->rowIndex;
            return true;
        }
        return false;
    }

    void PiggyBank::resetRow() {this->rowIndex = 0;}

    void PiggyBank::refreshRow(int current, int type) {
        int difference;
        if (this->rowIndex == this->rowLimit) {
            this->alivePerWave.push_back(current);
            ++this->rowLimit;
            ++this->rowIndex;
        }
        else {
            difference = this->alivePerWave.at(this->rowIndex) - current;
            if (difference > 0)
                switch (type) {
                    case 0:
                        this->points += 10 * difference;
                        break;
                    case 1:
                        this->points += 20 * difference;
                        break;
                    case 2:
                        this->points += 30 * difference;
                        break;
                    case 3:
                        this->points += 100 * difference;
                        break;
                }
            this->alivePerWave.at(this->rowIndex) = current;
        }
    }
}
