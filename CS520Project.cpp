#include "CS520Project.h"

#include "util.h"
#include "Sphere1.h"
#include "Tube1.h"
#include "Checker1.h"
#include "Model.h"
#include "Shader1.h"
#include "Shader2.h"
#include "Torus1.h"
#include "Pawn.h"
#include "King.h"
#include "Rook.h"
#include "Queen.h"
#include "Bishop.h"

CS520Project::CS520Project()
: Program(), showWireFrame(0), enableLight(1), 
  enableFog(0), enableShadows(0), showTextures(1),
  enableFlashlightMode(0)
{
    Point p;
    p.z = 100.0;
    p.y = 10.0;
    view = new View(p, 3.0 * M_PI / 2.0);  // look at the origin
    scene = new Scene(this);
    view->setScene(scene);
    view->setProgram(this);
    scene->setView(view);
}

void CS520Project::setup()
{
    Point position, a8(-87.0, 14.7, 87.5), b8(-87.0, 14.7, 62.5), c8(-87.0, 14.7, 37.5), d8(-87.0, 14.7, 12.5),
    e8(-87.0, 14.7, -12.5), f8(-87.0, 14.7, -37.5), g8(-87.0, 14.7, -62.5), h8(-87.0, 14.7, -87.5),
        a7(-62.0, 14.7, 87.5), b7(-62.0, 14.7, 62.5), c7(-62.0, 14.7, 37.5), d7(-62.0, 14.7, 12.5),
    e7(-62.0, 14.7, -12.5), f7(-62.0, 14.7, -37.5), g7(-62.0, 14.7, -62.5), h7(-62.0, 14.7, -87.5),
        a6(-37.0, 14.7, 87.5), b6(-37.0, 14.7, 62.5), c6(-37.0, 14.7, 37.5), d6(-37.0, 14.7, 12.5),
    e6(-37.0, 14.7, -12.5), f6(-37.0, 14.7, -37.5), g6(-37.0, 14.7, -62.5), h6(-37.0, 14.7, -87.5),
        a5(-12.0, 14.7, 87.5), b5(-12.0, 14.7, 62.5), c5(-12.0, 14.7, 37.5), d5(-12.0, 14.7, 12.5),
    e5(-12.0, 14.7, -12.5), f5(-12.0, 14.7, -37.5), g5(-12.0, 14.7, -62.5), h5(-12.0, 14.7, -87.5),
        a4(13.0, 14.7, 87.5), b4(13.0, 14.7, 62.5), c4(13.0, 14.7, 37.5), d4(13.0, 14.7, 12.5),
    e4(13.0, 14.7, -12.5), f4(13.0, 14.7, -37.5), g4(13.0, 14.7, -62.5), h4(13.0, 14.7, -87.5),
        a3(38.0, 14.7, 87.5), b3(38.0, 14.7, 62.5), c3(38.0, 14.7, 37.5), d3(38.0, 14.7, 12.5),
    e3(38.0, 14.7, -12.5), f3(38.0, 14.7, -37.5), g3(38.0, 14.7, -62.5), h3(38.0, 14.7, -87.5),
        a2(63.0, 14.7, 87.5), b2(63.0, 14.7, 62.5), c2(63.0, 14.7, 37.5), d2(63.0, 14.7, 12.5),
    e2(63.0, 14.7, -12.5), f2(63.0, 14.7, -37.5), g2(63.0, 14.7, -62.5), h2(63.0, 14.7, -87.5),
        a1(88.0, 14.7, 87.5), b1(88.0, 14.7, 62.5), c1(88.0, 14.7, 37.5), d1(88.0, 14.7, 12.5),
    e1(88.0, 14.7, -12.5), f1(88.0, 14.7, -37.5), g1(88.0, 14.7, -62.5), h1(88.0, 14.7, -87.5);


    scene->addModel(new Checker1(Point(0.0, 0.0, 0.0)));
    scene->addModel(new Sphere1(Point(0.0f, 50.0f, 10.0f)));
    scene->addModel(new Torus1(Point(0, 5, -60)));
    explosion = new Shader2(Point(25.0, 10.0, 0.0));
    scene->addModel(explosion);
    
    scene->addModel(new Shader1(Point(0.0, 10.0, 0.0)));
    //white
    scene->addModel(new Pawn(h7, ChessPiece::WHITE));
    scene->addModel(new Pawn(g7, ChessPiece::WHITE));
    scene->addModel(new Pawn(f7, ChessPiece::WHITE));
    scene->addModel(new Pawn(e7, ChessPiece::WHITE));
    scene->addModel(new Pawn(d7, ChessPiece::WHITE));
    scene->addModel(new Pawn(c7, ChessPiece::WHITE));
    scene->addModel(new Pawn(b7, ChessPiece::WHITE));
    scene->addModel(new Pawn(a7, ChessPiece::WHITE));
    scene->addModel(new Rook(h8, ChessPiece::WHITE));
    scene->addModel(new Rook(g8, ChessPiece::WHITE));
    scene->addModel(new Bishop(f8, ChessPiece::WHITE));
    scene->addModel(new King(e8, ChessPiece::WHITE));
    scene->addModel(new Queen(d8, ChessPiece::WHITE));
    scene->addModel(new Bishop(c8, ChessPiece::WHITE));
    scene->addModel(new Rook(b8, ChessPiece::WHITE));
    scene->addModel(new Rook(a8, ChessPiece::WHITE));
    //black

    scene->addModel(new Pawn(h2, ChessPiece::BLACK));
    scene->addModel(new Pawn(g2, ChessPiece::BLACK));
    scene->addModel(new Pawn(f2, ChessPiece::BLACK));
    scene->addModel(new Pawn(e2, ChessPiece::BLACK));
    scene->addModel(new Pawn(d2, ChessPiece::BLACK));
    scene->addModel(new Pawn(c2, ChessPiece::BLACK));
    scene->addModel(new Pawn(b2, ChessPiece::BLACK));
    scene->addModel(new Pawn(a2, ChessPiece::BLACK));
    scene->addModel(new Rook(h1, ChessPiece::BLACK));
    scene->addModel(new Rook(g1, ChessPiece::BLACK));
    scene->addModel(new Bishop(f1, ChessPiece::BLACK));
    scene->addModel(new King(e1, ChessPiece::BLACK));
    scene->addModel(new Queen(d1, ChessPiece::BLACK));
    scene->addModel(new Bishop(c1, ChessPiece::BLACK));
    scene->addModel(new Rook(b1, ChessPiece::BLACK));
    scene->addModel(new Rook(a1, ChessPiece::BLACK));     
    
    // Set the Scene object for all of the models
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

void CS520Project::reshape(int w, int h)
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
void CS520Project::update(int elapsedTime, int deltaTime)
{
    if (stillDrawing)
        return;
    view->update(elapsedTime, deltaTime);
    scene->update(elapsedTime, deltaTime);
}

void CS520Project::display()
{
    if (stillDrawing)
        return;
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    stillDrawing = true;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (enableFog && !enableShadows && !showWireFrame)
    {
        // Try some fog
        glEnable(GL_FOG);
        GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
        GLint fogMode = GL_EXP;
        glFogi(GL_FOG_MODE, fogMode);
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.02);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
        glFogf(GL_FOG_START, 1.0);
        glFogf(GL_FOG_END, 5.0); 
        if (enableShadows)
        {
            glClearColor(0, 0, 0, 0);
        }
        else
        {
            // Close to the color of sky
            glClearColor(0.5, 0.5, 0.7, 1.0);
        }
    }
    else
    {
        glDisable(GL_FOG);
        
        if (enableShadows)
        {
            glClearColor(0, 0, 0, 0);
        }
        else
        {
            // Close to the color of sky
            glClearColor(0.3, 0.2, 0.7, 0.0);
        }
    }
    
    // The light
    if (enableFlashlightMode)
    {
        Point viewPoint = view->getPosition();
        lightPosition0.x = viewPoint.x;
        lightPosition0.y = viewPoint.y+20;
        lightPosition0.z = viewPoint.z;
    }
    else
    {
        lightPosition0.x = 0;
        lightPosition0.y = 80.0;
        lightPosition0.z = 80.0;
    }
    GLfloat light_position[] = { lightPosition0.x, lightPosition0.y, lightPosition0.z, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    if (enableLight)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
    
    view->set();
    scene->draw();
    
    //drawText(-4, 3, "Press 'c' for surfaces");
    glutSwapBuffers();    
    stillDrawing = false;
    glFlush();
    glutTimerFunc(18, displayi, 0);
}

void CS520Project::keyboard(unsigned char key, int x, int y)
{
    printf("CS520Project::keyboard\n");
    switch (key) {
        case 'm':
        {
            enableFog = !enableFog;
        }
            break;
        case 'n':
        {
            showWireFrame = !showWireFrame;
            vector<Model *> models = scene->getModels();
            vector<Model *>::iterator iter = models.begin();
            vector<Model *>::iterator end = models.end();
            for (; iter != end; ++iter)
            {
                (*iter)->setShowWireFrame(showWireFrame);
            }
        }
            break;
        case 'o':
            view->fromAbove = !(view->fromAbove);
            break;
        case 'p':
            enableFlashlightMode = !enableFlashlightMode;
            break;
        case 'l':
            enableLight = !enableLight;
            break;
        case 'r':
        {
            showTextures = !showTextures;
            vector<Model *> models = scene->getModels();
            vector<Model *>::iterator iter = models.begin();
            vector<Model *>::iterator end = models.end();
            for (; iter != end; ++iter)
            {
                (*iter)->reset();
            }
        }
        case 't':
        {
            showTextures = !showTextures;
            vector<Model *> models = scene->getModels();
            vector<Model *>::iterator iter = models.begin();
            vector<Model *>::iterator end = models.end();
            for (; iter != end; ++iter)
            {
                (*iter)->setShowTextures(showTextures);
            }
        }
            break;
        case 'x':
            enableShadows = !enableShadows;
            break;
    }
    view->keyboard(key, x, y);
}

void CS520Project::keyboardUp(unsigned char key, int x, int y)
{
    printf("keyboardUp\n");
    view->keyboardUp(key, x, y);
}

void CS520Project::keyboardDown(unsigned char key, int x, int y)
{
    view->keyboardDown(key, x, y);
}

void CS520Project::motion(int x, int y)
{
    view->motion(x, y);
}

void CS520Project::mouse(int button, int state, int x, int y)
{
    view->mouse(button, state, x, y);
}
