#pragma once

#include <optional>
#include <string>
#include <GL/glew.h>


namespace space_invaders::shader {
    class Shader {
    public:
        Shader(GLenum type, const std::string& filename);
        ~Shader();

        GLuint getHandle() const; 
        std::string getLog();

    private:
        GLuint handle;
    };
}
