#ifndef _ButtonComponent_
#define _ButtonComponent_
#include "IComponent.h"
#include "ITouch.h"
#include "StateMachine.h"
#include "IState.h"
#include "StatePlaying.h"
class Entity;
class ButtonComponent : public IButtonComponent
{
public:
    ButtonComponent(Entity* e);
    ~ButtonComponent();
    
    //
    virtual void update();
    
    //
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);
    
    virtual void onPushed();
    //
    virtual void setCallBack(IButtonPushedCallBack* cb);
private:
    bool isInside(float x, float y);
    void onHover();
    void onHoverEnd();
private:
    eButtonState _state;
    Entity* _host;
    IButtonPushedCallBack* _callback;
};

template <eState s, eScene c = eScene_Size>
class ButtonPushedCallBack_Enter: public IButtonPushedCallBack
{
public:
    ButtonPushedCallBack_Enter(){};
    ~ButtonPushedCallBack_Enter(){};
    virtual void doIt()
    {
        StateMachine::getInstancePtr()->goNext(s);
        if (eScene_Size != c)
        {
            IState* t = StateMachine::getInstancePtr()->getState(eState_Playing);
            StatePlaying* sp = (StatePlaying*)t;
            if(sp->loadScene(c))
                sp->start();
        }
    }
};

class ButtonPushedCallBack_Setting: public IButtonPushedCallBack
{
public:
    virtual void doIt();
};

class ButtonPushedCallBack_Sound: public IButtonPushedCallBack
{
public:
    virtual void doIt();
};

class ButtonPushedCallStatePlaying_NextLevel: public IButtonPushedCallBack
{
public:
    virtual void doIt();
};
class ButtonPushedCallStatePlaying_DoTheSameLevelAgain: public IButtonPushedCallBack
{
public:
    virtual void doIt();
};
#endif
