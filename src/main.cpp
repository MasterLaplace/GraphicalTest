#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "window.hpp"

int main()
{
    if (!glfwInit())
        return std::cerr << "Failed to init GLFW\n", 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = createWindow();
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return 2;
    }

    std::cout << "Window created: " << window << "\n";

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "GLEW error: " << glewGetErrorString(err) << "\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 3;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
