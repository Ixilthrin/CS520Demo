#include "Tube1.h"

#include "main.h"
#include "Point.h"
#include "Matrix.h"

Matrix getFrenetFrame(float t)
{
    Matrix m;
    
    Point C;
    C.x = 1.0 / cos(t);
    C.y = tan(t);
    C.z = t;
    
    Point T;
    T.x = (1.0 / cos(t)) * tan(t);
    T.y = (1.0 / cos(t)) * (1.0 / cos(t));
    T.z = 1.0;
    float TD = sqrt(T.x * T.x + T.y * T.y + T.z * T.z);
    T.x = T.x / TD;
    T.y = T.y / TD;
    T.z = T.z / TD;
    
    Point N;
    N.x = (1.0 / cos(t)) * (1.0 / cos(t)) * (1.0 / cos(t));
    N.y = 2.0 * (1.0 / cos(t)) * (1.0 / cos(t)) * tan(t);
    N.z = 0;
    float ND = sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
    N.x = N.x / ND;
    N.y = N.y / ND;
    N.z = N.z / ND;
    
    Point B;
    B.x = T.y * N.z - N.y * T.z;
    B.y = -(T.x * N.z - N.x * T.z);
    B.z = T.x * N.y - N.x * T.y;
    
    m.a1 = N.x;
    m.a2 = B.x;
    m.a3 = T.x;
    m.a4 = C.x;
    m.b1 = N.y;
    m.b2 = B.y;
    m.b3 = T.y;
    m.b4 = C.y;
    m.c1 = N.z;
    m.c2 = B.z;
    m.c3 = T.z;
    m.c4 = C.z;
    m.d1 = 0;
    m.d2 = 0;
    m.d3 = 0;
    m.d4 = 1.0;
    return m;
}

void drawTube()
{
    Point p1;
    p1.x = 0;
    p1.y = 0;
    p1.z = 0;
    Point p2;
    p2.x = 1.0;
    p2.y = 0.0;
    p2.z = 0.0;
    Point p3;
    p3.x = 1.0;
    p3.y = 0.2;
    p3.z = 1.0;
    Point p4;
    p4.x = 0.0;
    p4.y = 0.2;
    p4.z = 1.0;
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glVertex3f(p4.x, p4.y, p4.z);
    glEnd();
    
    int numberOfSteps = 10;
    for (int n = 0; n < numberOfSteps; ++n)
    {
        float t = ((float) n) / (float) numberOfSteps;
        Matrix m = getFrenetFrame(t);
        Point q1;
        Point q2;
        Point q3;
        Point q4;
        q1 = m.multiply(p1);
        q2 = m.multiply(p2);
        q3 = m.multiply(p3);
        q4 = m.multiply(p4);        
        glBegin(GL_LINE_LOOP);
        glVertex3f(q1.x, q1.y, q1.z);
        glVertex3f(q2.x, q2.y, q2.z);
        glVertex3f(q3.x, q3.y, q3.z);
        glVertex3f(q4.x, q4.y, q4.z);
        glEnd();
    }
}

Point getPointOnCurve(float t)
{
    Point p;
    p.x = 1.0 / cos(t);
    p.y = tan(t);
    p.z = t;
    return p;
}

void drawCurve()
{
    glBegin(GL_LINE_STRIP);
    int numberOfSteps = 10;
    for (int n = 0; n < numberOfSteps; ++n)
    {
        float t = ((float) n) / (float) numberOfSteps;
        Point p = getPointOnCurve(t);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
}

Tube1::Tube1(Point position)
: Model(position)
{
    _rotationalSpeedYaw = .5;
}

void Tube1::init()
{
}

void Tube1::draw()
{
    glColor3f(1.0, 1.0, 0.0);
    drawCurve();
    
    
    // Draw the profiles
    glColor3f(1.0, 0.0, 0.0);
    drawTube();
}
