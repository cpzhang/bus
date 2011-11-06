//
//  PhysicsComponent.h
//  angry_bus
//
//  Created by suning on 11-11-6.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
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
    
private:
    b2Body* _body;
    Entity* _host;
};
#endif