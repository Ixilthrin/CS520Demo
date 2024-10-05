#include <math.h>
#include "Pawn.h"
#include "main.h"
#include "Point.h"
#include "bmp.h"
#include <iostream>


GLfloat pawn[19][3] = {
    {8.5, 0.0, 0.0}, {8.7, 0.7, 0.0}, 
    {8.9, 1.3, 0.0}, {9.2, 1.4, 0.0}, 
    {9.6, 1.2, 0.0}, {10.26, 0.8, 0.0}, 
    {10.264, 0.8, 0.0}, {10.66, 0.8, 0.0},
        {11.46, 2.0, 0.0}, {12.06, 2.6, 0.0}, 
    {12.66, 2.0, 0.0}, {13.064, 2.0, 0.0}, 
    {13.46, 2.8, 0.0}, {13.66, 3.2, 0.0}, 
    {14.26, 3.4, 0.0}, {14.261, 3.4, 0.0}, 
    {14.56, 3.2, 0.0}, {14.66, 2.0, 0.0}, 
    {14.71, 0.0, 0.0}
};


Pawn::Pawn(Point position)
: ChessPiece(position)
{ 
    baseControlPts = (GLfloat*) pawn;
    numberBasePoints = 19;
    topControlPts = 0;
    numberTopPoints = 0;
    baseStartX = 8.5;
    baseEndX = 14.7;
    topStartX = 0;
    topEndX = 0;
    _radius = 5;
}

Pawn::Pawn(Point position, int color)
: ChessPiece(position)
{
    this->color = color;
    baseControlPts = (GLfloat*) pawn;
    numberBasePoints = 19;
    topControlPts = 0;
    numberTopPoints = 0;
    baseStartX = 8.5;
    baseEndX = 14.7;
    topStartX = 0;
    topEndX = 0;
    _radius = 5;
}

