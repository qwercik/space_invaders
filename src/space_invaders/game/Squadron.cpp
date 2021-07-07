#include <space_invaders/game/Squadron.hpp>
#include <algorithm>
#include <random>

namespace space_invaders::game {
    Squadron::Squadron(
        int numberOfRows,
        int invadersPerRow,
        bool ufo,
        int margin,
        float squadronY,
        float descentSpeed
    ) :
        rowIndex{0},
        rowLimit{numberOfRows + static_cast<int>(ufo)},
        cooldown{0.0f}
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

    bool Squadron::isAlive() {return this->waves.at(this->rowIndex).isAlive();}

    float Squadron::getCooldown() {return this->cooldown;}

    void Squadron::setCooldown(float cooldown) {this->cooldown = cooldown;}

    void Squadron::moveShips(float time) {
        for (auto &wave : this->waves)
            wave.moveShips(time);
        this->cooldown = std::max(this->cooldown - time, 0.0f);
    }

    int Squadron::checkState() {
        // 0 - nothing special, 1 - defeat, 2 - victory
        for (auto &wave : this->waves) {
            if (wave.getAlive() != 0) {
                if (wave.getY() < 0.0f) return 1;
                else return 0;
            }
        }
        return 2;
    }

    void Squadron::analyze(PiggyBank &piggyBank) {
        piggyBank.resetRow();
        for (auto &wave : this->waves) {
            piggyBank.refreshRow(wave.getAlive(), wave.getType());
            piggyBank.nextRow();
        }
    }

    int Squadron::killClosest(float x, float y) {
        for (auto &wave : this->waves) {
            switch (Bullet::checkYCollision(y, wave.getY())) {
                case -1:
                    return -1;
                case 0:
                    if (wave.killClosest(x) == 0) return 0;
                    break;
            }
        }
        return 1;
    }

    Bullet Squadron::randomShot() {
        Bullet bullet(0.0f, 0.0f, 0);
        std::random_device r;
        std::default_random_engine d(r());
        for (auto &wave : this->waves) {
            bullet = wave.randomShot(d);
            if (bullet.getTarget() != 0)
                return bullet;
        }
        return bullet;
    }
}
