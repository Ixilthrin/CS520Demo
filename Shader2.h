#ifndef __SHADER2_H__
#define __SHADER2_H__

#include "Model.h"
#include "shaders.h"
#include "Point.h"

class Shader2 : public Model
{
    ShaderObjects shader;
public:
    Shader2(Point position);
    virtual ~Shader2();
    virtual void init();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void draw();
    virtual void bump();
};

#endif
