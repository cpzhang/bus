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

    //
    virtual void setCallBack(IButtonPushedCallBack* cb);
private:
    bool isInside(float x, float y);
    void onHover();
    void onPushed();
private:
    eButtonState _state;
    Entity* _host;
};

class ButtonPushedCallBack_Enter: public IButtonPushedCallBack
{
public:
   virtual void do();
};

class ButtonPushedCallBack_Us: public IButtonPushedCallBack
{
public:
    virtual void do();
};
#endif
