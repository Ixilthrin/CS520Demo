#ifndef __ROTATOR_H__
#define __ROTATOR_H__

#include "Point.h"

class Rotator
{
  private:
    int _axis;
    float _angle;
    float _cosine;
    float _sine;
  public:
    enum {  X_AXIS, Y_AXIS, Z_AXIS };
    Rotator(int axis, float angle);
    ~Rotator();
    Point rotate(Point p);
};

#endif
