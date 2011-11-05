//
//  Entity.h
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _Entity_
#define _Entity_

#include "IComponent.h"
class Entity
{
public:
    Entity();
    ~Entity();
    
    bool create();
    void render();
    IRenderComponent* getRenderComponent();
private:
    IRenderComponent*   _render_component;
};

#endif