#include <space_invaders/window/Cursor.hpp>
#include <lodepng/lodepng.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

namespace space_invaders::window {
    Cursor::Cursor(const std::string& filename) {
        this->ok = this->initialize(filename);
    }

    Cursor::~Cursor() {
        if (this->cursor != nullptr) {
            glfwDestroyCursor(this->cursor);
        }
    }
    
    Cursor::operator bool() const {
        return this->ok;
    }
    
    GLFWcursor* Cursor::getHandle() {
        return this->cursor;
    }
    
    bool Cursor::initialize(const std::string& filename) {
        unsigned width, height;

        unsigned returnCode = lodepng::decode(imageData, width, height, filename);
        if (returnCode != 0 ) {
            std::cerr << "Could not read file " << filename << '\n';
            return false;
        }

        this->image.width = width;
        this->image.height = height;
        this->image.pixels = imageData.data();
        this->cursor = glfwCreateCursor(&this->image, 0, 0);

        return this->cursor != nullptr;
    }
}
