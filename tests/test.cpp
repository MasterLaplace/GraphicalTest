#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "window.hpp"

extern int fake_glewInit_result;

int main()
{
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return 1;
    }

    GLFWwindow *window = createWindow();
    if (!window) {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        return 2;
    }

    std::cout << "Test: window pointer = " << window << "\n";


    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Mocked GLEW error: " << glewGetErrorString(err) << "\n";
    } else {
        std::cout << "GLEW initialized: " << glGetString(GL_VERSION) << "\n";
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
