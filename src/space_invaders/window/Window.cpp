#include <space_invaders/window/Window.hpp>
#include <space_invaders/window/Cursor.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace space_invaders::window {
    Window::Window(const std::string& title, unsigned width, unsigned height, bool resizable)
    {
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

        this->keyEventHandlers.push_back(handler);
        return *this;
    }
    
    Window& Window::onMouseButton(int button, int action, std::function<void()> callback) {
        MouseButtonEventHandler handler;
        handler.button = button;
        handler.action = action;
        handler.callback = callback;

        this->mouseButtonEventHandlers.push_back(handler);
        
        return *this;
    }
    
    Window& Window::onMouseMove(std::function<void(double y, double x)> callback) {
        this->mouseMoveCallback = callback;
        return *this;
    }

    Window& Window::onMouseEnter(std::function<void()> callback) {
        this->mouseEnterCallback = callback;
        return *this;
    }

    Window& Window::onMouseLeave(std::function<void()> callback) {
        this->mouseLeaveCallback = callback;
        return *this;
    }
   
    Window& Window::onScroll(std::function<void(double y, double x)> callback) {
        this->mouseScrollCallback = callback;
        return *this;
    }

    int Window::run() {
        if (!this->ok) {
            return EXIT_FAILURE;
        }

        if (this->initCallback) {
            this->initCallback();
        }

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (this->loopCallback) {
                this->loopCallback(); 
            }

            glfwSwapBuffers(this->window);
            glfwPollEvents();
        }
        
        if (this->exitCallback) {
            this->exitCallback();
        }

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

        this->cursor = std::make_unique<Cursor>(Window::CURSOR_FILE_PATH);
        if (!*this->cursor) {
            std::cout << "Could not read cursor file\n";
            return false;
        }
       
        glfwSetWindowUserPointer(this->window, this);
        glfwSetKeyCallback(this->window, Window::keyEventManager);
        glfwSetMouseButtonCallback(this->window, Window::mouseButtonEventManager);
        glfwSetScrollCallback(this->window, Window::scrollCallback);

        glfwSetCursor(this->window, this->cursor->getHandle());
        glfwSetCursorPosCallback(this->window, Window::cursorPositionCallback);
        glfwSetCursorEnterCallback(this->window, Window::cursorEnterCallback);

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
                if (handler.callback) {
                    handler.callback();
                }
            }
        }
    }
    
    void Window::mouseButtonEventManager(GLFWwindow *glfwWindow, int button, int action, int mods) {
        Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

        for (const auto handler : window->mouseButtonEventHandlers) {
            if (handler.button == button && handler.action == action) {
                if (handler.callback) {
                    handler.callback();
                }
            }
        }
    }

    void Window::cursorPositionCallback(GLFWwindow *glfwWindow, double x, double y) {
        Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    
        if (window->mouseMoveCallback) {
            window->mouseMoveCallback(y, x);
        }
    }
    
    void Window::cursorEnterCallback(GLFWwindow *glfwWindow, int entered) {
        Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
       
        if (entered) {
            if (window->mouseEnterCallback) {
                window->mouseEnterCallback();
            }
        } else {
            if (window->mouseLeaveCallback) {
                window->mouseLeaveCallback();
            }
        }
    }

    void Window::scrollCallback(GLFWwindow *glfwWindow, double x, double y) {
        Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

        if (window->mouseScrollCallback) {
            window->mouseScrollCallback(y, x);
        }
    }
}
