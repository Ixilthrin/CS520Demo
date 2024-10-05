#ifndef __KING_H__
#define __KING_H__

#include "main.h"
#include "ChessPiece.h"
#include "Point.h"
#include <vector>

class King : public ChessPiece
{
public:
    King(Point position);
    King(Point position, int color);
    virtual void draw();
};

#endif
