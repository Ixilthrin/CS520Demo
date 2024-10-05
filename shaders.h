#ifndef __SHADERS_H__
#define __SHADERS_H__

#include "main.h"

class ShaderObjects
{
public:
    ShaderObjects() 
    : programObject(0), 
      vertexShaderObject(0), 
      fragmentShaderObject(0)
    {}
    ~ShaderObjects();
    GLuint programObject;
    GLuint vertexShaderObject;
    GLuint fragmentShaderObject;
};

int readShaderSource(char *fileName, GLchar **shaderCode, ShaderObjects &shader);
int installShaders(const GLchar *vertex, const GLchar *fragment, ShaderObjects &shader);

#endif
