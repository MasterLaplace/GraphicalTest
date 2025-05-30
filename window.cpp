#include "window.h"

// Inclusion conditionnelle selon qu'on utilise les mocks ou pas
#ifdef USE_MOCK_GLFW
    extern "C" {
        #include "mock_glfw.h"
    }
#else
    #include <GLFW/glfw3.h>
#endif

#include <iostream>

// Implémentation des méthodes de classe
bool Window::init() {
    std::cout << "[WINDOW] Initializing GLFW...\n";
    return glfwInit() == GLFW_TRUE;
}

void Window::terminate() {
    std::cout << "[WINDOW] Terminating GLFW...\n";
    glfwTerminate();
}

Window::Window(int width, int height, const char* title)
    : m_width(width), m_height(height), m_title(title), m_glfwWindow(nullptr) {
    std::cout << "[WINDOW] Creating window " << width << "x" << height << " '" << title << "'\n";
    m_glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

Window::~Window() {
    if (m_glfwWindow) {
        std::cout << "[WINDOW] Destroying window\n";
        glfwDestroyWindow(m_glfwWindow);
        m_glfwWindow = nullptr;
    }
}

bool Window::shouldClose() const {
    if (!m_glfwWindow) {
        return true;
    }
    return glfwWindowShouldClose(m_glfwWindow) == GLFW_TRUE;
}

void Window::swapBuffers() const {
    if (m_glfwWindow) {
        glfwSwapBuffers(m_glfwWindow);
    }
}

void Window::pollEvents() {
    glfwPollEvents();
}

// Fonctions de compatibilité pour les tests C
// Ces fonctions agiront comme adaptateurs vers la classe C++
extern "C" {
    int window_init(void) {
        return Window::init() ? GLFW_TRUE : GLFW_FALSE;
    }

    void window_terminate(void) {
        Window::terminate();
    }

    Window* window_create(int width, int height, const char* title) {
        Window* window = new Window(width, height, title);
        if (!window->getGLFWwindow()) {
            delete window;
            return nullptr;
        }
        return window;
    }

    void window_destroy(Window* window) {
        if (window) {
            delete window;
        }
    }

    int window_should_close(Window* window) {
        if (!window) {
            return GLFW_TRUE;
        }
        return window->shouldClose() ? GLFW_TRUE : GLFW_FALSE;
    }

    void window_swap_buffers(Window* window) {
        if (window) {
            window->swapBuffers();
        }
    }

    void window_poll_events(void) {
        Window::pollEvents();
    }
}
