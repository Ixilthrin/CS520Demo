#include "Shader2.h"

GLuint timeParam;               //parameters for sending to vertex shader
GLuint velParam;                //parameters for sending to vertex shader

struct Particle
{
    float vx, vy, vz;
    Particle() {
        vx = ((float) (rand()%100000))/ ((float)(rand()%50000)) + (float)(rand()%20);
        vy = ((float) (rand()%100000))/ ((float)(rand()%50000)) + (float)(rand()%20);
        vz = ((float) (rand()%100000))/ ((float)(rand()%50000)) + (float)(rand()%20);
        if (rand()%10 < 5)
        {
            vx = -vx + 10;
        }
        if (rand()%10 < 5)
        {
            vz = -vz;
        }
    }
};

Particle **particles;
int particleCount = 10000;


Shader2::Shader2(Point position)
: Model(position), shader()
{
    // The effective radius of this object for collision
    // detection purposes.
    _radius = 0.0;
}

Shader2::~Shader2()
{
    glDeleteShader(shader.vertexShaderObject);
    glDeleteShader(shader.fragmentShaderObject);
    glDeleteProgram(shader.programObject);
}

void Shader2::init()
{   
    printf("Shader2 init()\n");
    switch (detail)
    {
        case 0:
            particleCount = 100;
            break;
        case 1:
            particleCount = 1000;
            break;
        case 2:
            particleCount = 7000;
            break;
        case 3:
            particleCount = 10000;
            break;
        case 4:
            particleCount = 25000;
            break;
        default:
            particleCount = 7000;
    }
    srand(time(0));
    particles = new Particle*[particleCount];
    for (int i = 0; i < particleCount; ++i)
        particles[i] = new Particle();
    
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

void Shader2::draw()
{
    
    glUseProgram(shader.programObject);
    float t = glutGet ( GLUT_ELAPSED_TIME );
    while ( t > 15000 ) t -= 15000;
    glUniform1f( timeParam, t );
    for (int i = 0; i < particleCount; ++i)
    {
        glVertexAttrib3f ( velParam, particles[i]->vx, particles[i]->vy, particles[i]->vz );      //send vel to vertex shader
        
        if (_showWireFrame)
            glBegin(GL_LINE_STRIP);
        else
            glBegin(GL_POLYGON);
        
        //glColor3f (0, .5, .3);
        //glVertex2f( -30, 5 );
        //glVertex2f( -30.0 + 0.2, 5 );
        //glVertex2f( -30.0 + 0.2, 5 + 0.4 );
        //glVertex2f( -30.0, 5 + 0.4);
        
        if (i % 2 == 0)
        {
            glVertex2f( -30, 5 );
            glVertex2f( -30.0 + 0.1, 5 );
            glVertex2f( -30.0 + 0.2, 5 + 0.2 );
            glVertex2f( -30.0, 5 + 0.2);
        }
        else
        {
            glVertex2f( -30, 5 );
            glVertex2f( -30.0 + 0.2, 5 );
            glVertex2f( -30.0 + 0.3, 5 + 0.2 );
            glVertex2f( -30.0, 5 + 0.1);
        }
        
        glEnd();
    }
     
    glUseProgram(0);
} 

void Shader2::bump()
{ 
    // Add code to respond to being bumped by the 
    // view object (see Sphere1 for example)
}
