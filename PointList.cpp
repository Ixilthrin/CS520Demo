#include "PointList.h"
#include "main.h"

PointList::PointList(int size)
: _size(size), _scaleX(1.0), _scaleY(1.0), _scaleZ(1.0)
{
    _list = new Point[size];
}

PointList::PointList(const PointList& rhs)
{
    _size = rhs._size;
    _list = new Point[_size];
    for (int i = 0; i < _size; ++i)
    {
        _list[i] = rhs._list[i];
    }
}

PointList& PointList::operator=(const PointList& rhs)
{
    if (this != &rhs)
    {
        Point *newArray = new Point[rhs._size];
        for (int i = 0; i < rhs._size; ++i)
        {
            newArray[i] = rhs._list[i];
        }
        //delete [] _list;
        _list = newArray;
        _size = rhs._size;
    }
    return *this;
}

PointList::~PointList()
{
    delete [] _list;
};

void PointList::rotate(Rotator r)
{
    for (int i = 0; i < _size; ++i)
    {
        _list[i] = r.rotate(_list[i]);
    }
}


void PointList::draw()
{
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < _size; ++i)
    {
        glVertex3f(_list[i].x * _scaleX, _list[i].y * _scaleY, _list[i].z * _scaleZ);
    }
    glEnd();
}
