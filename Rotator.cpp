#include "Rotator.h"
#include "main.h"

Rotator::Rotator(int axis, float angle)
: _axis(axis), _angle(angle)
{
    _cosine = cos(angle);
    _sine = sin(angle);
}

Rotator::~Rotator()
{
}

Point Rotator::rotate(Point p)
{
    Point q;
    if (_axis = X_AXIS)
    {
        q.x = p.x;
        q.y = _cosine * p.y - _sine * p.z;
        q.z = _sine * p.y + _cosine * p.z;
    }
    else if (_axis = Y_AXIS)
    {
        q.x = _cosine * p.x + _sine * p.z;
        q.y = p.y;
        q.z = -_sine * p.x + _cosine * p.z;
    }
    else if (_axis = Z_AXIS)
    {
        q.x = _cosine * p.x - _sine * p.y;
        q.y = _sine * p.x + _cosine * p.y;
        q.z = p.z;
    }
    return q;
}
