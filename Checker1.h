#ifndef __CHECKER1_H__
#define __CHECKER1_H__

#include "Model.h"
#include "Point.h"

#include <vector>
using namespace std;

class Checker1 : public Model
{
    vector<Point> points;
    vector<TextureCoordinate> texs;
public:
    Checker1(Point position);
    virtual void init();
    virtual void draw();
};

#endif
