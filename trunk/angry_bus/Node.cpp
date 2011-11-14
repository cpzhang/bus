#include "Node.h"
ButtonNode::ButtonNode(const std::string& name)
    :TransformationNode(name)
{
}

ButtonNode::~ButtonNode()
{
}

bool ButtonNode::touchBegin(float x, float y)
{
    if(_visible)
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
   
    }
    return false;
}

bool ButtonNode::touchMoved(float x, float y, float previousX, float previousY)
{
    if(_visible)
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
     }
    return false;
}

bool ButtonNode::touchEnd(float x, float y)
{
    if(_visible)
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
    }
    return false;
}
bool ButtonNode::isInside(float x, float y)
{
    return _data->isInside(x, y);
}
void ButtonNode::onHover()
{
}
void ButtonNode::onHoverEnd()
{
}
void ButtonNode::onPushed()
{
}
