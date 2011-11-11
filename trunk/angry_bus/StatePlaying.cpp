#include "StatePlaying.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Node.h"

StatePlaying::StatePlaying()
{
    {
        _uiRoot = new TransformationNode("background_playing");
        _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_playing"));
        _uiRoot->setPosition(160, 240, 0);
        _uiRoot->setScale(320, 480, 1.0);
    }
    
    {
        TransformationNode* n = new TransformationNode("sprite_bus");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_bus"));
        n->setPosition(80, 240, 0);
        n->setScale(160, 480, 1.0);
        _uiRoot->addChild(n);
    }
    
    {
        TransformationNode* n = new TransformationNode("button_back");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_back"));
        n->setPosition(16, 450, 0);
        n->setScale(32, 48, 1.0);
        _uiRoot->addChild(n);
    }
}

StatePlaying::~StatePlaying()
{
    _uiRoot->release();
    _uiRoot = 0;
}

void StatePlaying::render()
{
    _uiRoot->render();
}

void StatePlaying::update(float secondsElapsed)
{
    _uiRoot->breadth_first(&Entity::update);
}

bool StatePlaying::touchBegin(float x, float y)
{
    return _uiRoot->breadth_first(&Entity::touchBegin, x, y);
}

bool StatePlaying::touchMoved(float x, float y, float previousX, float previousY)
{
    return _uiRoot->breadth_first(&Entity::touchMoved, x, y, previousX, previousY);
}

bool StatePlaying::touchEnd(float x, float y)
{
    return _uiRoot->breadth_first(&Entity::touchEnd, x, y);
}

void StatePlaying::start()
{
    _uiRoot->setTransformation();
}