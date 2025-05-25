#include "window.hpp"
#include <iostream>

// GLFW wrappers
bool initGraphics() {
    return glfwInit() == GLFW_TRUE;
}

void terminateGraphics() {
    glfwTerminate();
}

GLFWwindow *createWindow() {
    return glfwCreateWindow(800, 600, "Hello", nullptr, nullptr);
}

void destroyWindow(GLFWwindow* window) {
    glfwDestroyWindow(window);
}

void makeContextCurrent(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
}

void swapBuffers(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void pollEvents() {
    glfwPollEvents();
}

int windowShouldClose(GLFWwindow* window) {
    return glfwWindowShouldClose(window);
}

void setWindowHint(int hint, int value) {
    glfwWindowHint(hint, value);
}

void setSwapInterval(int interval) {
    glfwSwapInterval(interval);
}

// GLEW wrappers
int initOpenGL() {
    glewExperimental = GL_TRUE;
    return glewInit();
}

const char* getOpenGLVersion() {
    return (const char*)glGetString(GL_VERSION);
}

const char* getGLEWErrorString(unsigned int error) {
    return (const char*)glewGetErrorString(error);
}

void clearScreen(unsigned int mask) {
    glClear(mask);
}
