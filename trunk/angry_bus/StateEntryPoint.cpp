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
        _uiRoot->setPosition(160, 240, 0);
        _uiRoot->setScale(320, 480, 1.0);
    }
    //
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_enter");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_enter"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to playing state"));
        n->setPosition(160, 240, 0);
        n->setScale(32, 48, 1.0);
        _uiRoot->addChild(n); 
    }
    //
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_score");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_score"));
        n->setPosition(30, 275, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_achievement");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_achievement"));
        n->setPosition(30, 195, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_network");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_network"));
        n->setPosition(30, 35, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_setting");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_setting"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("setting button in entry point state"));
        n->setPosition(30, 445, 0);
        n->setScale(41, 47, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "background_setting");
        n->setData(EntityManager::getInstancePtr()->getEntity("background_setting"));
        n->setPosition(80, 445, 0);
        n->setScale(64, 32, 1.0);
        _uiRoot->addChild(n);
        {
            Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_us");
            n->setData(EntityManager::getInstancePtr()->getEntity("button_us"));
            n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to about us state"));
            n->setPosition(70, 445, 0);
            n->setScale(32, 32, 1.0);
            NodeManager::getInstancePtr()->getNode("background_setting")->addChild(n);
        }
        {
            Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_sound");
            n->setData(EntityManager::getInstancePtr()->getEntity("button_sound"));
            n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("sound button in entry point state"));
            n->setPosition(100, 445, 0);
            n->setScale(32, 32, 1.0);
            NodeManager::getInstancePtr()->getNode("background_setting")->addChild(n);
        }
    }
    // sprite
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_car");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_car"));
        n->setPosition(80, 240, 0);
        n->setScale(32, 64, 1.0);
        _spriteRoot = n;
    }
    // tree 1
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_tree_bamboo");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_tree_bamboo"));
        n->setPosition(130, 340, 0);
        n->setScale(128, 64, 1.0);
        _spriteRoot->addChild(n);
        _trees.push_back("sprite_tree_bamboo");
    }
    // tree 2
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_tree_maple");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_tree_maple"));
        n->setPosition(130, 80, 0);
        n->setScale(128, 128, 1.0);
        _spriteRoot->addChild(n);
        _trees.push_back("sprite_tree_maple");
    }
    // leaf 1
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_leaf_purple");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_leaf_purple"));
        n->setPosition(320, 80, 0);
        n->setScale(32, 32, 1.0);
        _spriteRoot->addChild(n);
        _leaves.push_back("sprite_leaf_purple");
    }
    // leaf 2
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_leaf_green");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_leaf_green"));
        n->setPosition(320, 120, 0);
        n->setScale(32, 32, 1.0);
        _spriteRoot->addChild(n);
        _leaves.push_back("sprite_leaf_green");
    }
    // leaf 3
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_leaf_yellow");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_leaf_yellow"));
        n->setPosition(320, 200, 0);
        n->setScale(32, 32, 1.0);
        _spriteRoot->addChild(n);
        _leaves.push_back("sprite_leaf_yellow");
    }
}

StateEntryPoint::~StateEntryPoint()
{
    _uiRoot->release();
    _uiRoot = 0;
    _spriteRoot->release();
    _spriteRoot = 0;
}

void StateEntryPoint::render()
{
    _uiRoot->render();
    _spriteRoot->render();
}

void StateEntryPoint::updateTree(float secondsElapsed)
{
    for (size_t i = 0; i != _trees.size(); ++i)
    {
        Vector3 p = NodeManager::getInstancePtr()->getNode(_trees[i])->getPosition();
        static float speed = -18.0;
        p.y += speed * secondsElapsed;
        if(p.y < -50)
        {
            p.y = 550;
        }
        if(p.y > 550)
        {
            p.y = -50;
        }
        NodeManager::getInstancePtr()->getNode(_trees[i])->setPosition(p);
    }
}

void StateEntryPoint::updateLeaf(float secondsElapsed)
{
    for (size_t i = 0; i != _leaves.size(); ++i)
    {
        Vector3 p = NodeManager::getInstancePtr()->getNode(_leaves[i])->getPosition();
        srand(time(NULL) + i * rand());
        int j = rand() % 100;
        float y = j < 90 ? 1 : -1;  
        float speedX = -0.02f * j;
        float speedY = 0.005f * j * y;
        NodeManager::getInstancePtr()->getNode(_leaves[i])->translate(speedX, speedY, 0.0);
        NodeManager::getInstancePtr()->getNode(_leaves[i])->rotateZ(j*0.001f);
        if (p.x < 0 || p.y > 480 || p.y < 0)
        {
            NodeManager::getInstancePtr()->getNode(_leaves[i])->setPosition(320, rand() % 480, 0.0);
        }
    }
}

void StateEntryPoint::updateCar(float secondsElapsed)
{
    Vector3 p = NodeManager::getInstancePtr()->getNode("sprite_car")->getPosition();
    static float speed = 20.0;
    p.y += speed * secondsElapsed;
    if(p.y < 50 || p.y > 430)
    {
        speed *= -1.0;
    }
    NodeManager::getInstancePtr()->getNode("sprite_car")->setPosition(p);
}

void StateEntryPoint::update(float secondsElapsed)
{
    updateCar(secondsElapsed);
    updateLeaf(secondsElapsed);
    updateTree(secondsElapsed);
}

bool StateEntryPoint::touchBegin(float x, float y)
{
    return _uiRoot->touchBegin(x, y);
}

bool StateEntryPoint::touchMoved(float x, float y, float previousX, float previousY)
{
    return _uiRoot->touchMoved(x, y, previousX, previousY);
}

bool StateEntryPoint::touchEnd(float x, float y)
{
    return _uiRoot->touchEnd(x, y);
}

void StateEntryPoint::start()
{
    _uiRoot->setTransformation();
    _uiRoot->getNodeByName("background_setting")->hide();
    _spriteRoot->setTransformation();
}
