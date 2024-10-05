#ifndef __VIEW_H__
#define __VIEW_H__

#include "Point.h"
#include "Scene.h"
#include "Model.h"

class Program;

class View
{
    Point _position;
    float _yaw;
    float linearSpeed;
    float rotationalSpeed;
    int moving;  // -1 = backwards, 0 = still, 1 = forwards
    int rotatingYaw;  // -1 = counterclockwise, 0 = still, 1 = clockwise
    Scene *_scene;
    float _radius;
    float _linearSpeedX;
    float _linearSpeedZ;
    Program *program;
    bool lockPosition;
  public:
    View(Point position, float yaw)
    : _position(position), _yaw(yaw), moving(0), 
      rotatingYaw(0), linearSpeed(0.06), rotationalSpeed(0.0020),
      _radius(.5), fromAbove(0), _linearSpeedX(0), _linearSpeedZ(0),
      lockPosition(1)
    {}
    bool fromAbove;
    void move(Point change) {  _position = _position + change; }
    void changeYaw(float change) { _yaw += change; }
    void update(int elapsedTime, int deltaTime);
    void set();
    void keyboard(unsigned char key, int x, int y);
    void keyboardUp(unsigned char key, int x, int y);
    void keyboardDown(unsigned char key, int x, int y);
    void motion(int x, int y);
    void mouse(int button, int state, int x, int y);
    void setScene(Scene *scene) { _scene = scene; }
    float getRadius() { return _radius; }
    Point getPosition() { return _position; }
    bool intersects(Model *model);
    bool collided();
    virtual void bump(Point direction);
    void setProgram(Program *p) { program = p; }
};

#endif
