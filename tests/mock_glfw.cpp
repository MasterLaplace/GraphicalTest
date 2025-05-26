#include <GLFW/glfw3.h>
#include <cstdio>

#ifdef _WIN32
// Approche ALTERNATENAME : rediriger les vraies fonctions vers nos mocks
#pragma comment(linker, "/ALTERNATENAME:glfwInit=mock_glfwInit")
#pragma comment(linker, "/ALTERNATENAME:glfwCreateWindow=mock_glfwCreateWindow")
#pragma comment(linker, "/ALTERNATENAME:glfwTerminate=mock_glfwTerminate")
#pragma comment(linker, "/ALTERNATENAME:glfwMakeContextCurrent=mock_glfwMakeContextCurrent")
#pragma comment(linker, "/ALTERNATENAME:glfwDestroyWindow=mock_glfwDestroyWindow")
#pragma comment(linker, "/ALTERNATENAME:glfwSwapBuffers=mock_glfwSwapBuffers")
#pragma comment(linker, "/ALTERNATENAME:glfwPollEvents=mock_glfwPollEvents")
#pragma comment(linker, "/ALTERNATENAME:glfwWindowShouldClose=mock_glfwWindowShouldClose")
#pragma comment(linker, "/ALTERNATENAME:glfwWindowHint=mock_glfwWindowHint")
#pragma comment(linker, "/ALTERNATENAME:glfwSwapInterval=mock_glfwSwapInterval")
#endif

extern "C" {

// Fonctions avec préfixe mock_ pour ALTERNATENAME
int mock_glfwInit()
{
    std::puts("[MOCK] glfwInit called");
    return 1;
}

GLFWwindow *mock_glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    std::puts("[MOCK] glfwCreateWindow called");
    return (GLFWwindow*)0xDEADBEEF;
}

void mock_glfwTerminate() {
    std::puts("[MOCK] glfwTerminate called");
}

void mock_glfwMakeContextCurrent(GLFWwindow* window)
{
    std::puts("[MOCK] glfwMakeContextCurrent called");
}

void mock_glfwDestroyWindow(GLFWwindow* window)
{
    std::puts("[MOCK] glfwDestroyWindow called");
}

void mock_glfwSwapBuffers(GLFWwindow* window)
{
    std::puts("[MOCK] glfwSwapBuffers called");
}

void mock_glfwPollEvents()
{
    std::puts("[MOCK] glfwPollEvents called");
}

int mock_glfwWindowShouldClose(GLFWwindow* window)
{
    std::puts("[MOCK] glfwWindowShouldClose called");
    return 1;
}

void mock_glfwWindowHint(int hint, int value)
{
    std::puts("[MOCK] glfwWindowHint called");
}

void mock_glfwSwapInterval(int interval)
{
    std::puts("[MOCK] glfwSwapInterval called");
}

}
