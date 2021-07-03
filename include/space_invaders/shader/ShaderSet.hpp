#pragma once

#include <space_invaders/shader/Shader.hpp>
#include <queue>
#include <string>
#include <optional>

namespace space_invaders::shader {
    class ShaderSet {
    public:
        ShaderSet();
        ~ShaderSet();

        ShaderSet& attach(const Shader& shader);
        void link();

        std::optional<std::string> getLog();

        GLuint uniform(const std::string& variable) const;
        GLuint attribute(const std::string& variable) const;

    private:
        GLuint handle;
        std::queue<GLuint> attachedShaders;
    };
}
