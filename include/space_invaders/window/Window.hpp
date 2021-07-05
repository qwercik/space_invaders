#pragma once

#include <string>
#include <functional>
#include <list>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <space_invaders/window/Cursor.hpp>

namespace space_invaders::window {
    class Window {
    public:
        Window(const std::string& title, unsigned width, unsigned height, bool resizable);

        Window& onInit(std::function<void()> initCallback);
        Window& onLoop(std::function<void()> loopCallback);
        Window& onExit(std::function<void()> exitCallback);
        
        Window& onKey(int key, int action, std::function<void()> callback);
        Window& onMouseMove(std::function<void(double y, double x)> callback);
        Window& onMouseEnter(std::function<void()> callback);
        Window& onMouseLeave(std::function<void()> callback);
        Window& onMouseButton(int button, int action, std::function<void()> callback);
        Window& onScroll(std::function<void(double y, double x)> callback);
        
        int run();

    private:
        const std::string CURSOR_FILE_PATH = "../textures/cursor.png";
        
        struct KeyEventHandler {
            int key;
            int action;
            std::function<void()> callback;
        };

        struct MouseButtonEventHandler {
            int button;
            int action;
            std::function<void()> callback;
        };


        bool initialize(const std::string& title, unsigned width, unsigned height, bool resizable);
        static void keyEventManager(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods);
        static void mouseButtonEventManager(GLFWwindow *glfwWindow, int button, int action, int mods);
        static void cursorPositionCallback(GLFWwindow *glfwWindow, double x, double y);
        static void cursorEnterCallback(GLFWwindow *glfwWindow, int entered);
        static void scrollCallback(GLFWwindow *glfwWindow, double xoffset, double yoffset);


        GLFWwindow *window;
        std::unique_ptr<Cursor> cursor;
        bool ok = true;

        std::function<void()> initCallback;
        std::function<void()> loopCallback;
        std::function<void()> exitCallback;

        std::list<KeyEventHandler> keyEventHandlers;
        std::list<MouseButtonEventHandler> mouseButtonEventHandlers;
        
        std::function<void(double y, double x)> mouseMoveCallback;
        std::function<void()> mouseEnterCallback;
        std::function<void()> mouseLeaveCallback;
        std::function<void(double y, double x)> mouseScrollCallback;
    };
}
