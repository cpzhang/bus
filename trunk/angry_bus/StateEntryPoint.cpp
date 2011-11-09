#include "StateEntryPoint.h"
#include "EntityManager.h"
#include "Entity.h"

StateEntryPoint::StateEntryPoint()
{
    {
	_uiRoot = new TransformationNode<Entity>("background_entry_state");
	_uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_entry_state"));
	_uiRoot->setPosition(160, 240, 0);
	_uiRoot->setScale(320, 480, 1.0);
    }
    {
        TransformationNode<Entity>* n = new TransformationNode<Entity>("button_enter");
	n->setData(EntityManager::getInstancePtr()->getEntity("button_enter"));
	n->setPosition(160, 240, 0);
	n->setScale(32, 48, 1.0);
        _uiRoot->addChild(n);
    }
}

StateEntryPoint::~StateEntryPoint()
{
    _uiRoot->release();
}

void StateEntryPoint::render()
{
    _uiRoot->breadth_first(&Entity::render);
}

void StateEntryPoint::update(float secondsElapsed)
{
    _uiRoot->breadth_first(&Entity::update);
}

void StateEntryPoint::touchBegin(float x, float y)
{
    _uiRoot->breadth_first(&Entity::touchBegin, x, y);
}
void StateEntryPoint::touchMoved(float x, float y, float previousX, float previousY)
{
    _uiRoot->breadth_first(&Entity::touchMoved, x, y, previousX, previousY);
}
void StateEntryPoint::touchEnd(float x, float y)
{
    _uiRoot->breadth_first(&Entity::touchEnd, x, y);
}
