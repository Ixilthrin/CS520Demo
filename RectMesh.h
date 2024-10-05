#ifndef __RECTMESH_H__
#define __RECTMESH_H__

#include "Point.h"
#include "Model.h"

class Vertex 
{
public:
    float x;
    float y;
    float z;
    float u;
    float v;
};

class RectMesh : public Model
{
    Vertex **_vertices;
    int _divisions;
    int _width;
public:
    RectMesh(int divisions, Point position, int width);
    ~RectMesh();
    virtual void init();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void draw();
};
#endif