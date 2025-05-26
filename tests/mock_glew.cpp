#include <GL/glew.h>
#include <iostream>

// Forcer l'inclusion des symboles
#ifdef _WIN32
#pragma comment(linker, "/INCLUDE:glewInit")
#pragma comment(linker, "/INCLUDE:glGetString")
#pragma comment(linker, "/INCLUDE:glewGetErrorString")
#pragma comment(linker, "/INCLUDE:glClear")
#pragma comment(linker, "/INCLUDE:glewExperimental")
#endif

int fake_glewInit_result = GLEW_OK;

// Variable globale pour GLEW
__attribute__((visibility("default")))
GLboolean glewExperimental = GL_TRUE;

extern "C" {

__attribute__((visibility("default")))
GLenum glewInit()
{
    std::cout << "[MOCK] glewInit() called\n";
    return fake_glewInit_result;
}

__attribute__((visibility("default")))
const GLubyte *glGetString(GLenum name)
{
    std::cout << "[MOCK] glGetString() called\n";
    if (name == GL_VERSION)
        return (const GLubyte*)"Mock OpenGL 4.5 GLEW";
    return nullptr;
}

__attribute__((visibility("default")))
const GLubyte* glewGetErrorString(GLenum err)
{
    return (const GLubyte*)"[MOCK] GLEW error string";
}

__attribute__((visibility("default")))
void glClear(GLbitfield mask)
{
    std::cout << "[MOCK] glClear(" << mask << ")\n";
}

}
