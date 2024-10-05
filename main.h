#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "math.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif


using namespace std;

void displayi(int);
