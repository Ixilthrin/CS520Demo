#ifndef __CLOSEDLOOPMESH_H__
#define __CLOSEDLOOPMESH_H__

#include "PointList.h"

class ClosedLoopMesh
{
  private:
    int _size;
    PointList **_list;
  public:
    ClosedLoopMesh(int size);
    ~ClosedLoopMesh();
    int size() { return _size; }
    void setPointList(int index, PointList *list)
    {
        _list[index] = list;
    }
    void draw();
};

#endif
