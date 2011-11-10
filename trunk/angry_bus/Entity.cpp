#include "Entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "ButtonComponent.h"

#include <iostream>
Entity::Entity()
:_render_component(0), _physics_component(0), _button_component(0)
{
    
}

Entity::~Entity()
{
    delete _render_component;
    _render_component = 0;
    
    delete _physics_component;
    _physics_component = 0;
    
    if (_button_component)
    {
        delete _button_component;
        _button_component = 0;
    }
}

bool Entity::create()
{
    _render_component = new RenderComponent;
    _physics_component = new PhysicsComponent(this);
    _button_component = new ButtonComponent;
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

void Entity::setScale(const Vector3 &s)
{
    _render_component->setScale(s);
}

void Entity::setPosition(float x, float y, float z)
{
    _render_component->setPosition(x, y, z);
}

void Entity::setPosition(const Vector3 &p)
{
    _render_component->setPosition(p);
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

bool Entity::touchBegin(float x, float y)
{
    return _button_component->touchBegin(x, y);
}

bool Entity::touchMoved(float x, float y, float previousX, float previousY)
{
    return _button_component->touchMoved(x, y, previousX, previousY);
}

bool Entity::touchEnd(float x, float y)
{
    return _button_component->touchEnd(x, y);
}

void Entity::setCallBack(IButtonPushedCallBack *cb)
{
    _button_component->setCallBack(cb);
}