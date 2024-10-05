#include "Shader3.h"

Shader3::Shader3(Point position)
: Model(position), shader()
{
    _radius = 0.0;
}

Shader3::Shader3()
{
    glDeleteShader(shader.vertexShaderObject);
    glDeleteShader(shader.fragmentShaderObject);
    glDeleteProgram(shader.programObject);
}

void Shader3::init()
{   
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
    readShaderSource("particle1.vert", &VertexShaderSource, shader);
    readShaderSource("particle1.frag", &FragmentShaderSource, shader);
    loadstatus = installShaders(VertexShaderSource, FragmentShaderSource, shader);
    
    printf("Load status for Shader2 shaders: %d\n", loadstatus);
    
    timeParam = glGetUniformLocation ( shader.programObject, "time" );
    velParam = glGetAttribLocation ( shader.programObject, "vel" );
}

void Shader2::update(int elapsedTime, int deltaTime)
{
    Model::update(elapsedTime, deltaTime);   
    
}

void Shader3::draw()
{
    glDisable(GL_CULL_FACE);
    glUseProgram(shader.programObject);
    float t = glutGet ( GLUT_ELAPSED_TIME );
    while ( t > 15000 ) t -= 15000;
    glUniform1f( timeParam, t );
    for (int i = 0; i < particleCount; ++i)
    {
        glVertexAttrib3f ( velParam, particles[i]->vx, particles[i]->vy, particles[i]->vz );      //send vel to vertex shader
        
        glBegin(GL_POLYGON);
        int red = 255 - rand() %50;
        int blue = 255 / 2 - rand()%50;
        int green = 255 / 3 - rand()%30;
        //glColor3f ( ((float) red) / 255.0, ((float) green) / 255.0, ((float) blue) / 255.0 ); 
        glColor3f (0, .5, .3);
        glVertex2f( -30, 5 );
        glVertex2f( -30.0 + 0.2, 5 );
        glVertex2f( -30.0 + 0.2, 5 + 0.4 );
        glVertex2f( -30.0, 5 + 0.4);
        glEnd();
    }
     
    glUseProgram(0);
    glEnable(GL_CULL_FACE);
} 

void Shader3::bump()
{ 
    // Add code to respond to being bumped by the 
    // view object (see Sphere1 for example)
}
