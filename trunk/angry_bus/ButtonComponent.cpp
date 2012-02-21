#include "ButtonComponent.h"
#include "Entity.h"
#include "NodeManager.h"
#include "SoundManager.h"
#include "EntityManager.h"

ButtonComponent::ButtonComponent(Entity* e)
:_state(eButtonState_Normal), _host(e), _callback(0)
{
}

ButtonComponent::~ButtonComponent()
{
}

void ButtonComponent::update()
{
    
}

bool ButtonComponent::touchBegin(float x, float y)
{
    if(isInside(x, y))
    {
        if (_state != eButtonState_Hover) 
        {
            onHover();
        }
        
        _state = eButtonState_Hover;
        
        return true;
    }
    else
    {
        if (_state == eButtonState_Hover) 
        {
            onHoverEnd();
        }
        
        _state = eButtonState_Normal;
    }
    
    return false;
}

bool ButtonComponent::touchMoved(float x, float y, float previousX, float previousY)
{
    if(isInside(x, y))
    {
        if (_state != eButtonState_Hover) 
        {
            onHover();
        }
        
        _state = eButtonState_Hover;
        return true;
    }
    else
    {
        if (_state == eButtonState_Hover) 
        {
            onHoverEnd();
        }
        
        _state = eButtonState_Normal;
    }
    
    return false;
}

bool ButtonComponent::touchEnd(float x, float y)
{
    if(isInside(x, y))
    {
        if(_state == eButtonState_Hover)
        {
            if (_state == eButtonState_Hover) 
            {
                onHoverEnd();
            }
            
            _state = eButtonState_Pushed;
            onPushed();
            _state = eButtonState_Normal;
        }
        return true;
    }
    
    return false;
}

void ButtonComponent::setCallBack(IButtonPushedCallBack* cb)
{
    _callback = cb;
}

bool ButtonComponent::isInside(float x, float y)
{
    return _host->isInside(x, y);
}

void ButtonComponent::onHover()
{
    _host->setScale(_host->getScale() * 1.33);
}

void ButtonComponent::onHoverEnd()
{
    _host->setScale(_host->getScale() / 1.33);
}
void ButtonComponent::onPushed()
{
    if(_callback)
    {
        _callback->doIt();
    }
}

void ButtonPushedCallBack_Setting::doIt()
{
    Node<Entity>* n = NodeManager::getInstancePtr()->getNode("background_setting");
    if(n)
    {
        bool b = n->isVisible();
        n->setVisible(!b);
    }
}

void ButtonPushedCallBack_Sound::doIt()
{
    bool b =SoundManager::getInstancePtr()->isEnable();
    if(b)
    {
        SoundManager::getInstancePtr()->stop();
        EntityManager::getInstancePtr()->getEntity("button_sound")->setTexture("shengyin2.png");
    }
    else
    {
        SoundManager::getInstancePtr()->play();
        EntityManager::getInstancePtr()->getEntity("button_sound")->setTexture("shengyin1.png");
    }
}

void ButtonPushedCallStatePlaying_NextLevel::doIt()
{
    IState* t = StateMachine::getInstancePtr()->getState(eState_Playing);
    StatePlaying* sp = (StatePlaying*)t;
    sp->nextLevel();
}

void ButtonPushedCallStatePlaying_DoTheSameLevelAgain::doIt()
{
    IState* t = StateMachine::getInstancePtr()->getState(eState_Playing);
    StatePlaying* sp = (StatePlaying*)t;
    sp->theSameLevelAgain();
}
