#ifndef _Entity_
#define _Entity_

#include "IComponent.h"
#include "b2Body.h"
class Entity: public IRenderComponent, public IPhysicsComponent
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
    virtual void setPosition(float x, float y, float z);
    virtual void setRotation(float angle);

    //
    virtual void setBody(b2Body* b);
    virtual void startContact();
    virtual void endContact();
    
    //
    virtual void touchBegin(float x, float y);
    virtual void touchMoved(float x, float y, float previousX, float previousY);
    virtual void touchEnd(float x, float y);

private:
    IRenderComponent*   _render_component;
    IPhysicsComponent*  _physics_component;
    IButtonComponent*   _button_component;
};

#endif
