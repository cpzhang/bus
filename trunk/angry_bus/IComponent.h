//
//  IComponent.h
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _IComponent_
#define _IComponent_
struct IComponent
{
    
};

struct IRenderComponent : public IComponent
{
    virtual ~IRenderComponent(){};
    virtual void render() = 0;
};

#endif