#include "window.hpp"

GLFWwindow *createWindow()
{
    return glfwCreateWindow(800, 600, "Hello", nullptr, nullptr);
}
