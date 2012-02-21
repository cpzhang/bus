#include "StateLevelSelection.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Node.h"
#include "NodeManager.h"
#include "ButtonCallbackManager.h"

StateLevelSelection::StateLevelSelection()
{
    {
        _uiRoot = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "background_selection");
        _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_selection"));
        _uiRoot->setPosition(160, 240, 0);
        _uiRoot->setScale(320, 480, 1.0);
    }
   
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_city");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_city"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to playing state in city"));
        n->setPosition(160, 240, 0);
        n->setScale(110, 110, 1.0);
        _uiRoot->addChild(n);
    }

    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_wetLand");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_wetLand"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to playing state in wetLand"));
        n->setPosition(230, 330, 0);
        n->setScale(100, 100, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_glacier");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_glacier"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to playing state in glacier"));
        n->setPosition(230, 150, 0);
        n->setScale(100, 100, 1.0);
        _uiRoot->addChild(n);
    } 
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_spaceStation");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_spaceStation"));
        //n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to playing state in glacier"));
        n->setPosition(230, 50, 0);
        n->setScale(59, 59, 1.0);
        _uiRoot->addChild(n);
    } 
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_body");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_body"));
        //n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to playing state in glacier"));
        n->setPosition(230, 400, 0);
        n->setScale(59, 59, 1.0);
        _uiRoot->addChild(n);
    } 
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_ant");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_ant"));
        //n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to playing state in glacier"));
        n->setPosition(60, 350, 0);
        n->setScale(59, 59, 1.0);
        _uiRoot->addChild(n);
    } 
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_back_entrystate");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_back"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to entry point state"));
        n->setPosition(16, 450, 0);
        n->setScale(32, 32, 1.0);
        _uiRoot->addChild(n);
    }
}

StateLevelSelection::~StateLevelSelection()
{
    _uiRoot->release();
    _uiRoot = 0;
}

void StateLevelSelection::render()
{
    _uiRoot->render();
}

void StateLevelSelection::update(float secondsElapsed)
{
    _uiRoot->breadth_first(&Entity::update);
}

bool StateLevelSelection::touchBegin(float x, float y)
{
    return _uiRoot->touchBegin(x, y);
}

bool StateLevelSelection::touchMoved(float x, float y, float previousX, float previousY)
{
    return _uiRoot->touchMoved(x, y, previousX, previousY);
}

bool StateLevelSelection::touchEnd(float x, float y)
{
    return _uiRoot->touchEnd(x, y);
}

void StateLevelSelection::start()
{
    _uiRoot->setTransformation();
}

