#include "PhysicsComponent.h"
#include "Entity.h"
#include "Common.h"

PhysicsComponent::PhysicsComponent(Entity* e)
:_body(0), _host(e)
{
    
}

PhysicsComponent::~PhysicsComponent()
{
    
}

void PhysicsComponent::setBody(b2Body *b)
{
    _body = b;
    _body->SetUserData(_host);
}

void PhysicsComponent::startContact()
{
    
}

void PhysicsComponent::endContact()
{
    
}

void PhysicsComponent::update()
{
    if (_body && _body->IsActive()) 
    { 
        b2Vec2 p = _body->GetPosition();
        float a = _body->GetAngle();
        _host->setPosition(m2p(p.x), m2p(p.y), 0.0);
        _host->setRotation(a);
    }
}

void PhysicsComponent::setPosition(float x, float y)
{
    b2Vec2 p;
    p.x = p2m(x);
    p.y = p2m(y);
    _body->SetTransform(p, 0.0f);
}
