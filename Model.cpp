#include "Model.h"

#include "main.h"
#include "Scene.h"
#include "Program.h"

int Model::detail(2);  // Change to 1, 2, or 3 to see different levels of detail

Model::Model(Point position)
: _position(position), _yaw(0), _pitch(0), _roll(0),
  _linearSpeedX(0), _linearSpeedY(0), _linearSpeedZ(0),
  _rotationalSpeedYaw(0), _rotationalSpeedPitch(0), 
  _rotationalSpeedRoll(0), _checkCollisions(0), 
  _respondsToCollisions(0), _showWireFrame(0), _scene(0),
  _showTextures(1)
{
    _initialPosition.x = position.x;
    _initialPosition.y = position.y;
    _initialPosition.z = position.z;
    _initialYaw = 0;
    _initialRoll = 0;
    _initialPitch = 0;
    falling = 1.0;
    shadowMatrix[0] = 1;
    shadowMatrix[10] = 1;
    shadowMatrix[15] = 1;
    // set shadowMatrix[7] at time when we know the light position.
}

Model::~Model()
{
    delete _scene;
}

void Model::update(int elapsedTime, int deltaTime)
{
    _position.x += (float) deltaTime * _linearSpeedX;
    _position.y += (float) deltaTime * _linearSpeedY;
    _position.z += (float) deltaTime * _linearSpeedZ;
    _yaw += (float) deltaTime * _rotationalSpeedYaw;
    _pitch += (float) deltaTime * _rotationalSpeedPitch;
    _roll += (float) deltaTime * _rotationalSpeedRoll;
    
    if (_position.x > 110 || _position.z > 110 
        || _position.x < -110 || _position.z < -110)
    {
        _position.y -= falling;
        falling += 1.0;
    }
    else
    {
        falling = 1;
    }
    
    if (_position.y < -100)
    {
        falling = 0;
        _position.y = 75.0;
        _position.x = _initialPosition.x;
        _position.z = _initialPosition.z;
        _yaw = _initialYaw;
        _pitch = _initialPitch;
        _roll = _initialRoll;
        _linearSpeedZ = 0.0; 
        _linearSpeedX = 0.0;
        _rotationalSpeedRoll = 0.0;
        _rotationalSpeedYaw = 0.0;
        _rotationalSpeedPitch = 0.0;
    }
}

void Model::projectShadow()
{
    if (!_projectShadow)
        return;
    
    if (_scene && _scene->getProgram()->lightingEnabled() 
        && _scene->getProgram()->shadowsEnabled()
        && !_scene->getProgram()->wireFrameEnabled())
    {
        glPolygonOffset(-1.0, -1.0);
        glEnable(GL_POLYGON_OFFSET_FILL);
        Point lightPosition = _scene->getProgram()->getLightPosition0();
        shadowMatrix[7] = -1.0 / lightPosition.y;
        glPushMatrix();
        glTranslatef(lightPosition.x, 0, lightPosition.z);
        glMultMatrixf(shadowMatrix);
        glTranslatef(-lightPosition.x, -0, -lightPosition.z);
        glDisable(GL_LIGHTING);
        glColor3f(0, 0, 0);
        doPreTransformations();
        drawProjectionShadow();
        doPostTransformations();
        glPopMatrix();
        glEnable(GL_LIGHTING);
        glDisable(GL_POLYGON_OFFSET_FILL);
    }
}

void Model::doPreTransformations()
{
    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(_roll, 0.0, 0.0, 1.0);
    glRotatef(_pitch, 1.0, 0.0, 0.0);
    glRotatef(_yaw, 0.0, 1.0, 0.0);
}

void Model::doPostTransformations()
{
    glPopMatrix();
}


bool Model::intersects(Model *model)
{
    float modelRadius = model->getRadius();
    Point modelPosition = model->getPosition();
    float x2 = _position.x - modelPosition.x;
    float y2 = _position.y - modelPosition.y;
    float z2 = _position.z - modelPosition.z;
    float distance = sqrt(x2*x2 + y2*y2 + z2*z2);
    
    return distance < _radius + modelRadius;
}

bool Model::collided()
{
    vector<Model *> models = _scene->getModels();
    vector<Model *>::iterator iter = models.begin();
    vector<Model *>::iterator end = models.end();
    for (; iter != end; ++iter)
    {
        if (intersects(*iter))
        {
            return true;
        }
    }
    return false;
}

// Override this to respond to viewer bumping the model
void Model::bump(Point direction)
{
}

void Model::reset()
{
    _position = _initialPosition;
    _linearSpeedX = 0;
    _linearSpeedY = 0;
    _linearSpeedZ = 0;
    _rotationalSpeedYaw = 0;
    _rotationalSpeedPitch = 0;
    _rotationalSpeedRoll = 0;
}
