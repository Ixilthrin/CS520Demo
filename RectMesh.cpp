#include "RectMesh.h"

#include "main.h"

RectMesh::RectMesh(int divisions, Point position, int width)
: Model(position), _divisions(divisions), _width(width)
{
}

RectMesh::~RectMesh()
{
}

void RectMesh::init()
{
    _vertices = new Vertex*[(_divisions + 1) * (_divisions + 1)];
    float divisionWidth = _width / _divisions;
    for (int i = 0; i < _divisions + 1; ++i)
    {
        for (int j = 0; j < _divisions + 1; ++j)
        {
            Vertex *v = new Vertex();
            v->x = j * divisionWidth;
            v->z = i * divisionWidth;
            v->y = 0;
        }
    }
}

void RectMesh::update(int elapsedTime, int deltaTime)
{
}

void RectMesh::draw()
{
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < _divisions; ++i)
    {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j < _divisions; ++j)
        {
            //glVertex3f(_vertices[i]->x, _vertices[i]->y, _vertices[i]->z);
        }
        glEnd();
    }
}