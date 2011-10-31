//
//  Entity.cpp
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Entity.h"
#include "RenderComponent.h"
Entity::Entity()
{
    
}

Entity::~Entity()
{
    
}

bool Entity::create()
{
    _render_component = new RenderComponent;
    return true;
}
void Entity::render()
{
    if (_render_component)
    {
        _render_component->render();
    }
}