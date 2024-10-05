#ifndef __TORUS1_H__
#define __TORUS1_H__

#include "Model.h"
#include "Point.h"

class Torus1 : public Model
{
    float _theta;  // angle where torus touches surface
    float _thetaSpeed;  // speed of rotation of theta
    float _rotationXAxis;
    float _rotationZAxis;
    float _tiltAngle;
    int _precision;
    
public:
    Torus1(Point position);
    virtual void init();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void doPreTransformations();
    virtual void draw();
    void drawProjectionShadow();
    virtual void bump(Point direction);
};

#endif
