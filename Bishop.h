#ifndef __Bishop_H__
#define __Bishop_H__

#include "main.h"
#include "ChessPiece.h"
#include "Point.h"
#include <vector>

class Bishop : public ChessPiece
{
public:
    Bishop(Point position);
    Bishop(Point position, int color);
};

#endif
