#ifndef _ButtonComponent_
#define _ButtonComponent_
#include "IComponent.h"
#include "ITouch.h"

class ButtonComponent : public IButtonComponent, public ITouch
{
public:
    ButtonComponent();
    ~ButtonComponent();

    virtual void touchBegin(float x, float y);
    virtual void touchMoved(float x, float y, float previousX, float previousY);
    virtual void touchEnd(float x, float y);

private:
    eButtonState _state;
};
#endif
