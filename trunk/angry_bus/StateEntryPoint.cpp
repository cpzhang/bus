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
void StateEntryPoint::updateTree()
{
    static const float speed = 0.8f;
    static const float edge = 500.0f;
    static const float edgeOffset = 128.0f;
    //
#define TranslateTree(tree)			\
    tree->translate(0, speed);			\
    if (tree->getCenterY() >= edge)		\
    {						\
	tree->translate(0, -edge - edgeOffset);	\
    }
    //
    TranslateTree(_tree1);
    TranslateTree(_tree2);
    TranslateTree(_tree3);
    TranslateTree(_tree4);
}
void StateEntryPoint::updateLeaf()
{
  for (size_t i = 0; i != _leaf.size(); ++i)
  {
                srand(time(NULL) + i * rand());
                int j = rand() % 100;
                float y = j < 90 ? 1 : -1;  
                float speedX = -0.02f * j;
                float speedY = 0.005f * j * y;
                _leaf[i]->translate(speedX, speedY, 0.0);
                _leaf[i]->rotateZ(j*0.01f);
                if (_leaf[i]->getPosition().x < 0 || _leaf[i]->getPosition().y > 480 || _leaf[i]->getPosition().y < 0)
                {
                    _leaf[i]->setPosition(320, rand() % 480, 0.0f);
                }
  }
}
void StateEntryPoint::updateCar()
{
       Vector3 p = NodeManager::getInstancePtr()->getNode("sprite_car")->getPosition();
        
        srand(time(NULL) + rand());
        static int threshold = 80;
        float speed = rand() % 100 - threshold;
        if(p.y < 50)
        {
            speed = abs(speed);
            threshold = 35;
        }
        else if(p.y > 430)
        {
            speed = -abs(speed);
            threshold = 60;
        }
       
        p.y += speed * secondsElapsed;
        NodeManager::getInstancePtr()->getNode("sprite_car")->setPosition(p);
}
void StateEntryPoint::update(float secondsElapsed)
{
    updateCar();
    updateLeaf();
    updateTree();
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
