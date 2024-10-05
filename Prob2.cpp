#include "Prob2.h"

#include "util.h"
#include "Sphere2.h"
#include "Sphere1.h"
#include "Torus1.h"

static bool enableFog;

Prob2::Prob2()
: Program()
{
    Point p;
    p.z = 100.0;
    p.y = 10.0;
    view = new View(p, 3.0 * M_PI / 2.0);  // look at the origin
    scene = new Scene();
    view->setScene(scene);
}

void Prob2::setup()
{
    enableFog = false;
    Point position;
    //scene->addModel(new Sphere2(Point(0.0, 0.0, 0.0)));
    scene->addModel(new Torus1(Point(50.0, 0.0, 0.0)));
    //scene->addModel(new Sphere1(Point(0.0f, 50.0f, 10.0f)));
    
    vector<Model *> models = scene->getModels();
    vector<Model *>::iterator iter = models.begin();
    vector<Model *>::iterator end = models.end();
    for (; iter != end; ++iter)
    {
        (*iter)->setScene(scene);
    }
    
    
    Program::setup();
    scene->init();
    
    // Light
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { .1, .1, .1, 1.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void Prob2::reshape(int w, int h)
{
    float aspectRatio = (float) w / (float) h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-2.0 * aspectRatio, 2.0 * aspectRatio, -2.0, 2.0, 5.0, 100.0);
    gluPerspective(60.0, aspectRatio, 2.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static bool stillDrawing = false;
void Prob2::update(int elapsedTime, int deltaTime)
{
    if (stillDrawing)
        return;
    view->update(elapsedTime, deltaTime);
    scene->update(elapsedTime, deltaTime);
}

void Prob2::display()
{
    if (stillDrawing)
        return;
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    stillDrawing = true;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (enableFog == true)
    {
        // Try some fog
        glEnable(GL_FOG);
        GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
        GLint fogMode = GL_EXP;
        glFogi(GL_FOG_MODE, fogMode);
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.01);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
        glFogf(GL_FOG_START, 1.0);
        glFogf(GL_FOG_END, 5.0);
        glClearColor(0.5, 0.5, 0.7, 1.0);  
    }
    else
    {
        glDisable(GL_FOG);
        
        // Close to the color of sky
        glClearColor(0.3, 0.2, 0.7, 0.0);
    }
    
    // The light
    GLfloat light_position[] = { 0.0, 100.0, 50.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    view->set();
    scene->draw();
    
    //drawText(-4, 3, "Press 'c' for surfaces");
    glutSwapBuffers();    
    stillDrawing = false;
    glFlush();
    glutTimerFunc(18, displayi, 0);
}

void Prob2::keyboard(unsigned char key, int x, int y)
{
    printf("Prob2::keyboard\n");
    switch (key) {
        case 'm':
        {
            if (enableFog == false)
                enableFog = true;
            else
                enableFog = false;
        }
    }
    view->keyboard(key, x, y);
}

void Prob2::keyboardUp(unsigned char key, int x, int y)
{
    view->keyboardUp(key, x, y);
}

void Prob2::keyboardDown(unsigned char key, int x, int y)
{
    view->keyboardDown(key, x, y);
}

void Prob2::motion(int x, int y)
{
    view->motion(x, y);
}

void Prob2::mouse(int button, int state, int x, int y)
{
    view->mouse(button, state, x, y);
}
