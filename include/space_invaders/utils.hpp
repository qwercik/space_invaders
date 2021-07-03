#pragma once

#include <string>
#include <functional>
#include <GL/glew.h>

namespace space_invaders::utils {
    std::string loadWholeFile(const std::string& filename);

    std::optional<std::string> obtainOpenGlLog(
        GLuint handle,
        std::function<void(GLuint, GLenum, GLint*)> parameterFunction,
        std::function<void(GLuint, GLsizei, GLsizei*, GLchar*)> logFunction
    );
}
