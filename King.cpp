#include <math.h>
#include "King.h"
#include "main.h"
#include "Point.h"

const double PI = 3.14159265389;

GLfloat king[32][3] = {
    {0.5, 0.0, 0.0}, { 2.1, 2.5, 0.0}, 
    {2.6, 2.6, 0.0}, {2.8, 2.4, 0.0},
    {3.05, 2.0, 0.0}, {3.3, 2.0, 0.0},
    {3.6, 1.5, 0.0}, {4.0, 1.5, 0.0},
    {4.3, 1.5, 0.0}, {5.1, 2.2, 0.0},
        {5.6, 3.5, 0.0}, {6.0, 3.6, 0.0},
    {6.4, 2.5, 0.0}, {7.225, 1.5, 0.0},
    {7.7, 1.6, 0.0}, {8.3, 1.7, 0.0},
    {9.0, 1.75, 0.0}, {9.725, 2.00, 0.0},
    {10.45, 2.20, 0.0}, {10.95, 2.575, 0.0},
    {11.4, 3.0, 0.0}, {12.0, 3.475, 0.0},
    {12.6, 4.7, 0.0}, {12.8, 4.8, 0.0},
    {13.2, 4.40, 0.0},{13.5, 4.6, 0.0},
    {13.9, 5.2, 0.0}, {14.25, 5.1, 0.0},
    {14.65, 4.0, 0.0}, {15.3, 4.0, 0.0}, 
    {15.7, 4.0, 0.0}, {16.0, 4.0, 0.0}
//const float startx = 2.6, endx = 14.7;
};

GLfloat Ktop[17][3] = 
{
    
    {-2.1, 0.0, 0.0}, 
    {-2.0, 3.1, 0.0},
    {-1.8, 4.25, 0.0},
        {-1.6, 4.3, 0.0},
    {-1.2, 4.25, 0.0},
        {-0.8, 4.1, 0.0}, 
    {-0.3, 3.8, 0.0}, 
    {0.1, 3.5, 0.0},
    {0.4, 3.3, 0.0},
    {0.9, 3.1, 0.0},
    {1.2, 3.2, 0.0},
    {1.7, 3.3, 0.0},
    {1.9, 3.5, 0.0},
    {2.1, 3.4, 0.0},
    {2.2, 3.2, 0.0},
    {2.4, 2.9, 0.0},
    {2.7, 2.5, 0.0}
//const float startx = -2.14, endx = 2.6;

};

GLfloat cross[11][3] = 
{

    {-4.14, 0.0, 0.0},
        {-4.14, 0.8, 0.0},
    {-4.1, 0.8, 0.0},
        {-3.7, 0.8, 0.0}, 
    {-3.4, 0.8, 0.0}, 
    {-3.4, 2.0, 0.0},
    {-2.9, 2.0, 0.0},
    {-2.9, 0.8, 0.0},
    {-2.6, 0.8, 0.0},
    {-2.3, 0.8, 0.0},
    {-2.1, 0.8, 0.0}
//

};

// changed wmarble to green
//static char w[] = "wmarble";
//static char w[] = "green";


King::King(Point position)
: ChessPiece(position)
{
    baseControlPts = (GLfloat*) king;
    numberBasePoints = 32;
    topControlPts = (GLfloat*) Ktop;
    numberTopPoints = 17;
    baseStartX = 2.6;
    baseEndX = 14.7;
    topStartX = -2.14;
    topEndX = 2.6;
    _radius = 8;
}

King::King(Point position, int color)
: ChessPiece(position)
{
    this->color = color;
    baseControlPts = (GLfloat*) king;
    numberBasePoints = 32;
    topControlPts = (GLfloat*) Ktop;
    numberTopPoints = 17;
    baseStartX = 2.6;
    baseEndX = 14.7;
    topStartX = -2.14;
    topEndX = 2.6;
    _radius = 8;
}

void dcross(void)
{
   int i, j, n=0;
   float x, y, z, r;                //current coordinates
   float x1, y1, z1, r1;            //next coordinates
   float theta;
   const float startx = -4.14, endx = -2.14;
   const int nx = 11;                //number of slices along x-direction
   const int ntheta = 20;            //number of angular slices
   const float dx = (endx - startx) / nx;    //x step size
   const float dtheta = 2*PI / ntheta;        //angular step size

   x = startx;
   r = cross[n++][1];
  
   for ( i = 0; i < nx; ++i ) 
   {            //step through x
      theta = 0;
      x1 = x + dx;                //next x

      r1 = cross[n++][1];        //next f(x)
      //draw the surface composed of quadrilaterals by sweeping theta
      glBegin( GL_QUAD_STRIP );
    for ( j = 0; j <= ntheta; ++j )
    {
      theta += dtheta;
      double cosa = cos( theta );
      double sina = sin ( theta );
      y = r * cosa;  y1 = r1 * cosa;    //current and next y
      z = r * sina;     z1 = r1 * sina;    //current and next z
     
      //edge from point at x to point at next x
          glTexCoord2f(x, theta);
      glVertex3f (y, -x, z);
          glTexCoord2f(x1, theta+dtheta);
      glVertex3f (y1, -x1, z1);
      
      //forms quad with next pair of points with incremented theta value    
    }                  
      glEnd();
      x = x1;
      r = r1;    
   } //for i
}

void King::draw()
{
    ChessPiece::draw();
    dcross();
}
