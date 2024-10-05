#include "Shader5.h"

static GLuint timeParam;               //parameters for sending to vertex shader


static GLuint p1x;
static GLuint p1y;
static GLuint p1z;

Shader5::Shader5(Point position)
: Model(position), shader()
{
    // The effective radius of this object for collision
    // detection purposes.
    _radius = 0.0;
}

Shader5::~Shader5()
{
    glDeleteShader(shader.vertexShaderObject);
    glDeleteShader(shader.fragmentShaderObject);
    glDeleteProgram(shader.programObject);
}

void Shader5::init()
{   
    printf("Shader5 init()\n");
    
    const char *version;
    GLchar *VertexShaderSource = 0;
    GLchar *FragmentShaderSource = 0;
    int loadstatus = 0;
    
    version = (const char *) glGetString(GL_VERSION);
    if (version[0] != '2' || version[1] != '.') {
        printf("This program requires OpenGL 2.x, found %s\n", version);
        
        // On Mac, the version fails but the functionality is still supported
#ifndef __APPLE__
        exit(1);
#endif
    }
    readShaderSource("prob4.vert", &VertexShaderSource, shader);
    readShaderSource("prob4.frag", &FragmentShaderSource, shader);
    loadstatus = installShaders(VertexShaderSource, FragmentShaderSource, shader);
    
    printf("Load status for Shader5 shaders: %d\n", loadstatus);
    
    timeParam = glGetUniformLocation ( shader.programObject, "time" );
    
    
    p1x = glGetAttribLocation ( shader.programObject, "p1x" );
    p1y = glGetAttribLocation ( shader.programObject, "p1y" );
    p1z = glGetAttribLocation ( shader.programObject, "p1z" );
}

void Shader5::update(int elapsedTime, int deltaTime)
{
    Model::update(elapsedTime, deltaTime);   
    
}

void Shader5::draw()
{
    glDisable(GL_CULL_FACE);
    glUseProgram(shader.programObject);
    float t = glutGet ( GLUT_ELAPSED_TIME );
    while ( t > 10000 ) t -= 10000;
    glUniform1f( timeParam, t );
    
    
    
    
    glBegin(GL_TRIANGLES);
    glVertexAttrib1f(p1x, 20.0);
    glVertexAttrib1f(p1y, 10.0);
    glVertexAttrib1f(p1z, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glVertexAttrib1f(p1x, 0.0);
    glVertexAttrib1f(p1y, 30.0);
    glVertexAttrib1f(p1z, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glVertexAttrib1f(p1x, -5.0);
    glVertexAttrib1f(p1y, -5.0);
    glVertexAttrib1f(p1z, 0.0);
    glVertex3f(-10.0, 0.0, 0.0);
    glEnd();
     
    glUseProgram(0);
    glEnable(GL_CULL_FACE);
} 

void Shader5::bump()
{ 
    // Add code to respond to being bumped by the 
    // view object (see Sphere1 for example)
}
