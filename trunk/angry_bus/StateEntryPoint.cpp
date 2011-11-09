#include "StateEntryPoint.h"
#include "EntityManager.h"
#include "Entity.h"

StateEntryPoint::StateEntryPoint()
{
    _uiRoot = new Node<Entity>;
    Entity* e = EntityManager::getInstancePtr()->getEntity("background_entry_state");
    _uiRoot->setData(e);
    
    {
        Node<Entity>* n = new Node<Entity>;
        n->setData(EntityManager::getInstancePtr()->getEntity("button_enter"));
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
    
}
void StateEntryPoint::touchMoved(float x, float y, float previousX, float previousY)
{
    
}
void StateEntryPoint::touchEnd(float x, float y)
{
    
}
