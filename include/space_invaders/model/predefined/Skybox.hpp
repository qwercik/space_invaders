#pragma once

#include <space_invaders/model/HierarchicalModel.hpp>
#include <space_invaders/model/TexturedModel.hpp>
#include <array>

namespace space_invaders::models::predefined {
    class Skybox : public HierarchicalModel {
    public:
        SkyBox();

    private:
        enum class WallIdentifier {

        }

        void drawingCallback(const HierarchicalModel& model);

        std::array<TexturedModel, 6> walls;
    };
}

