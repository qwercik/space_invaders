#include <space_invaders/texture/Texture.hpp>
#include <lodepng/lodepng.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>

namespace space_invaders::texture {
    Texture::Texture(const std::string& filename) {
        this->ok = this->initialize(filename);
    }
    
    Texture::~Texture() {
        glDeleteTextures(1, &this->handle);
    }
    
    Texture::operator bool() const {
        return this->ok;
    }

    GLuint Texture::getHandle() const {
        return this->handle;
    }

    bool Texture::initialize(const std::string& filename) {
        glGenTextures(1, &this->handle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->handle);

        unsigned width, height;
        std::vector<unsigned char> image;
        unsigned returnCode = lodepng::decode(image, width, height, filename);
        if (returnCode != 0) {
            return false;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<unsigned char*>(image.data()));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return true;
    }
}
