#include <space_invaders/window/Window.hpp>
#include <iostream>
#include <string>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace space_invaders::window {
    Window::Window(const std::string& title, unsigned width, unsigned height, bool resizable) {
        this->ok = this->initialize(title, width, height, resizable);
    }

    Window& Window::onInit(std::function<void()> initCallback) {
        this->initCallback = initCallback;
        return *this;
    }

    Window& Window::onLoop(std::function<void()> loopCallback) {
        this->loopCallback = loopCallback;
        return *this;
    }
    
    Window& Window::onExit(std::function<void()> exitCallback) {
        this->exitCallback = exitCallback;
        return *this;
    }
    
    Window& Window::onKey(int key, int action, std::function<void()> callback) {
        KeyEventHandler handler;
        handler.key = key;
        handler.action = action;
        handler.callback = callback;

        keyEventHandlers.push_back(handler);
        return *this;
    }

    int Window::run() {
        if (!this->ok) {
            return EXIT_FAILURE;
        }

        this->initCallback();

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            this->loopCallback(); 

            glfwSwapBuffers(this->window);
            glfwPollEvents();
        }

        this->exitCallback();

        glfwDestroyWindow(this->window);
        glfwTerminate();
        
        return EXIT_SUCCESS;
    }
    
    bool Window::initialize(const std::string& title, unsigned width, unsigned height, bool resizable) {
        if (!glfwInit()) {
            std::cerr << "Could not initialize GLFW\n";
            return false;
        }

        glfwWindowHint(GLFW_RESIZABLE, resizable);
        glfwSetErrorCallback([](int error, const char *desc) {
            std::cerr << "[Error " << error << "]: " << desc << '\n';
        });

        this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!this->window) {
            std::cerr << "Could not initialize window\n";
            glfwTerminate();
            return false;
        }
       
        glfwSetWindowUserPointer(this->window, this);
        glfwSetKeyCallback(this->window, Window::keyEventManager);


        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        
        if (glewInit() != GLEW_OK) {
            std::cerr << "Could not initialize GLEW\n";
            return false;
        }
        
        if (!GLEW_VERSION_3_3) {
            std::cerr << "OpenGL 3.3 is required\n";
            return false;
        }
        
        return true;
    }
    
    void Window::keyEventManager(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods) {
        Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

        for (const auto handler : window->keyEventHandlers) {
            if (handler.key == key && handler.action == action) {
                handler.callback();
            }
        }
    }
}
