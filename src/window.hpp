#pragma once
#include <GLFW/glfw3.h>
#include <GL/glew.h>

// GLFW wrappers
bool initGraphics();
void terminateGraphics();
GLFWwindow *createWindow();
void destroyWindow(GLFWwindow* window);
void makeContextCurrent(GLFWwindow* window);
void swapBuffers(GLFWwindow* window);
void pollEvents();
int windowShouldClose(GLFWwindow* window);
void setWindowHint(int hint, int value);
void setSwapInterval(int interval);

// GLEW wrappers
int initOpenGL();
const char* getOpenGLVersion();
const char* getGLEWErrorString(unsigned int error);
void clearScreen(unsigned int mask);
