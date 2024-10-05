#include "Scene.h"
#include "View.h"
#include "Program.h"

Scene::Scene(Program *p)
: models(), view(0), program(p)
{
}

Scene::~Scene()
{
    vector<Model *>::iterator iter = models.begin();
    vector<Model *>::iterator end = models.end();
    for (; iter != end; ++iter)
    {
        delete (*iter);
    }
}
void Scene::init()
{
    vector<Model *>::iterator iter = models.begin();
    vector<Model *>::iterator end = models.end();
    for (; iter != end; ++iter)
    {
        (*iter)->init();
    }
}

void Scene::update(float elapsedTime, float deltaTime)
{
    vector<Model *>::iterator iter = models.begin();
    vector<Model *>::iterator end = models.end();
    for (; iter != end; ++iter)
    {
        (*iter)->update(elapsedTime, deltaTime);
    }
    
    // Very simple collsion detection
    for (int i = 0; i < models.size() - 1; ++i)
    {
        Model *currentModel = models[i];
        for (int j = i+1; j < models.size(); ++j)
        {
            Model *targetModel = models[j];
            if (targetModel->getCheckCollisions() || currentModel->getCheckCollisions())
            {
                if (currentModel->intersects(targetModel))
                {
                    if (targetModel->getRespondsToCollisions() && currentModel->getCheckCollisions())
                    {
                        targetModel->bump(currentModel->getPosition());
                    }
                    if (currentModel->getRespondsToCollisions() && targetModel->getCheckCollisions())
                    {
                        currentModel->bump(targetModel->getPosition());
                    }
                }
            }
        }
        if (view->intersects(currentModel) && currentModel->getCheckCollisions())
        {
            view->bump(currentModel->getPosition());
            if (currentModel->getRespondsToCollisions())
            {
                currentModel->bump(view->getPosition());
            }
        }
    }
    
}

void Scene::draw()
{
    glColor3f(1.0, 1.0, 1.0);
    
    vector<Model *>::iterator iter = models.begin();
    vector<Model *>::iterator end = models.end();
    for (; iter != end; ++iter)
    {
        (*iter)->projectShadow();
        (*iter)->doPreTransformations();
        (*iter)->draw();
        (*iter)->doPostTransformations();
    }
}