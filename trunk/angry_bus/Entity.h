#ifndef _Entity_
#define _Entity_

#include "IComponent.h"
#include "b2Body.h"
#include "Vector3.h"

class Entity: public IRenderComponent, public IPhysicsComponent, public IButtonComponent
{
public:
    Entity();
    ~Entity();
    
    bool create();
    
    virtual void update();
    //
    virtual void render();
    virtual void setProgram(const std::string& name);
    virtual bool setTexture(const std::string& fileName);
    virtual void setScale(float sx, float sy, float sz);
    virtual void setScale(const Vector3& s);
    virtual void setPosition(float x, float y, float z);
    virtual void setPosition(const Vector3& p);
    virtual void setRotation(float angle);

    //
    virtual void setBody(b2Body* b);
    virtual void startContact();
    virtual void endContact();
    
    //
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);

    //
    virtual void setCallBack(IButtonPushedCallBack* cb);
private:
    IRenderComponent*   _render_component;
    IPhysicsComponent*  _physics_component;
    IButtonComponent*   _button_component;
};

#endif
