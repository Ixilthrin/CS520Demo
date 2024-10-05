#include "Sphere1.h"

#include "main.h"
#include "Point.h"
#include "Matrix.h"
#include "bmp.h"
#include <vector>


static GLuint textureID;
static GLubyte *texture = 0;
static int textureWidth = 0;
static void loadTexture()
{
    char str[] ="Granite.bmp";
    //char str[] ="green.bmp";
    //char str[] ="bluegrating.bmp";
    BMP *bmp = new BMP();
    bmp->readWithString(str);
    unsigned char *colorValues = bmp->getColorValues();
    int width = bmp->getWidth();
    int height = bmp->getHeight();
    
    textureWidth = width;
    if (height < textureWidth)
    {
        textureWidth = height;
    }
    printf("size = %d\n", textureWidth);
    texture = (GLubyte*) malloc(sizeof(GLubyte) * 4 * textureWidth * textureWidth);
    
    int i = 0;
    int j = 0;
    for (i = textureWidth - 1; i >= 0; --i) {
        for (j = 0; j < textureWidth; ++j) {
            int index = i * 4 * textureWidth + 4 * j;
            texture[index] = (GLubyte) colorValues[(i * 3 * textureWidth) + j*3 + 0];
            //printf("red = %d\n", (int) texture[i][j][0]);
            texture[index + 1] = (GLubyte) colorValues[(i * 3 * textureWidth) + j*3 + 1];
            //printf("green = %d\n", (int) texture[i][j][1]);
            texture[index + 2] = (GLubyte) colorValues[(i * 3 * textureWidth) + j*3 + 2];
            //printf("blue = %d\n", (int) texture[i][j][2]);
            texture[index + 3] = (GLubyte) 255;
        }
    }
}


typedef struct {
    double x;
    double y;
    double z;
} XYZ;

static vector<XYZ> verts;
static vector<XYZ> norms;
static vector<TextureCoordinate> texs;

static void CreateSphere(XYZ c, double r, int n)
{
    const float TWOPI = 2.0 * M_PI;
    const float PI = M_PI;
    int i,j;
    double phi1,phi2,theta, u, v;
    XYZ e,p;
    
    if (r < 0)
        r = -r;
    if (n < 0)
        n = -n;
    if (n < 4 || r <= 0) {
        verts.push_back(c);
        return;
    }
    
    for (j=0;j < n; j++) {
        phi1 = j * TWOPI / n;
        phi2 = (j + 1) * TWOPI / n;    //next phi
        
        for (i=0;i <= n;i++) {
            theta = i * PI / n;
            
            e.x = sin ( theta ) * cos ( phi2 );
            e.y = sin ( theta ) * sin ( phi2 );
            e.z = cos ( theta );
            p.x = c.x + r * e.x;
            p.y = c.y + r * e.y;
            p.z = c.z + r * e.z;
            
            norms.push_back(e);
            u = (double)(j+1) / n;        // column
            v = 1 - (double) i / n;        // row
            //glTexCoord2f(u, v);
            TextureCoordinate t1;
            t1.u = u;
            t1.v = v;
            texs.push_back(t1);
            verts.push_back(p);
            
            e.x = sin ( theta ) * cos ( phi1 );
            e.y = sin ( theta ) * sin ( phi1 );
            e.z = cos ( theta );
            p.x = c.x + r * e.x;
            p.y = c.y + r * e.y;
            p.z = c.z + r * e.z;
            
            norms.push_back(e);
            TextureCoordinate t2;
            t2.u = j/(double)n;
            t2.v = 1-i/(double)n;
            texs.push_back(t2);
            verts.push_back(p);
        }
    }
}

static void DrawSphere(XYZ c,double r,int n, bool wireFrame)
{
    int index = 0;
    int i,j;
    
    if (r < 0)
        r = -r;
    if (n < 0)
        n = -n;
    if (n < 4 || r <= 0) {
        glBegin(GL_POINTS);
        glVertex3f(verts[index].x, verts[index].y, verts[index].z);
        ++index;
        glEnd();
        return;
    }
    
    for (j=0;j < n; j++) {
        
        if (wireFrame)
            glBegin(GL_LINES);
        else
            glBegin(GL_QUAD_STRIP);
        for (i=0;i <= n;i++) {
            
            glNormal3f(norms[index].x, norms[index].y, norms[index].z);
            glTexCoord2f(texs[index].u, texs[index].v);
            glVertex3f(verts[index].x, verts[index].y, verts[index].z);
            ++index;
            
            glNormal3f(norms[index].x, norms[index].y, norms[index].z);
            glTexCoord2f(texs[index].u, texs[index].v);
            glVertex3f(verts[index].x, verts[index].y, verts[index].z);
            ++index;
            
        }
        glEnd();
    }
}


Sphere1::Sphere1(Point position)
: Model(position)
{
    switch (detail)
    {
        case 0:
            precision = 4;
            break;
        case 1:
            precision = 10;
            break;
        case 2:
            precision = 22;
            break;
        case 3:
            precision = 40;
            break;
        case 4:
            precision = 80;
            break;
        default:
            precision = 22;
    }
    _rotationalSpeedYaw = 0.05;
    _radius = 10.0;
}

XYZ coord = { 0.0, 0.0, 0.0 };
void Sphere1::init()
{
    static bool sphereWasCreated = false;
    if (!sphereWasCreated)
    {
        CreateSphere(coord, _radius, precision);
        sphereWasCreated = true;
    }
    
    _checkCollisions = true;
    _respondsToCollisions = true;
    _projectShadow = true;
    
    loadTexture();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 texture);
    
}

static float speed = 0;
static float accel = 0.6;
void Sphere1::update(int elapsedTime, int deltaTime)
{
    if (_position.y < _radius)
    {
        if (speed > -2)
        {
            Model::update(elapsedTime, deltaTime);
            return;
        }
        _position.y = _radius;
        speed = -speed - 2;
        _position.y += speed;
        speed -= accel;
    }
    else
    {
        _position.y += speed;
        speed -= accel;
    }
    Model::update(elapsedTime, deltaTime);
}

void Sphere1::draw()
{
    // Texture mapping
    if (_showTextures)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    DrawSphere(coord, _radius, precision, _showWireFrame);
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
} 

void Sphere1::drawProjectionShadow()
{
    glutSolidSphere(_radius, precision, precision);
}

void Sphere1::bump(Point direction)
{ 
    float speed = .04;
    float rotationalSpeed = .12;
    float deltaX = _position.x - direction.x;
    float deltaZ = _position.z - direction.z;
    float theta = atan2(deltaZ, deltaX);
    if (theta < 0.0)
    {
        theta = 2.0 * M_PI + theta;
    }
    _linearSpeedX = speed * cos(theta); 
    _linearSpeedZ = speed * sin(theta);
    _rotationalSpeedPitch = rotationalSpeed * _linearSpeedZ/speed;
    _rotationalSpeedRoll = -rotationalSpeed * _linearSpeedX/speed;
    _rotationalSpeedYaw = 0;
}
