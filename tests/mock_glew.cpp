#include <GL/glew.h>
#include <iostream>

int fake_glewInit_result = GLEW_OK;

extern "C" {

__attribute__((weak))
GLenum glewInit()
{
    std::cout << "[MOCK] glewInit() called\n";
    return fake_glewInit_result;
}

__attribute__((weak))
const GLubyte *glGetString(GLenum name)
{
    std::cout << "[MOCK] glGetString() called\n";
    if (name == GL_VERSION)
        return (const GLubyte*)"Mock OpenGL 4.2 GLEW";
    return nullptr;
}

}
