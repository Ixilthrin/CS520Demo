#ifndef __TUBEASSIGNMENT_H__
#define __TUBEASSIGNMENT_H__

#include "Program.h"

#include "View.h"
#include "Scene.h"

class TubeAssignment : public Program
{
private:
    View *view;
    Scene *scene;
public:
    TubeAssignment();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void setup();
    virtual void reshape(int w, int h);
    virtual void display();
    virtual void keyboard(unsigned char key, int x, int y);
    virtual void keyboardUp(unsigned char key, int x, int y);
    virtual void keyboardDown(unsigned char key, int x, int y);
    virtual void motion(int x, int y);
    virtual void mouse(int button, int state, int x, int y);
};

#endif