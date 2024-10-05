#include "Shader4.h"

static GLuint timeParam;               //parameters for sending to vertex shader
static GLuint velParam;                //parameters for sending to vertex shader
static GLuint positionParam;
Shader4::Shader4(Point position)
: Model(position), shader()
{
    // The effective radius of this object for collision
    // detection purposes.
    _radius = 0.0;
}

Shader4::~Shader4()
{
    glDeleteShader(shader.vertexShaderObject);
    glDeleteShader(shader.fragmentShaderObject);
    glDeleteProgram(shader.programObject);
}

void Shader4::init()
{   
    printf("Shader4 init()\n");
    
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
    readShaderSource("prob5.vert", &VertexShaderSource, shader);
    readShaderSource("prob5.frag", &FragmentShaderSource, shader);
    loadstatus = installShaders(VertexShaderSource, FragmentShaderSource, shader);
    
    printf("Load status for Shader4 shaders: %d\n", loadstatus);
    
    timeParam = glGetUniformLocation ( shader.programObject, "time" );
    velParam = glGetAttribLocation ( shader.programObject, "vel" );
    positionParam = glGetAttribLocation(shader.programObject, "position");
}

void Shader4::update(int elapsedTime, int deltaTime)
{
    Model::update(elapsedTime, deltaTime);   
    
}

void Shader4::draw()
{
    glDisable(GL_CULL_FACE);
    glUseProgram(shader.programObject);
    float t = glutGet ( GLUT_ELAPSED_TIME );
    while ( t > 5000 ) t -= 5000;
    glUniform1f( timeParam, t );
    glVertexAttrib3f ( velParam, 0, 0, 0 );      //send vel to vertex shader
    glVertexAttrib3f(positionParam, 0, 20, 0);
    glutSolidSphere(10, 25, 25);
     
    glUseProgram(0);
    glEnable(GL_CULL_FACE);
} 

void Shader4::bump()
{ 
    // Add code to respond to being bumped by the 
    // view object (see Sphere1 for example)
}
