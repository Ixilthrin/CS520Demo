#ifndef __SHADER5_H__
#define __SHADER5_H__

#include "Model.h"
#include "shaders.h"
#include "Point.h"

class Shader5 : public Model
{
    ShaderObjects shader;
public:
    Shader5(Point position);
    virtual ~Shader5();
    virtual void init();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void draw();
    virtual void bump();
};

#endif
