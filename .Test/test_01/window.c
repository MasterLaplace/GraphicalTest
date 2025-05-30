// window.c
#include "window.h"
#include <stdlib.h>
#include <stdio.h>

int window_init(void)
{
    return glfwInit() ? 1 : 0;
}

GLFWwindow* window_create(int width, int height, const char* title)
{
    GLFWwindow* win = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!win)
        fprintf(stderr, "Erreur : impossible de créer la fenêtre\n");

    return win;
}

int window_main_loop(GLFWwindow* win)
{
    if (!win) return 0;

    glfwMakeContextCurrent(win);
    while (!glfwWindowShouldClose(win))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    return 1;
}
