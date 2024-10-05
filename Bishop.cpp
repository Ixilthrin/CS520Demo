#include <math.h>
#include "Bishop.h"
#include "main.h"
#include "Point.h"
#include "bmp.h"

const double PI = 3.14159265389;

GLfloat bishop[25][3] = {
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
       };

GLfloat btop[6][3] = 
{
    {-0.2, 0.0, 0.0}, 
    {1.8, 1.2, 0.0},
        {3.8, 1.0, 0.0},
    {4.6, 0.6, 0.0},
        {5.1, 0.6, 0.0}, 
    {5.8, 1.2, 0.0}
};

//static char w[] = "wmarble";


Bishop::Bishop(Point position)
: ChessPiece(position)
{
    baseControlPts = (GLfloat*) bishop;
    numberBasePoints = 25;
    topControlPts = (GLfloat*) btop;
    numberTopPoints = 6;
    baseStartX = 4.15;
    baseEndX = 14.7;
    topStartX = -.2;
    topEndX = 4.8;
    _radius = 6;
}

Bishop::Bishop(Point position, int color)
: ChessPiece(position)
{
    this->color = color;
    baseControlPts = (GLfloat*) bishop;
    numberBasePoints = 25;
    topControlPts = (GLfloat*) btop;
    numberTopPoints = 6;
    baseStartX = 4.15;
    baseEndX = 14.7;
    topStartX = -.2;
    topEndX = 4.8;
    _radius = 6;
}


