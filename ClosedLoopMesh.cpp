#include "ClosedLoopMesh.h"
#include "main.h"

ClosedLoopMesh::ClosedLoopMesh(int size)
: _size(size)
{
    _list = new PointList*[size];
}

ClosedLoopMesh::~ClosedLoopMesh()
{
    for (int i = 0; i < _size; ++i)
    {
        delete _list[i];
    }
}

void ClosedLoopMesh::draw()
{
    for (int i = 0; i < _size - 1; ++i)
    {
        int numPoints = _list[i]->size();
        //printf("numPoints = %d\n", numPoints);
        for (int j = 0; j < numPoints - 1; ++j)
        {
            Point P1 = _list[i]->getPoint(j);
            //printf("P1(%d).x = %f\n", j, P1.x);
            Point P2 = _list[i]->getPoint(j + 1);
            Point P3 = _list[i + 1]->getPoint(j + 1);
            Point P4 = _list[i + 1]->getPoint(j);
            glBegin(GL_LINE_LOOP);
            glVertex3f(P1.x, P1.y, P1.z);
            glVertex3f(P2.x, P2.y, P2.z);
            glVertex3f(P3.x, P3.y, P3.z);
            glVertex3f(P4.x, P4.y, P4.z);
            glEnd();
        }                   
    }
}
