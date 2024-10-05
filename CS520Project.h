#ifndef __CS520PROJECT_H__
#define __CS520PROJECT_H__

#include "Program.h"

#include "View.h"
#include "Scene.h"


class CS520Project : public Program
{
private:
    Model *explosion;
    View *view;
    Scene *scene;
    bool showWireFrame;
    bool showTextures;
    bool enableLight;
    bool enableFog;
    bool enableShadows;
    bool enableFlashlightMode;
    Point lightPosition0;
public:
    CS520Project();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void setup();
    virtual void reshape(int w, int h);
    virtual void display();
    virtual void keyboard(unsigned char key, int x, int y);
    virtual void keyboardUp(unsigned char key, int x, int y);
    virtual void keyboardDown(unsigned char key, int x, int y);
    virtual void motion(int x, int y);
    virtual void mouse(int button, int state, int x, int y);
    virtual bool lightingEnabled() { return enableLight; }
    virtual bool shadowsEnabled() { return enableShadows; }
    virtual Point getLightPosition0() { return lightPosition0; }
    virtual bool wireFrameEnabled() { return showWireFrame; }
};

#endif