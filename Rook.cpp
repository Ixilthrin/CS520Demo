#include <math.h>
#include "Rook.h"
#include "main.h"
#include "Point.h"
#include "bmp.h"

const double PI = 3.14159265389;

GLfloat rook[][3] = {
    {2.8, 0.0, 0.0}, { 3.1, .5, 0.0}, 
    {3.35, 1.0, 0.0}, {3.6, 1.25, 0.0}, {4.025, 1.5, 0.0}, 
    {5.0, 2.2, 0.0},
    {5.3, 2.5, 0.0}, {5.8, 2.5, 0.0},
    {6.475, 2.075, 0.0}, {7.025, 1.4, 0.0},
    {7.3, 1.5, 0.0},
    {8.25, 1.6, 0.0},
    {9.1, 2.00, 0.0},
    {9.9, 2.20, 0.0}, {10.9, 2.575, 0.0},
    {11.6, 3.0, 0.0}, {12.625, 3.475, 0.0},
    {13.15, 4.675, 0.0}, {13.4, 4.80, 0.0},
    {13.825, 4.40, 0.0},{14.3, 4.5, 0.0},
    {14.4, 4.2, 0.0}, {14.5, 3.9, 0.0},
    {14.7, 0.0, 0.0},
    {15.85, 0.0, 0.0}
//const float startx = 4.15, endx = 14.7;
};

GLfloat rtop[16][3] = 
{
    
    {1.0, 0.0, 0.0}, 
    {1.2, 4.3, 0.0},
    {1.5, 4.25, 0.0},
        {2.0, 4.2, 0.0},
    {2.5, 4.15, 0.0},
        {3.1, 4.1, 0.0}, 
    {3.6, 4.0, 0.0}, 
    {4.2, 3.8, 0.0},
    {4.3, 3.7, 0.0},
    {4.9, 3.6, 0.0},
    {5.2, 3.6, 0.0},
    {5.7, 3.4, 0.0},
    {5.9, 3.2, 0.0},
    {6.1, 2.7, 0.0},
    {6.2, 2.5, 0.0},
    {6.5, 2.3, 0.0}

//const float startx = 1.19, endx = 6.2;
};

//static char w[] = "wmarble";


Rook::Rook(Point position)
: ChessPiece(position)
{
    baseControlPts = (GLfloat*) rook;
    numberBasePoints = 25;
    topControlPts = (GLfloat*) rtop;
    numberTopPoints = 16;
    baseStartX = 6.0;
    baseEndX = 14.7;
    topStartX = 1.19;
    topEndX = 6.2;
    _radius = 7;
}

Rook::Rook(Point position, int color)
: ChessPiece(position)
{
    this->color = color;
    baseControlPts = (GLfloat*) rook;
    numberBasePoints = 25;
    topControlPts = (GLfloat*) rtop;
    numberTopPoints = 16;
    baseStartX = 6.0;
    baseEndX = 14.7;
    topStartX = 1.19;
    topEndX = 6.2;
    _radius = 7;
}

