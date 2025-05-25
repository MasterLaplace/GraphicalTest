#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "window.hpp"

int main()
{
    if (!initGraphics())
        return std::cerr << "Failed to init GLFW\n", 1;

    setWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    setWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    setWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = createWindow();
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        terminateGraphics();
        return 2;
    }

    std::cout << "Window created: " << window << "\n";

    makeContextCurrent(window);
    setSwapInterval(1);

    int err = initOpenGL();
    if (err != GLEW_OK)
    {
        std::cerr << "GLEW error: " << getGLEWErrorString(err) << "\n";
        destroyWindow(window);
        terminateGraphics();
        return 3;
    }

    std::cout << "OpenGL version: " << getOpenGLVersion() << "\n";

    while (!windowShouldClose(window))
    {
        pollEvents();
        clearScreen(GL_COLOR_BUFFER_BIT);
        swapBuffers(window);
    }

    destroyWindow(window);
    terminateGraphics();
    return 0;
}
