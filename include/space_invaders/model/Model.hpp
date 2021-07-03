#pragma once

#include <GL/glew.h>

namespace space_invaders::model {
    class Model {
    public:
        virtual void draw() const = 0;
        void drawOutline();
    };
}
