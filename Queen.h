#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "main.h"
#include "ChessPiece.h"
#include "Point.h"
#include <vector>

class Queen : public ChessPiece
{
public:
    Queen(Point position);
    Queen(Point position, int color);
};

#endif
