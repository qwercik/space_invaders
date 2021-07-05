#pragma once

#include <string>
#include <vector>
#include <GLFW/glfw3.h>

namespace space_invaders::window {
    class Cursor {
    public:
        Cursor(const std::string& filename);
        ~Cursor();
        operator bool() const;

        GLFWcursor *getHandle();

    private:
        bool initialize(const std::string& filename);

        std::vector<unsigned char> imageData;
        GLFWimage image;
        GLFWcursor *cursor;
        bool ok;
    };
}
