#include "Torus1.h"

#include "main.h"
#include "Point.h"
#include "Matrix.h"
#include "bmp.h"
#include <vector>

/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

#define stripeImageWidth 32
GLubyte stripeImage[4*stripeImageWidth];

static GLuint texName;

void makeStripeImage(void)
{
    int j;
    for (j= 0; j < stripeImageWidth; ++j)
    {
        stripeImage[4*j] = (GLubyte) ((j<=4) ? 255 : 0);
        stripeImage[4*j+1] = (GLubyte) ((j>4) ? 255 : 0);
        stripeImage[4*j+2] = (GLubyte) 0;
        stripeImage[4*j+3] = (GLubyte) 255;
    }
}

void makeCheckImage3(void)
{
    int i, j, a, b, c;
    
    for (i = 0; i < checkImageHeight; i++) {
        for (j = 0; j < checkImageWidth; j++) {
            a = ((((i&0x8)==0)^((j&0x8))==0))*255;
            b = ((((i&0x8)==0)^((j&0x8))==0))*255;
            c = ((((i&0x8)==0)^((j&0x8))==0))*255;
            
            checkImage[i][j][0] = (GLubyte) a;
            checkImage[i][j][1] = (GLubyte) b;
            checkImage[i][j][2] = (GLubyte) c;
            checkImage[i][j][3] = (GLubyte) 255;
        }
    }
}

Torus1::Torus1(Point position)
: Model(position), _theta(0)
{
    _radius = 15.0;
    switch (detail)
    {
        case 0:
            _precision = 4;
            break;
        case 1:
            _precision = 10;
            break;
        case 2:
            _precision = 22;
            break;
        case 3:
            _precision = 40;
            break;
        case 4:
            _precision = 80;
            break;
        default:
            _precision = 22;
    }
}

void Torus1::init()
{
    //makeStripeImage();
    makeCheckImage3();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                 checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 checkImage);
    
    
    //glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
    
    _initialPosition.y = 11;
    _position.y = 11.0;
    _pitch = 90.0;
    _rotationXAxis = 0;
    _rotationZAxis = 0;
    _tiltAngle = 30.0;
    _thetaSpeed = 360.0 / 1000.0;
    
    _checkCollisions = true;
    _respondsToCollisions = true;
    _projectShadow = true;
    
}

static float speed = 0;
static float accel = 0.6;
void Torus1::update(int elapsedTime, int deltaTime)
{
    _theta += _thetaSpeed * deltaTime;
    
    if (_theta > 360.0)
    {
        _theta -= 360.0;
     }
    float radians = _theta * M_PI / 180.0;
    _rotationXAxis = cos(radians);
    _rotationZAxis = sin(radians);
    _pitch = 90.0 + _rotationXAxis * _tiltAngle;
    _roll = _rotationZAxis * _tiltAngle;
    
    
    if (_position.y < 10)
    {
        if (speed > -2)
        {
            Model::update(elapsedTime, deltaTime);
            return;
        }
        _position.y = 10;
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

void Torus1::doPreTransformations()
{
    static float zRotation = 0.0;
    zRotation += 4;
    Model::doPreTransformations();
    glRotatef(zRotation, 0, 0, 1.0);
    glScalef(10, 10, 10);
}

void Torus1::draw()
{
    if (_showTextures)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texName);
        
        // Set up automatic texture coordinate calculation.
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        //glEnable(GL_TEXTURE_1D);
    }
    
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    //glutSolidTorus(.5, 1, 40, 40);
    if (_showWireFrame)
        glutWireTorus(.5, 1, _precision, _precision);
    else
        glutSolidTorus(.5, 1, _precision, _precision);
    
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_1D);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_AUTO_NORMAL);
    glDisable(GL_NORMALIZE);
    glDisable(GL_CULL_FACE);
}  

void Torus1::drawProjectionShadow()
{
    glutSolidTorus(.5, 1, _precision, _precision);
}

void Torus1::bump(Point direction)
{ 
    float speed = .04;
    float deltaX = _position.x - direction.x;
    float deltaZ = _position.z - direction.z;
    float theta = atan2(deltaZ, deltaX);
    if (theta < 0.0)
    {
        theta = 2.0 * M_PI + theta;
    }
    _linearSpeedX = speed * cos(theta); 
    _linearSpeedZ = speed * sin(theta);
}
