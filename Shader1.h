#ifndef __SHADER1_H__
#define __SHADER1_H__

#include "Model.h"
#include "shaders.h"

class Shader1 : public Model
{
    ShaderObjects shader;
public:
    Shader1(Point position);
    virtual ~Shader1();
    virtual void init();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void draw();
    virtual void bump();
};

#endif
