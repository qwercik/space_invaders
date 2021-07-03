#include <space_invaders/shader/Shader.hpp>
#include <space_invaders/utils.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>

namespace space_invaders::shader {
    Shader::Shader(GLenum type, const std::string& filename) {
        this->handle = glCreateShader(type);
        std::string content = utils::loadWholeFile(filename);

        auto pointer = content.c_str();
        glShaderSource(this->handle, 1, &pointer, NULL);
        glCompileShader(this->handle);

        auto log = this->getLog();
        if (log) {
            std::cout << log.value() << '\n';
        }
    }

    Shader::~Shader() {
        glDeleteShader(this->handle);
    }
    
    GLuint Shader::getHandle() const {
        return this->handle;
    }

    std::optional<std::string> Shader::getLog() {
        return utils::obtainOpenGlLog(this->handle, glGetShaderiv, glGetShaderInfoLog);
    }
}
