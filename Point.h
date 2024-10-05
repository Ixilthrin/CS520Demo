#ifndef __point_h__
#define __point_h__

class Point
{
  public:
    Point(float px, float py, float pz)
    : x(px), y(py), z(pz)
    {}
    Point() : x(0.0), y(0.0), z(0.0) 
    {}
    float x;
    float y;
    float z;
    Point operator+(const Point &p1)
    {
        Point p;
        p.x = x + p1.x;
        p.y = y + p1.y;
        return p;
    }
};

struct TextureCoordinate
{
    float u;
    float v;
};

#endif

