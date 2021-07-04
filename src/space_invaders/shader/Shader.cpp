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

        std::string log = this->getLog();
        if (!log.empty()) {
            std::cout << log << '\n';
        }
    }

    Shader::~Shader() {
        glDeleteShader(this->handle);
    }
    
    GLuint Shader::getHandle() const {
        return this->handle;
    }

    std::string Shader::getLog() {
        return utils::obtainOpenGlLog(this->handle, glGetShaderiv, glGetShaderInfoLog);
    }
}
