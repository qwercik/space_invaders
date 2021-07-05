#pragma once

#include <string>
#include <vector>
#include <GLFW/glfw3.h>

namespace space_invaders::window {
    class Cursor {
    public:
        enum class Hotspot {
            TOP_LEFT,
            CENTER
        };

        Cursor(const std::string& filename, Hotspot hotspot);
        ~Cursor();
        operator bool() const;

        GLFWcursor *getHandle();

    private:
        bool initialize(const std::string& filename, Hotspot hotspot);

        std::vector<unsigned char> imageData;
        GLFWimage image;
        GLFWcursor *cursor;
        bool ok;
    };
}
