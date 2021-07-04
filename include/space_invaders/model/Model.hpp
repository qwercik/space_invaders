#pragma once

#include <GL/glew.h>
#include <space_invaders/shader/ShaderSet.hpp>

namespace space_invaders::model {
    class Model {
    public:
        virtual void draw(const shader::ShaderSet& shaders) const = 0;
        void drawOutline(const shader::ShaderSet& shaders);
    };
}
