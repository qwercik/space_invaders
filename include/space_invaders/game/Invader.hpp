#pragma once

#include <space_invaders/model/TexturedModel.hpp>

namespace space_invaders::game {
    class Invader {
    public:
        Invader(int type, int x);

        bool alive;
        int type;
        int x;
        float cooldown;
    };
}
