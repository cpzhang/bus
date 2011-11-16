#include "StateAboutUs.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Node.h"
#include "NodeManager.h"
#include "ButtonCallbackManager.h"

StateAboutUs::StateAboutUs()
{
    {
        _uiRoot = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "background_contact_us");
        _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_contact_us"));
        _uiRoot->setPosition(160, 240, 0);
        _uiRoot->setScale(320, 480, 1.0);
    }
    {
        Node* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_back");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_back"));
	n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to entry point state"));
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
    if (1) {
        return _uiRoot->touchBegin(x, y);
    }
    return _uiRoot->breadth_first(&Entity::touchBegin, x, y);
}

bool StateAboutUs::touchMoved(float x, float y, float previousX, float previousY)
{
   if (1) {
        return _uiRoot->touchMoved(x, y, previousX, previousY);
    }
 
    return _uiRoot->breadth_first(&Entity::touchMoved, x, y, previousX, previousY);
}

bool StateAboutUs::touchEnd(float x, float y)
{
    if (1) {
        return _uiRoot->touchEnd(x, y);
    }

    return _uiRoot->breadth_first(&Entity::touchEnd, x, y);
}

void StateAboutUs::start()
{
    _uiRoot->setTransformation();
}
