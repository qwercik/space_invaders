#include <space_invaders/game/Invader.hpp>

namespace space_invaders::game {
    Invader::Invader(int type, int x) : alive{true}, type{type}, x{x}, cooldown{0.0f} {}
}
