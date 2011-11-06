//
//  IComponent.h
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _IComponent_
#define _IComponent_
#include <string>
#include "b2Body.h"

struct IComponent
{
    virtual void update() = 0;
};

struct IRenderComponent : public IComponent
{
    virtual ~IRenderComponent(){};
    virtual void render() = 0;
    virtual void setProgram(const std::string& name) = 0;
    virtual bool setTexture(const std::string& fileName) = 0;
    virtual void setScale(float sx, float sy, float sz) = 0;
    virtual void setPosition(float x, float y, float z) = 0;
    virtual void setRotation(float angle) = 0;
};

struct IPhysicsComponent: public IComponent
{
    virtual void setBody(b2Body* b) = 0;
    virtual void startContact() = 0;
    virtual void endContact() = 0;
};
#endif