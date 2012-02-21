#ifndef _PhysicsComponent_
#define _PhysicsComponent_
#include "IComponent.h"
class Entity;

class PhysicsComponent: public IPhysicsComponent
{
public:  
    PhysicsComponent(Entity* e);
    ~PhysicsComponent();
    
    virtual void update();
    
    virtual void setBody(b2Body* b);
    virtual void startContact();
    virtual void endContact();
    virtual void setPosition(float x, float y);
private:
    b2Body* _body;
    Entity* _host;
};
#endif
