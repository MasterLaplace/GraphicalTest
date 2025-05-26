#include <stdio.h>
#include <GLFW/glfw3.h>

#ifdef _MSC_VER
// Sous MSVC, aliaser glfwInit → __wrap_glfwInit
#pragma comment(linker, "/alternatename:glfwInit=__wrap_glfwInit")
// Alias pour glfwCreateWindow
#pragma comment(linker, "/alternatename:glfwCreateWindow=__wrap_glfwCreateWindow")
#endif

// Prototype des vraies fonctions
int __real_glfwInit(void);
GLFWwindow* __real_glfwCreateWindow(int, int, const char*, GLFWmonitor*, GLFWwindow*);

int __wrap_glfwInit(void) {
    printf("[wrap-mock] glfwInit() appelé → échec\n");
    return 0;
}

GLFWwindow* __wrap_glfwCreateWindow(int w, int h, const char* t, GLFWmonitor* m, GLFWwindow* s) {
    printf("[wrap-mock] glfwCreateWindow(%dx%d, \"%s\") appelé → retourne NULL\n", w, h, t);
    return NULL
}
