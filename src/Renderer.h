#pragma once
#include <GL/glew.h>
#define ASSERT(x) if(!(x)) __debugbreak();;
#define GLCall(x) GLClearErrorCode();\
                  x;\
                  ASSERT(GLLogCall(#x,__FILE__,__LINE__));
void GLClearErrorCode();
bool GLLogCall(const char* function, const char* file, int line);
