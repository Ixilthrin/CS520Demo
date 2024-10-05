#ifndef __SCENE_H__
#define __SCENE_H__

#include "main.h"
#include "Model.h"
#include <vector>
class View;  // Forward declaration since View.h already includes Scene.h
class Program;

class Scene
{
    vector<Model *> models;
    View *view;
    Program *program;
public:
    Scene(Program *p);
    ~Scene();
    void init();
    void setView(View *v) { view = v; }
    void addModel(Model *model) { models.push_back(model); }
    void update(float elapsedTime, float deltaTime);
    void draw();
    vector<Model *> getModels() { return models; }
    Program *getProgram() { return program; }
};

#endif