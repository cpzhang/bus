#include "Entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"

#include <iostream>
Entity::Entity()
 :_render_component(0), _physics_component(0), _hide(false), _isInBus(false)
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
}

void Entity::render(const Color& c /*= Color::white*/)
{
    if (!_hide && _render_component)
    {
        _render_component->render(c);
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

void Entity::setPosition(float x, float y)
{
    if (_physics_component)
        _physics_component->setPosition(x, y);
}

void Entity::setBody(b2Body* b)
{
    if (_physics_component)
        _physics_component->setBody(b);
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

Vector3 Entity::getPosition()
{
    if (_render_component)
        return _render_component->getPosition();
    
    return Vector3::ZERO;
}

void Entity::hide()
{
    _hide = true;
}

void Entity::show()
{
    _hide = false;
}

void Entity::setExpression(eExpression e)
{
    if (!_expressions[e].empty()) 
    {
        setTexture(_expressions[e]); 
    }
}
void Entity::setExpression(eExpression e,const std::string &s)
{
    _expressions[e] = s;
}
void Entity::setValue(eValueProperty property, int value)
{
    _property = property;
    _value = value;
}
int Entity::getValue()
{
    return _value;
}
eValueProperty Entity::getProperty()
{
    return _property;
}
void Entity::setInBus(bool inBus)
{
    _isInBus = inBus;
}
bool Entity::isInBus()
{
    return _isInBus;
}