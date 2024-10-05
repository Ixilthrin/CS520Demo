#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Point.h"

class Matrix
{
  public:
    float a1, a2, a3, a4;
    float b1, b2, b3, b4;
    float c1, c2, c3, c4;
    float d1, d2, d3, d4;
    Point multiply(Point &p)
    {
        Point r;
        r.x = p.x * a1 + p.y * a2 + p.z * a3 + a4;
        r.y = p.x * b1 + p.y * b2 + p.z * b3 + b4;
        r.z = p.x * c1 + p.y * c2 + p.z * c3 + c4;
        return r;
    }
    Matrix multiply(Matrix &m)
    {
        Matrix r;
        return r;
    }
};

#endif
