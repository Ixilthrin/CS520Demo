#ifndef __ROOK_H__
#define __ROOK_H__

#include "main.h"
#include "ChessPiece.h"
#include "Point.h"
#include <vector>

class Rook : public ChessPiece
{
public:
    Rook(Point position);
    Rook(Point position, int color);
};

#endif
