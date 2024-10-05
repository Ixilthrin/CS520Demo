#ifndef __SHADER4_H__
#define __SHADER4_H__

#include "Model.h"
#include "shaders.h"
#include "Point.h"

class Shader4 : public Model
{
    ShaderObjects shader;
public:
    Shader4(Point position);
    virtual ~Shader4();
    virtual void init();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void draw();
    virtual void bump();
};

#endif
