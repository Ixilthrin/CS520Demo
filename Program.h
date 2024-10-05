#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "main.h"
#include "Point.h"

class Program
{
public:
    Program();
    virtual void update(int elapsedTime, int deltaTime) = 0;
    virtual void setup();
    virtual void reshape(int w, int h);
    virtual void display() = 0;
    virtual void keyboard(unsigned char key, int x, int y) = 0;
    virtual void keyboardUp(unsigned char key, int x, int y) = 0;
    virtual void keyboardDown(unsigned char key, int x, int y) = 0;
    virtual void motion(int x, int y) = 0;
    virtual void mouse(int button, int state, int x, int y) = 0;
    virtual bool lightingEnabled() { return false; }
    virtual bool shadowsEnabled() { return false; }
    virtual Point getLightPosition0() { Point p; return p; }
    virtual bool wireFrameEnabled() { return false; }
};

#endif