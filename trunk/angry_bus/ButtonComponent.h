#ifndef _ButtonComponent_
#define _ButtonComponent_
#include "IComponent.h"
#include "ITouch.h"
class Entity;
class ButtonComponent : public IButtonComponent
{
public:
    ButtonComponent(Entity* e);
    ~ButtonComponent();

    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);

    //
    virtual void setCallBack(IButtonPushedCallBack* cb);
private:
    bool isInside(float x, float y);
    void onHover();
    void onPushed();
private:
    eButtonState _state;
    Entity* _host;
    IButtonPushedCallBack* _callback;
};

class ButtonPushedCallBack_Enter: public IButtonPushedCallBack
{
public:
    ButtonPushedCallBack_Enter(){};
    ~ButtonPushedCallBack_Enter(){};
    virtual void doIt()
    {
	StateMachine::getInstancePrt()->goNext(eState_Playing);
    }
};

class ButtonPushedCallBack_Us: public IButtonPushedCallBack
{
public:
    virtual void doIt()
    {
	StateMachine::getInstancePrt()->goNext(eState_AboutUs);
    }
};
#endif
