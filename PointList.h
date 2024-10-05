#ifndef __POINTLIST_H__
#define __POINTLIST_H__

#include "Point.h"
#include "Rotator.h"

class PointList
{
  private:
    Point *_list;
    int _size;
    float _scaleX;
    float _scaleY;
    float _scaleZ;
  public:
    PointList(int size);
    PointList(const PointList& rhs);
    PointList& operator=(const PointList& rhs);
    ~PointList();
    int size() { return _size; }
    void setPoint(int index, Point point)
    {
        _list[index] = point;
    }
    Point* getPoints() { return _list; }
    Point getPoint(int i) { return _list[i]; }
    void scaleX(float s) { _scaleX += s; }
    void scaleY(float s) { _scaleY += s; }
    void scaleZ(float s) { _scaleZ += s; }
    void rotate(Rotator r);
    void draw();
};

#endif
