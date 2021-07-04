#include <space_invaders/shader/Shader.hpp>
#include <space_invaders/shader/ShaderSet.hpp>
#include <space_invaders/utils.hpp>
#include <GL/glew.h>

namespace space_invaders::shader {
    ShaderSet::ShaderSet() {
        this->handle = glCreateProgram();
    }

    ShaderSet::~ShaderSet() {
        while (!this->attachedShaders.empty()) {
            auto shaderHandle = this->attachedShaders.front();
            glDetachShader(this->handle, shaderHandle);
            this->attachedShaders.pop();
        }

        glDeleteProgram(this->handle);
    }

    ShaderSet& ShaderSet::attach(const Shader& shader) {
        auto shaderHandle = shader.getHandle();
        this->attachedShaders.push(shaderHandle);
        glAttachShader(this->handle, shaderHandle);
        return *this;
    }

    void ShaderSet::link() {
        glLinkProgram(this->handle);
    }
    
    void ShaderSet::use() {
        glUseProgram(this->handle);
    }
   
    std::string ShaderSet::getLog() {
        return utils::obtainOpenGlLog(this->handle, glGetProgramiv, glGetProgramInfoLog);
    }

    GLuint ShaderSet::uniform(const std::string& variable) const {
        return glGetUniformLocation(this->handle, variable.c_str());
    }

    GLuint ShaderSet::attribute(const std::string& variable) const {
        return glGetAttribLocation(this->handle, variable.c_str());
    }
}
