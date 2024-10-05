#ifndef __MODEL_H__
#define __MODEL_H__

#include "Point.h"
class Scene;

class Model
{
protected:
    Point _position;
    Point _initialPosition;
    float _yaw;
    float _pitch;
    float _roll;
    float _initialYaw;
    float _initialPitch;
    float _initialRoll;
    float _linearSpeedX;
    float _linearSpeedY;
    float _linearSpeedZ;
    float _rotationalSpeedYaw;
    float _rotationalSpeedPitch;
    float _rotationalSpeedRoll;
    float _radius;
    Scene *_scene;
    bool _checkCollisions; // If false, ignore this object in collision detection
    bool _respondsToCollisions;
    bool _showWireFrame;
    float falling; // Used when object falls off the edge
    bool _projectShadow;
    float shadowMatrix[16];
    bool _showTextures;
public:
    Model(Point position);
    virtual ~Model();
    virtual void init() = 0;
    virtual void update(int elapsedTime, int deltaTime);
    void projectShadow();
    virtual void doPreTransformations();
    virtual void doPostTransformations();
    virtual void draw() = 0;
    virtual void drawProjectionShadow() {};
    float getRadius() { return _radius; }
    Point getPosition() { return _position; }
    virtual void reset();
    bool intersects(Model *model);
    bool collided();
    void setScene(Scene *scene) { _scene = scene; }
    virtual void bump(Point direction);
    bool getCheckCollisions() { return _checkCollisions; }
    bool getRespondsToCollisions() { return _respondsToCollisions; }
    void setShowWireFrame(bool value) { _showWireFrame = value; }
    void setShowTextures(bool value) { _showTextures = value; }
    
    static int detail;  // Amount of vertices used. 1 = small 2 = medium 3 = large.
};

#endif
