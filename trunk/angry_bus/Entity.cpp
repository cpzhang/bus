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
    if (_render_component) 
    {
        delete _render_component;
        _render_component = 0;
        
    }
    
    if (_physics_component)
    {
        delete _physics_component;
        _physics_component = 0;
    }
    
    if (_button_component)
    {
        delete _button_component;
        _button_component = 0;
    }
}

bool Entity::create(bool bRender, bool bPhysics, bool bButton)
{
    if (bRender) 
    {
        _render_component = new RenderComponent;
    }
    
    if (bPhysics) 
    {
        _physics_component = new PhysicsComponent(this);
    }
    
    if(bButton)
    {
        _button_component = new ButtonComponent(this);
    }
    
    return true;
}

void Entity::update()
{
    if (_physics_component)
    {
        _physics_component->update();
    }
    
    if (_render_component)
    {
        _render_component->update();
    }
    
    if (_button_component)
    {
        _button_component->update();
    }
}

void Entity::render()
{
    if (_render_component)
    {
        _render_component->render();
    }
}

void Entity::setProgram(std::string const &name)
{
    if (_render_component)
        _render_component->setProgram(name);
}

bool Entity::setTexture(std::string const &fileName)
{
    if (_render_component)
        return _render_component->setTexture(fileName);
    
    return false;
}

void Entity::setScale(float sx, float sy, float sz)
{
    if (_render_component)
        _render_component->setScale(sx, sy, sz);
}

void Entity::setScale(const Vector3 &s)
{
    if (_render_component)
        _render_component->setScale(s);
}

void Entity::setPosition(float x, float y, float z)
{
    if (_render_component)
        _render_component->setPosition(x, y, z);
}

void Entity::setPosition(const Vector3 &p)
{
    if (_render_component)
        _render_component->setPosition(p);
}

void Entity::setRotation(float angle)
{
    if (_render_component)
        _render_component->setRotation(angle);
}

void Entity::startContact()
{
    if (_physics_component)
        _physics_component->startContact();
}

void Entity::endContact()
{
    if (_physics_component)
        _physics_component->endContact();
}

void Entity::setBody(b2Body* b)
{
    if (_physics_component)
        _physics_component->setBody(b);
}

bool Entity::touchBegin(float x, float y)
{
    if(_button_component)
        return _button_component->touchBegin(x, y);
    
    return false;
}

bool Entity::touchMoved(float x, float y, float previousX, float previousY)
{
    if(_button_component)
        return _button_component->touchMoved(x, y, previousX, previousY);
    
    return false;
}

bool Entity::touchEnd(float x, float y)
{
    if(_button_component)
        return _button_component->touchEnd(x, y);
    
    return false;
}

void Entity::setCallBack(IButtonPushedCallBack *cb)
{
    if(_button_component)
        _button_component->setCallBack(cb);
}

bool Entity::isInside(float x, float y)
{
    if (_render_component)
        return _render_component->isInside(x, y);
    
    return false;
}

Vector3 Entity::getScale()
{
    if (_render_component)
        return _render_component->getScale();
    
    return Vector3::ZERO;
}
