#ifndef __SPHERE1_H__
#define __SPHERE1_H__

#include "Model.h"
#include "Point.h"

class Sphere1 : public Model
{
        int precision;
public:
    Sphere1(Point position);
    virtual void init();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void draw();
    virtual void drawProjectionShadow();
    virtual void bump(Point direction);
};

#endif
