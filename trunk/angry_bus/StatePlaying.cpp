#include "StatePlaying.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Node.h"
#include "NodeManager.h"
#include "ButtonCallbackManager.h"

StatePlaying::StatePlaying()
{
    {
        _uiRoot = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "background_playing");
        _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_playing"));
        _uiRoot->setPosition(160, 240, 0);
        _uiRoot->setScale(320, 480, 1.0);
    }
    
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_bus");
        // TransformationNode* n = new TransformationNode("sprite_bus");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_bus"));
        n->setPosition(80, 240, 0);
        n->setScale(160, 480, 1.0);
        _uiRoot->addChild(n);
    }
    
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_back");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_back"));
	n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to entry point state"));
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
    //if (1) {
        return _uiRoot->touchBegin(x, y);
    //}

    //return _uiRoot->breadth_first(&Entity::touchBegin, x, y);
}

bool StatePlaying::touchMoved(float x, float y, float previousX, float previousY)
{
    //if (1) {
        return _uiRoot->touchMoved(x, y, previousX, previousY);
    //}

    //return _uiRoot->breadth_first(&Entity::touchMoved, x, y, previousX, previousY);
}

bool StatePlaying::touchEnd(float x, float y)
{
    //if (1) {
        return _uiRoot->touchEnd(x, y);
    //}

    //return _uiRoot->breadth_first(&Entity::touchEnd, x, y);
}

void StatePlaying::start()
{
    _uiRoot->setTransformation();
}
