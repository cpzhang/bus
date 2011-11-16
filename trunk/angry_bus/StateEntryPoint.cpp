#include "StateEntryPoint.h"
#include "EntityManager.h"
#include "Entity.h"
#include "NodeManager.h"
#include "ButtonCallbackManager.h"

StateEntryPoint::StateEntryPoint()
{
    {
        _uiRoot = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "background_entry_state");
        _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_entry_state"));
	_uiRoot->setCallBack();
        _uiRoot->setPosition(160, 240, 0);
        _uiRoot->setScale(320, 480, 1.0);
    }
    //
    {
        Node* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_enter");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_enter"));
	n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to playing state"));
        n->setPosition(160, 240, 0);
        n->setScale(32, 48, 1.0);
        _uiRoot->addChild(n); 
    }
    //
    {
        Node* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_score");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_score"));
        n->setPosition(30, 275, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_achievement");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_achievement"));
        n->setPosition(30, 195, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_network");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_network"));
        n->setPosition(30, 35, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_setting");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_setting"));
	n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("setting button in entry point state"));
        n->setPosition(30, 445, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "background_setting");
        n->setData(EntityManager::getInstancePtr()->getEntity("background_setting"));
        n->setPosition(80, 445, 0);
        n->setScale(64, 32, 1.0);
        _uiRoot->addChild(n);
	{
	    Node* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "button_us");
	    n->setData(EntityManager::getInstancePtr()->getEntity("button_us"));
	    n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to about us state"));
	    n->setPosition(80, 445, 0);
	    n->setScale(32, 32, 1.0);
	    NodeManager::getInstancePtr()->getNode("background_setting")->addChild(n);
	}
	{
	    Node* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "button_sound");
	    n->setData(EntityManager::getInstancePtr()->getEntity("button_sound"));
	    n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("sound button in entry point state"));
	    n->setPosition(80, 445, 0);
	    n->setScale(32, 32, 1.0);
	    NodeManager::getInstancePtr()->getNode("background_setting")->addChild(n);
	}
    }
}

StateEntryPoint::~StateEntryPoint()
{
    _uiRoot->release();
    _uiRoot = 0;
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
    if (1) {
        return _uiRoot->touchBegin(x, y);
    }
    return _uiRoot->breadth_first(&Entity::touchBegin, x, y);
}
bool StateEntryPoint::touchMoved(float x, float y, float previousX, float previousY)
{
    if (1) {
        return _uiRoot->touchMoved(x, y, previousX, previousY);
    }
    return _uiRoot->breadth_first(&Entity::touchMoved, x, y, previousX, previousY);
}
bool StateEntryPoint::touchEnd(float x, float y)
{
    if (1) {
        return _uiRoot->touchEnd(x, y);
    }
    return _uiRoot->breadth_first(&Entity::touchEnd, x, y);
}

void StateEntryPoint::start()
{
    _uiRoot->setTransformation();
    _uiRoot->getNodeByName("background_setting")->hide();
}
