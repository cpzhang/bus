//
//  Entity.cpp
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include <iostream>
Entity::Entity()
:_render_component(0), _physics_component(0)
{
    
}

Entity::~Entity()
{
    delete _render_component;
    _render_component = 0;
    
    delete _physics_component;
    _physics_component = 0;
}

bool Entity::create()
{
    _render_component = new RenderComponent;
    _physics_component = new PhysicsComponent(this);
    return true;
}

void Entity::update()
{
    _physics_component->update();
    _render_component->update();
}

void Entity::render()
{
    _render_component->render();
}

void Entity::setProgram(std::string const &name)
{
    _render_component->setProgram(name);
}

bool Entity::setTexture(std::string const &fileName)
{
    return _render_component->setTexture(fileName);
}

void Entity::setScale(float sx, float sy, float sz)
{
    _render_component->setScale(sx, sy, sz);
}

void Entity::setPosition(float x, float y, float z)
{
    _render_component->setPosition(x, y, z);
}

void Entity::setRotation(float angle)
{
    _render_component->setRotation(angle);
}

void Entity::startContact()
{
    _physics_component->startContact();
}

void Entity::endContact()
{
    _physics_component->endContact();
}

void Entity::setBody(b2Body* b)
{
    _physics_component->setBody(b);
}