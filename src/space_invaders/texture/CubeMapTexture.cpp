#include <space_invaders/texture/CubeMapTexture.hpp>
#include <lodepng/lodepng.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>

namespace space_invaders::texture {
    CubeMapTexture::CubeMapTexture(const std::array<std::string, 6>& filenames) {
        this->ok = this->initialize(filenames);
    }
    
    CubeMapTexture::~CubeMapTexture() {
        glDeleteTextures(1, &this->handle);
    }
    
    CubeMapTexture::operator bool() const {
        return this->ok;
    }

    GLuint CubeMapTexture::getHandle() const {
        return this->handle;
    }

    bool CubeMapTexture::initialize(const std::array<std::string, 6>& filenames) {
        glGenTextures(1, &this->handle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->handle);

        for (auto i = 0; i < filenames.size(); i++) {
            unsigned width, height;
            std::vector<unsigned char> image;
            unsigned returnCode = lodepng::decode(image, width, height, filenames[i]);
            if (returnCode != 0) {
                return false;
            }

            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 4,
                width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                reinterpret_cast<unsigned char*>(image.data())
            );
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return true;
    }
}
