#pragma once

#include <string>
#include <array>
#include <GL/glew.h>

namespace space_invaders::texture {
    class CubeMapTexture {
    public:
        CubeMapTexture(const std::array<std::string, 6>& filenames);
        ~CubeMapTexture();
        operator bool() const;

        GLuint getHandle() const;

    private:
        bool initialize(const std::array<std::string, 6>& filenames);

        GLuint handle;
        bool ok;
    };
}
