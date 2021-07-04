#pragma once

#include <string>
#include <GL/glew.h>

namespace space_invaders::texture {
    class Texture {
    public:
        Texture(const std::string& filename);
        ~Texture();

        operator bool() const;
        GLuint getHandle() const;

    private:
        bool initialize(const std::string& filename);

        GLuint handle;
        bool ok = false;
    };
}

