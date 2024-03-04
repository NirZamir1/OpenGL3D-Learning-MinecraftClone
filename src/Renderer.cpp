#include "Renderer.h"
#include <iostream>

void GLClearErrorCode()
{
    while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
    GLenum error = glGetError();
    bool ret = true;
    while (error != GL_NO_ERROR)
    {
        ret = false;
        std::cout << "[OPENGL ERROR] (" << error << ") On Line: " << line << " | " << function << "| in: " << file << std::endl;
        error = glGetError();
    }
    return ret;
}