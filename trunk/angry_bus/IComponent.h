#ifndef _IComponent_
#define _IComponent_
#include <string>
#include "b2Body.h"
#include "Vector3.h"
#include "ITouch.h"

struct IComponent
{
    virtual ~IComponent(){};
    virtual void update() = 0;
};

struct IRenderComponent : public IComponent
{
    virtual ~IRenderComponent(){};
    virtual void render() = 0;
    virtual void setProgram(const std::string& name) = 0;
    virtual bool setTexture(const std::string& fileName) = 0;
    virtual void setScale(float sx, float sy, float sz) = 0;
    virtual Vector3 getScale() = 0;
    virtual void setPosition(float x, float y, float z) = 0;
    virtual void setRotation(float angle) = 0;
    virtual Vector3 getPosition() = 0;
    virtual void setScale(const Vector3& s) = 0;
    virtual void setPosition(const Vector3& p) = 0;
    virtual bool isInside(float x, float y) = 0;
};

struct IPhysicsComponent: public IComponent
{
    virtual ~IPhysicsComponent(){};
    virtual void setBody(b2Body* b) = 0;
    virtual void startContact() = 0;
    virtual void endContact() = 0;
    virtual void setPosition(float x, float y) = 0;
};

enum eButtonState
{
    eButtonState_Normal,
    eButtonState_Hover,
    eButtonState_Pushed,
    eButtonState_Size,
};

struct IButtonPushedCallBack
{
    virtual void doIt() = 0;
};

struct IButtonComponent: public IComponent, public ITouch
{
    virtual ~IButtonComponent(){};
    virtual void setCallBack(IButtonPushedCallBack* cb) = 0;
    virtual void onPushed() = 0;
};
#endif
