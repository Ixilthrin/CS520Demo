#ifndef __TUBE1_H__
#define __TUBE1_H__

#include "Model.h"
#include "Point.h"

class Tube1 : public Model
{
public:
    Tube1(Point position);
    virtual void init();
    virtual void draw();
};

#endif
