#pragma once

#include <string>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace space_invaders {
    class Window {
    public:
        Window(const std::string& title, unsigned width, unsigned height, bool resizable);

        Window& onInit(std::function<void()> initCallback);
        Window& onLoop(std::function<void()> loopCallback);
        Window& onExit(std::function<void()> loopCallback);
        
        int run();

    private:
        bool initialize(const std::string& title, unsigned width, unsigned height, bool resizable);

        GLFWwindow *window;
        bool ok = true;

        std::function<void()> initCallback;
        std::function<void()> loopCallback;
        std::function<void()> exitCallback;
    };
}
