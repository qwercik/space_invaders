#include <space_invaders/utils.hpp>
#include <optional>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>

namespace space_invaders::utils {
    std::string loadWholeFile(const std::string& filename) {
        std::ifstream file(filename);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    std::string obtainOpenGlLog(
        GLuint handle,
        std::function<void(GLuint, GLenum, GLint*)> parameterFunction,
        std::function<void(GLuint, GLsizei, GLsizei*, GLchar*)> logFunction
    ) {
        GLint logLength = 0;
        GLint charactersWritten = 0;

        parameterFunction(handle, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            std::vector<char> buffer(logLength);
            logFunction(handle, logLength, &charactersWritten, buffer.data());
            return std::string(buffer.begin(), buffer.end());
        }

        return "";
    }
}
