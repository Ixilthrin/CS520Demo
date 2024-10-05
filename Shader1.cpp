#include "Shader1.h"
#include "Scene.h"
#include "Program.h"

Shader1::Shader1(Point position)
: Model(position), shader()
{
    // The effective radius of this object for collision
    // detection purposes.
    _radius = 0.0;
    
    _rotationalSpeedRoll = .002;
}

Shader1::~Shader1()
{
    glDeleteShader(shader.vertexShaderObject);
    glDeleteShader(shader.fragmentShaderObject);
    glDeleteProgram(shader.programObject);
}

void Shader1::init()
{
    
    const char *version;
    GLchar *VertexShaderSource, *FragmentShaderSource;
    int loadstatus = 0;
    
    version = (const char *) glGetString(GL_VERSION);
    if (version[0] != '2' || version[1] != '.') {
        printf("This program requires OpenGL 2.x, found %s\n", version);
        
        // On Mac, the version fails but the functionality is still supported
#ifndef __APPLE__
        exit(1);
#endif
    }
    readShaderSource("tests.vert", &VertexShaderSource, shader);
    readShaderSource("tests.frag", &FragmentShaderSource, shader);
    loadstatus = installShaders(VertexShaderSource, FragmentShaderSource, shader);
    
    printf("Load status for shaders: %d\n", loadstatus);
}

void Shader1::update(int elapsedTime, int deltaTime)
{
    Model::update(elapsedTime, deltaTime);
}

void Shader1::draw()
{
    if (_scene->getProgram()->shadowsEnabled())
        return;
    glUseProgram(shader.programObject);
    //glColor3f ( 1, 0, 0 );          //red, this will have no effect if shader is loaded
    glutWireSphere(300.0, 50.0, 50.0);
    glUseProgram(0);
} 

void Shader1::bump()
{ 
    // Add code to respond to being bumped by the 
    // view object (see Sphere1 for example)
}
