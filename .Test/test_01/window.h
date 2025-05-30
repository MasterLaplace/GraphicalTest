#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// initialise GLFW
int window_init(void);

// crée la fenêtre et renvoie le handle
GLFWwindow* window_create(int width, int height, const char* title);

// boucle principale, retourne 1 si tout s'est bien passé, 0 sinon
int window_main_loop(GLFWwindow* win);
