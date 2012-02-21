#include "Node.h"
ButtonNode::ButtonNode(const std::string& name)
:TransformationNode(name), _callback(0)
{
}

ButtonNode::~ButtonNode()
{
}

void ButtonNode::setCallBack(IButtonPushedCallBack* cb)
{
    _callback = cb;
}

bool ButtonNode::touchBeginImp(float x, float y)
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

bool ButtonNode::touchMovedImp(float x, float y, float previousX, float previousY)
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

bool ButtonNode::touchEndImp(float x, float y)
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

bool ButtonNode::isInside(float x, float y)
{
    return _data->isInside(x, y);
}

void ButtonNode::onHover()
{
    setTransformation(1.33, false);
}

void ButtonNode::onHoverEnd()
{
    setTransformation();
}

void ButtonNode::onPushed()
{
    if (_callback)
    {
        return _callback->doIt();
    }
}
