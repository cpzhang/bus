//
//  Entity.h
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.

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
private:
    IRenderComponent*   _render_component;
    IPhysicsComponent*  _physics_component;
};

#endif