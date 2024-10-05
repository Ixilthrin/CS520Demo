#include "View.h"
#include "main.h"
#include "Program.h"

static float speed = 0;
static float accel = 0.6;
static float falling = 1.0;

void View::update(int elapsedTime, int deltaTime)
{
    
    _position.x += (float) deltaTime * _linearSpeedX;
    _position.z += (float) deltaTime * _linearSpeedZ;
    
    if(rotatingYaw)
    {
        _yaw += (float) deltaTime * rotationalSpeed * (float) rotatingYaw;
        while (_yaw > 2.0 * M_PI)
        {
            _yaw -= 2.0 * M_PI;
        }
        while (_yaw < -2.0 * M_PI)
        {
            _yaw += 2.0 * M_PI;
        }
    }
    if (moving)
    {
        float distance = (float) deltaTime * linearSpeed * (float) moving;
        _position.x += distance * cos(_yaw);
        _position.z += distance * sin(_yaw);
        
        //if (collided())
        //{
        //    _position.x -= distance * cos(_yaw);
        //    _position.z += distance * sin(_yaw);
        //}
    }
    
    // Falling
    if (_position.x > 110 || _position.z > 110 
        || _position.x < -110 || _position.z < -110)
    {
        //speed = 0;
        _position.y -= falling;
        falling += 1.0;
        _linearSpeedX = 0;
        _linearSpeedZ = 0;
    }
    else
    { 
        falling = 1;
    }
    
    // Come back
    if (_position.y < -300)
    {
        //falling = 0;
        speed = 0;
        _position.y = 100.0;
        _position.x = 0.0;
        _position.z = 50.0;
        return;
    }
    
    if (_position.y < 10)
    {
        if (speed > -2)
        {
            return;
        }
        _position.y = 10;
        speed = -speed - 2;
        _position.y += speed;
        speed -= accel;
    }
    else
    {
        _position.y += speed;
        speed -= accel;
    }
}

void View::set()
{
    if (fromAbove)
    {
        glLoadIdentity();
        gluLookAt(0, 200, 0, 
                  0, 0, 0, 
                  0.0, 0.0, 1.0);
        glPushMatrix();
        glTranslatef(_position.x, _position.y, _position.z);
        glRotatef(90, 0.0, 1.0, 0.0);
        glRotatef(-_yaw * 180 / M_PI, 0.0, 1.0, 0.0);
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 0);
        glBegin(GL_TRIANGLES);
        glNormal3f(0, 1, 0);
        glVertex3f(5.0, 1.0, 0.0);
        glNormal3f(0, 1, 0);
        glVertex3f(-5.0, 1.0, 0.0);
        glNormal3f(0, 1, 0);
        glColor3f(0, 0, 1);
        glVertex3f(0.0, 1.0, 10.0);
        glEnd();
        glPopMatrix();
        if (program && program->lightingEnabled())
        {
            glEnable(GL_LIGHTING);
        }
    }
    else
    {
        glLoadIdentity();
        gluLookAt(_position.x, _position.y, _position.z, 
                  _position.x + cos(_yaw), _position.y, _position.z + sin(_yaw), 
                  0.0, 1.0, 0.0);
        
        // Use the following to see an interesting camera control effect.
        //gluLookAt(_position.x, _position.y, _position.z, 
        //sin(_yaw), 0.0, -cos(_yaw), 0.0, 1.0, 0.0);
    }
}

void View::keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'a':
            rotatingYaw = -1;
            break;
        case 'd':
            rotatingYaw = 1;
            break;
        case 's':
            moving = -1;
            break;
        case 'w':
            moving = 1;
            break;
        case 'c':
            lockPosition = !lockPosition;
            break;
    }
}

void View::keyboardUp(unsigned char key, int x, int y)
{
    switch (key) {
        case 'a':
            rotatingYaw = 0;
            break;
        case 'd':
            rotatingYaw = 0;
            break;
        case 's':
            _linearSpeedX = 0;
            _linearSpeedZ = 0;
            moving = 0;
            break;
        case 'w':
            _linearSpeedX = 0;
            _linearSpeedZ = 0;
            moving = 0;
            break;
    }
}

void View::keyboardDown(unsigned char key, int x, int y)
{
}

void View::motion(int x, int y)
{
}

void View::mouse(int button, int state, int x, int y)
{
}

bool View::intersects(Model *model)
{
    float modelRadius = model->getRadius();
    if (modelRadius <= 0.0)
    {
        return false;
    }
    Point modelPosition = model->getPosition();
    float x2 = _position.x - modelPosition.x;
    float y2 = _position.y - modelPosition.y;
    float z2 = _position.z - modelPosition.z;
    float distance = sqrt(x2*x2 + y2*y2 + z2*z2);
    
    return distance < modelRadius + 5.0;
}

bool View::collided()
{
    vector<Model *> models = _scene->getModels();
    vector<Model *>::iterator iter = models.begin();
    vector<Model *>::iterator end = models.end();
    
    bool intersected = false;
    for (; iter != end; ++iter)
    {
        if (intersects(*iter))
        {
            (*iter)->bump(_position);
            intersected = true;
        }
    }
    return intersected;
}

void View::bump(Point direction)
{ 
    if (lockPosition)
        return;
    float speed = .04;
    float deltaX = _position.x - direction.x;
    float deltaZ = _position.z - direction.z;
    float theta = atan2(deltaZ, deltaX);
    if (theta < 0.0)
    {
        theta = 2.0 * M_PI + theta;
    }
    _linearSpeedX = speed * cos(theta); 
    _linearSpeedZ = speed * sin(theta);
}
