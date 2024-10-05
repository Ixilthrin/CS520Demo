#include <math.h>
#include "Queen.h"
#include "main.h"
#include "Point.h"
#include "bmp.h"

const double PI = 3.14159265389;

GLfloat Qtop[16][3] = 
{
    
    {-3.0, 0.0, 0.0}, 
    {-2.8, 4.3, 0.0},
    {-2.2, 4.2, 0.0},
        {-1.7, 4.2, 0.0},
    {-1.4, 4.1, 0.0},
        {-0.8, 4.1, 0.0}, 
    {-0.4, 4.0, 0.0}, 
    {0.2, 3.5, 0.0},
    {0.3, 3.4, 0.0},
    {0.9, 3.6, 0.0},
    {1.2, 3.6, 0.0},
    {1.7, 3.0, 0.0},
    {1.9, 2.9, 0.0},
    {2.1, 2.7, 0.0},
    {2.2, 2.5, 0.0},
    {2.5, 2.3, 0.0}
//const float startx = -2.82, endx = 2.49;

};

GLfloat queen[32][3] = {
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
//const float startx = 2.49, endx = 14.7;
};

//static char w[] = "wmarble";

Queen::Queen(Point position)
: ChessPiece(position)
{
    baseControlPts = (GLfloat*) queen;
    numberBasePoints = 32;
    topControlPts = (GLfloat*) Qtop;
    numberTopPoints = 16;
    baseStartX = 2.49;
    baseEndX = 14.7;
    topStartX = -2.82;
    topEndX = 2.49;
    _radius = 8;
}

Queen::Queen(Point position, int color)
: ChessPiece(position)
{
    this->color = color;
    baseControlPts = (GLfloat*) queen;
    numberBasePoints = 32;
    topControlPts = (GLfloat*) Qtop;
    numberTopPoints = 16;
    baseStartX = 2.49;
    baseEndX = 14.7;
    topStartX = -2.82;
    topEndX = 2.49;
    _radius = 8;
}

