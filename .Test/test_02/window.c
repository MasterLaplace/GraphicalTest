#include "window.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

struct Window {
    GLFWwindow* glfw_window;
    int width;
    int height;
    const char* title;
};

int window_init(void) {
    printf("[WINDOW] Initializing GLFW...\n");
    return glfwInit();
}

void window_terminate(void) {
    printf("[WINDOW] Terminating GLFW...\n");
    glfwTerminate();
}

Window* window_create(int width, int height, const char* title) {
    printf("[WINDOW] Creating window %dx%d '%s'\n", width, height, title);

    Window* window = malloc(sizeof(Window));
    if (!window) {
        return NULL;
    }

    window->width = width;
    window->height = height;
    window->title = title;

    // Appel à GLFW - sera remplacé par le mock dans les tests
    window->glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window->glfw_window) {
        free(window);
        return NULL;
    }

    return window;
}

void window_destroy(Window* window) {
    if (window) {
        printf("[WINDOW] Destroying window\n");
        if (window->glfw_window) {
            glfwDestroyWindow(window->glfw_window);
        }
        free(window);
    }
}

int window_should_close(Window* window) {
    if (!window || !window->glfw_window) {
        return 1;
    }
    return glfwWindowShouldClose(window->glfw_window);
}

void window_swap_buffers(Window* window) {
    if (window && window->glfw_window) {
        glfwSwapBuffers(window->glfw_window);
    }
}

void window_poll_events(void) {
    glfwPollEvents();
}
