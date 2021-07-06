#include <space_invaders/game/Invader.hpp>
#include <space_invaders/model/TexturedModel.hpp>

namespace space_invaders::game {
    Invader::Invader(int type, int x) : alive{true}, type{type}, x{x} {}
}
