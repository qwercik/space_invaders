#pragma once

#include <space_invaders/model/BasicModel.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <vector>
#include <string>

namespace space_invaders::model {
    class ColoredModel : public BasicModel {
    public:
        ColoredModel(const std::string& filename);
        virtual void draw(const shader::ShaderSet& shaders) const override;

    protected:
        ColoredModel() = default;
        bool initialize(const std::string& filename);

        std::vector<float> colors;
    };
}
