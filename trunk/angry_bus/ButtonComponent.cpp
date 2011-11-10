#include "ButtonComponent.h"
#include "Entity.h"
#include "StateMachine.h"

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
        _state = eButtonState_Hover;
        onHover();
        return true;
    }
    else
    {
        _state = eButtonState_Normal;
    }
    
    return false;
}

bool ButtonComponent::touchMoved(float x, float y, float previousX, float previousY)
{
    if(isInside(x, y))
    {
        _state = eButtonState_Hover;
        onHover();
        return true;
    }
    else
    {
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

void ButtonComponent::onPushed()
{
    if(_callback)
    {
        _callback->doIt();
    }
}

void ButtonPushedCallBack_Enter::doIt()
{
    StateMachine::getInstancePtr()->goNext(eState_Playing);
}

void ButtonPushedCallBack_Us::doIt()
{
    StateMachine::getInstancePtr()->goNext(eState_AboutUs);
}

void ButtonPushedCallBack_GotoEntryPoint::doIt()
{
    StateMachine::getInstancePtr()->goNext(eState_EntryPoint);
}