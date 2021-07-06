#include <space_invaders/game/Squadron.hpp>
#include <space_invaders/game/Wave.hpp>

namespace space_invaders::game {
    Squadron::Squadron(
        int numberOfRows,
        int invadersPerRow,
        bool ufo, int margin,
        float squadronY,
        float descentSpeed
    ) :
        rowIndex{0},
        rowLimit{numberOfRows + static_cast<int>(ufo)}
    {
        // establishing positions
        this->waves = std::vector<Wave>();

        int invaderType;
        for (int i = 0; i < this->rowLimit - 1; ++i) {
            if (i % 6 == 0 || i % 6 == 1) invaderType = 0;
            if (i % 6 == 2 || i % 6 == 3) invaderType = 1;
            if (i % 6 == 4 || i % 6 == 5) invaderType = 2;
            this->waves.emplace_back(Wave(
                invadersPerRow,
                invaderType,
                static_cast<float>(margin),
                static_cast<float>(margin),
                descentSpeed,
                squadronY + static_cast<float>(i) - 0.5f,
                true
            ));
        }

        if (ufo) this->waves.emplace_back(Wave(
            1,
            3,
            static_cast<float>(invadersPerRow - 1) / 2.0f + static_cast<float>(margin),
            static_cast<float>(invadersPerRow - 1) / 2.0f + static_cast<float>(margin),
            descentSpeed,
            squadronY + static_cast<float>(this->rowLimit - 1) - 0.5f,
            false
        ));
    }

    bool Squadron::nextInvader() {
        if (this->waves.at(this->rowIndex).nextInvader()) {
            return true;
        }
        if (this->rowIndex + 1 < this->rowLimit) {
            this->waves.at(this->rowIndex).resetInvader();
            ++this->rowIndex;
            return true;
        }
        else return false;
    }

    void Squadron::resetInvader() {
        this->waves.at(this->rowIndex).resetInvader();
        this->rowIndex = 0;
    }

    int Squadron::getType() {return this->waves.at(this->rowIndex).getType();}

    float Squadron::getX() {return this->waves.at(this->rowIndex).getX();}

    float Squadron::getY() {return this->waves.at(this->rowIndex).getY();}

    void Squadron::moveShips(float time) {
        for (int i = 0; i < this->rowLimit; ++i)
            this->waves.at(i).moveShips(time);
    }
}
