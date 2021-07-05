#include <space_invaders/window/Cursor.hpp>
#include <lodepng/lodepng.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

namespace space_invaders::window {
    Cursor::Cursor(const std::string& filename, Cursor::Hotspot hotspot) {
        this->ok = this->initialize(filename, hotspot);
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
    
    bool Cursor::initialize(const std::string& filename, Cursor::Hotspot hotspot) {
        unsigned width, height;

        unsigned returnCode = lodepng::decode(imageData, width, height, filename);
        if (returnCode != 0 ) {
            std::cerr << "Could not read file " << filename << '\n';
            return false;
        }

        this->image.width = width;
        this->image.height = height;
        this->image.pixels = imageData.data();
        int hotspotX = hotspot == Hotspot::CENTER ? width / 2 : 0;
        int hotspotY = hotspot == Hotspot::CENTER ? height / 2 : 0;
        this->cursor = glfwCreateCursor(&this->image, hotspotX, hotspotY);

        return this->cursor != nullptr;
    }
}
