#ifndef __PAWN_H__
#define __PAWN_H__

#include "main.h"
#include "ChessPiece.h"
#include "Point.h"
#include <vector>

class Pawn : public ChessPiece
{
public:
    Pawn(Point position);
    Pawn(Point position, int color);
};

#endif
