#include "StateEntryPoint.h"
#include "EntityManager.h"
#include "Entity.h"

StateEntryPoint::StateEntryPoint()
{
    {
        _uiRoot = new TransformationNode("background_entry_state");
        _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_entry_state"));
        _uiRoot->setPosition(160, 240, 0);
        _uiRoot->setScale(320, 480, 1.0);
    }
    {
        TransformationNode* n = new TransformationNode("button_enter");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_enter"));
        n->setPosition(160, 240, 0);
        n->setScale(32, 48, 1.0);
        _uiRoot->addChild(n);
    }
    {
        TransformationNode* n = new TransformationNode("button_score");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_score"));
        n->setPosition(30, 275, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        TransformationNode* n = new TransformationNode("button_achievement");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_achievement"));
        n->setPosition(30, 195, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        TransformationNode* n = new TransformationNode("button_network");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_network"));
        n->setPosition(30, 35, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        TransformationNode* n = new TransformationNode("button_setting");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_setting"));
        n->setPosition(30, 445, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        TransformationNode* n = new TransformationNode("background_setting");
        n->setData(EntityManager::getInstancePtr()->getEntity("background_setting"));
        n->setPosition(80, 445, 0);
        n->setScale(64, 32, 1.0);
        _uiRoot->addChild(n);
    }
}

StateEntryPoint::~StateEntryPoint()
{
    _uiRoot->release();
}

void StateEntryPoint::render()
{
    //_uiRoot->breadth_first(&Entity::render);
    _uiRoot->render();
}

void StateEntryPoint::update(float secondsElapsed)
{
    _uiRoot->breadth_first(&Entity::update);
}

bool StateEntryPoint::touchBegin(float x, float y)
{
    return _uiRoot->breadth_first(&Entity::touchBegin, x, y);
}
bool StateEntryPoint::touchMoved(float x, float y, float previousX, float previousY)
{
    return _uiRoot->breadth_first(&Entity::touchMoved, x, y, previousX, previousY);
}
bool StateEntryPoint::touchEnd(float x, float y)
{
    return _uiRoot->breadth_first(&Entity::touchEnd, x, y);
}

void StateEntryPoint::start()
{
    _uiRoot->setTransformation();
}