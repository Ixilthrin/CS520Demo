#ifndef __SHADER3_H__
#define __SHADER3_H__

#include "Model.h"
#include "shaders.h"
#include "Point.h"

class Shader3 : public Model
{
    ShaderObjects shader;
public:
    Shader3(Point position);
    virtual ~Shader3();
    virtual void init();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void draw();
    virtual void bump();
};

#endif
