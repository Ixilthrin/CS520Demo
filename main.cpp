#include "main.h"

#include "CS520Project.h"
#include "Program.h"
#include "util.h"

static bool fullScreen = false;
Program *theProgram;
static GLint win = 0;

void init(void)
{
    theProgram->setup();
}

void cleanUp(void)
{
    glutDestroyWindow(win);
}

void displayi(int)
{
    glutPostRedisplay();
}

void display()
{
    static int previousTime = getMilliseconds();
    int currentTime = getMilliseconds();
    int deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    //printf("%d\n", deltaTime);
    
    theProgram->update(currentTime, deltaTime);
    theProgram->display();
    //glutTimerFunc(16, displayi, 0);
    //glutTimerFunc(25, displayi, 0);
}

void reshape(int w, int h)
{
    theProgram->reshape(w, h);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'f':
            if (fullScreen)
            {
                glutReshapeWindow(500, 500);
                glutPositionWindow(100, 100);
                fullScreen = false;
            }
            else
            {
                glutFullScreen();
                fullScreen = true;
            }
            break;
        case 27:
            exit(0);
            cleanUp();
            break;
        default:
            theProgram->keyboard(key, x, y);
    }
}

void keyboardUp(unsigned char key, int x, int y)
{
    theProgram->keyboardUp(key, x, y);
}

void motion(int x, int y)
{
    theProgram->motion(x, y);
}

void mouse(int button, int state, int x, int y)
{
    theProgram->mouse(button, state, x, y);
}


int main(int argc, char** argv)
{    
    // Seed the random number generator
    srand(time(0));
    
    // Start the main program where most of the functionality is defined
    theProgram = new CS520Project();
    //theProgram = new Prob2();
    //theProgram = new Prob5();
    
    // Set up OpenGL
    glutInit(&argc, argv);
    printf("Called glutInit\n");
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    win = glutCreateWindow (argv[0]);
    //glutIdleFunc(display);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc (keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    // Initialize the "OpenGL Extension Wrangler" library
#ifndef __APPLE__
    glewInit();
#endif
    init();
    glutMainLoop();
    return 0;
}
