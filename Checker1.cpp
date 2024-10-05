#include "Checker1.h"

#include "main.h"
#include "Point.h"
#include "Matrix.h"
#include "bmp.h"
#include <vector>


/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint texName;

void makeCheckImage(void)
{
   int i, j, a, b, c;

   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         a = ((((i&0x8)==0)^((j&0x8))==0))*0;
         b = ((((i&0x8)==0)^((j&0x8))==0))*255;
         if (b == 0) a = 255;
         c = ((((i&0x8)==0)^((j&0x8))==0))*0;
          
         checkImage[i][j][0] = (GLubyte) a;
         checkImage[i][j][1] = (GLubyte) b;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}


Checker1::Checker1(Point position)
: Model(position)
{
    //_rotationalSpeedPitch = 0.05;
}

void Checker1::init()
{
    makeCheckImage();
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                 checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 checkImage);
    
    float xMin = -100;
    float xMax = 100;
    float zMin = -100;
    float zMax = 100;
    float xDivisions;
    float zDivisions;
    switch (detail)
    {
        case 0:
            xDivisions = 79;
            zDivisions = 79;
            break;
        case 1:
            xDivisions = 7;
            zDivisions = 7;
            break;
        case 2:
            xDivisions = 39;
            zDivisions = 39;
            break;
        case 3:
            xDivisions = 79;
            zDivisions = 79;
            break;
        case 4:
            xDivisions = 119;
            zDivisions = 119;
            break;
        default:
            xDivisions = 39;
            zDivisions = 39;
    }
    float deltaX = (xMax - xMin) / (xDivisions + 1.0);
    float deltaZ = (zMax - zMin) / (zDivisions + 1.0);
    float deltaU = 1.0 / (xDivisions + 1.0);
    float deltaV = 1.0 / (zDivisions + 1.0);
    for (int j = 0; j < zDivisions + 1.0; ++j)
    {
        for (int i = 0; i < xDivisions + 1.0; ++i)
        {
            Point p1, p2, p3, p4;
            TextureCoordinate t1, t2, t3, t4;
            p1.x = xMin + ((float) i) * deltaX;
            p1.y = 0;
            p1.z = zMin + ((float) j) * deltaZ;
            t1.u = ((float) i) * deltaU;
            t1.v = ((float) j) * deltaV;
            
            p2.x = xMin + ((float) i) * deltaX;
            p2.y = 0;
            p2.z = zMin + ((float) (j + 1)) * deltaZ;
            t2.u = ((float) i) * deltaU;
            t2.v = ((float) (j + 1)) * deltaV;
            
            p3.x = xMin + ((float) (i + 1)) * deltaX;
            p3.y = 0;
            p3.z = zMin + ((float) (j + 1)) * deltaZ;
            t3.u = ((float) (i + 1)) * deltaU;
            t3.v = ((float) (j + 1)) * deltaV;
            
            p4.x = xMin + ((float) (i + 1)) * deltaX;
            p4.y = 0;
            p4.z = zMin + ((float) j) * deltaZ;
            t4.u = ((float) (i + 1)) * deltaU;
            t4.v = ((float) j) * deltaV;
            
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);
            points.push_back(p4);
            
            texs.push_back(t1);
            texs.push_back(t2);
            texs.push_back(t3);
            texs.push_back(t4);
        }
    }
}

void Checker1::draw()
{
    if (_showTextures)
    {
        glBindTexture(GL_TEXTURE_2D, texName);
        glEnable(GL_TEXTURE_2D);
    }
    
    if (_showWireFrame)
    {
        int i = 0;
        while (i < points.size())
        {
            glBegin(GL_LINE_STRIP);
            for (int j = 0; j < 4; ++j)
            {
                glNormal3f(0.0, 1.0, 0.0);
                glTexCoord2f(texs[i+j].u, texs[i+j].v);
                glVertex3f(points[i+j].x, points[i+j].y, points[i+j].z);
            }
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(texs[i].u, texs[i].v);
            glVertex3f(points[i].x, points[i].y, points[i].z);
            glEnd();
            i = i + 4;
        }
    }
    else
    {
        glBegin(GL_QUADS);
        for (int i = 0; i < points.size(); ++i)
        {
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(texs[i].u, texs[i].v);
            glVertex3f(points[i].x, points[i].y, points[i].z);
        }
        glEnd();
    }
    
    /*
     glNormal3f(0.0 , 1.0, 0.0);
     glTexCoord2f(0.0, 0.0); glVertex3f(-100.0, 0.0, 100.0);
     glNormal3f(0.0 , 1.0, 0.0);
     glTexCoord2f(1.0, 0.0); glVertex3f(100.0, 0.0, 100.0);
     glNormal3f(0.0 , 1.0, 0.0);
     glTexCoord2f(1.0, 1.0); glVertex3f(100.0, 0.0, -100.0);
     glNormal3f(0.0 , 1.0, 0.0);
     glTexCoord2f(0.0, 1.0); glVertex3f(-100.0, 0.0, -100.0);
     */
     
    glDisable(GL_TEXTURE_2D);
}
