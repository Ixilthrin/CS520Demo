#ifndef __SPHERE2_H__
#define __SPHERE2_H__

#include "Model.h"
#include "Point.h"

class Sphere2 : public Model
{
public:
    Sphere2(Point position);
    virtual void init();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void draw();
};

#endif
