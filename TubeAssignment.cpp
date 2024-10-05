#include "TubeAssignment.h"

#include "util.h"
#include "Tube1.h"
#include <string.h>

void drawText(int x, int y, char *string)
{
    int len, i;
    
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}


TubeAssignment::TubeAssignment()
: Program()
{
    Point p;
    printf("p.x = %f\n", p.x);
    p.z = 5.0;
    view = new View(p, 0.0);
    scene = new Scene();
}

void TubeAssignment::setup()
{
    Point position;
    scene->addModel(new Tube1(Point(0.0f, 0.0f, 10.0f)));
    Program::setup();
}

void TubeAssignment::reshape(int w, int h)
{
    float aspectRatio = (float) w / (float) h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TubeAssignment::update(int elapsedTime, int deltaTime)
{
    view->update(elapsedTime, deltaTime);
    scene->update(elapsedTime, deltaTime);
}

static bool stillDrawing = false;
void TubeAssignment::display()
{
    if (stillDrawing)
        return;
    stillDrawing = true;
    view->set();
    scene->draw();
    
    //drawText(-4, 3, "Press 'c' for surfaces");
    glutSwapBuffers();
    glFlush();
    stillDrawing = false;
    glutTimerFunc(1, displayi, 0);
}

void TubeAssignment::keyboard(unsigned char key, int x, int y)
{
    view->keyboard(key, x, y);
}

void TubeAssignment::keyboardUp(unsigned char key, int x, int y)
{
    view->keyboardUp(key, x, y);
}

void TubeAssignment::keyboardDown(unsigned char key, int x, int y)
{
    view->keyboardDown(key, x, y);
}

void TubeAssignment::motion(int x, int y)
{
    view->motion(x, y);
}

void TubeAssignment::mouse(int button, int state, int x, int y)
{
    view->mouse(button, state, x, y);
}
