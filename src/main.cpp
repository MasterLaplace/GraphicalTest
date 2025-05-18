#include <GLFW/glfw3.h>
#include <iostream>
#include "window.hpp"

int main()
{
    if (!glfwInit())
        return std::cerr << "Failed to init GLFW\n", 1;

    GLFWwindow *window = createWindow();
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return 2;
    }

    std::cout << "Window created: " << window << "\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
