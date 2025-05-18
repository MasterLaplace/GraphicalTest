#include <GLFW/glfw3.h>
#include <cstdio>

extern "C" __attribute__((weak))
GLFWwindow *glfwCreateWindow(int, int, const char*, GLFWmonitor*, GLFWwindow*)
{
    std::puts("[MOCK] glfwCreateWindow called");
    return (GLFWwindow *)0xBEEF1234;
}
