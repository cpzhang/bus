#include "StateAboutUs.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Node.h"

StateAboutUs::StateAboutUs()
{
    {
        _uiRoot = new TransformationNode("background_contact_us");
        _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_contact_us"));
        _uiRoot->setPosition(160, 240, 0);
        _uiRoot->setScale(320, 480, 1.0);
    }
    {
        TransformationNode* n = new TransformationNode("button_back");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_back"));
        n->setPosition(16, 450, 0);
        n->setScale(32, 48, 1.0);
        _uiRoot->addChild(n);
    }
    
}

StateAboutUs::~StateAboutUs()
{
    _uiRoot->release();
    _uiRoot = 0;
}

void StateAboutUs::render()
{
    _uiRoot->render();
}

void StateAboutUs::update(float secondsElapsed)
{
    _uiRoot->breadth_first(&Entity::update);
}

bool StateAboutUs::touchBegin(float x, float y)
{
    return _uiRoot->breadth_first(&Entity::touchBegin, x, y);
}

bool StateAboutUs::touchMoved(float x, float y, float previousX, float previousY)
{
    return _uiRoot->breadth_first(&Entity::touchMoved, x, y, previousX, previousY);
}

bool StateAboutUs::touchEnd(float x, float y)
{
    return _uiRoot->breadth_first(&Entity::touchEnd, x, y);
}

void StateAboutUs::start()
{
    _uiRoot->setTransformation();
}