#pragma once

#include <string>
#include <functional>
#include <list>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace space_invaders::window {
    class Window {
    public:
        Window(const std::string& title, unsigned width, unsigned height, bool resizable);

        Window& onInit(std::function<void()> initCallback);
        Window& onLoop(std::function<void()> loopCallback);
        Window& onExit(std::function<void()> exitCallback);
        
        Window& onKey(int key, int action, std::function<void()> callback);
        Window& onMouseMove(std::function<void(double y, double x)> callback);
        
        int run();

    private:
        struct KeyEventHandler {
            int key;
            int action;
            std::function<void()> callback;
        };

        bool initialize(const std::string& title, unsigned width, unsigned height, bool resizable);
        static void keyEventManager(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void cursorPositionCallback(GLFWwindow *window, double x, double y);


        GLFWwindow *window;
        bool ok = true;

        std::function<void()> initCallback;
        std::function<void()> loopCallback;
        std::function<void()> exitCallback;

        std::list<KeyEventHandler> keyEventHandlers;
        
        std::function<void(double y, double x)> mouseMoveCallback;
    };
}
