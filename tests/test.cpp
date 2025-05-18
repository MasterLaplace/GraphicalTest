#include <GLFW/glfw3.h>
#include <iostream>
#include "window.hpp"

int main()
{
    GLFWwindow *window = createWindow();
    std::cout << "Test: window pointer = " << window << "\n";
    return 0;
}
