#include "PhysicsManager.h"
#include "box2DRender.h"
#include <Box2D/Box2d.h>
#include "EntityManager.h"
PhysicsManager::PhysicsManager()
:_focus(0), _mouseJoint(0), _groundBody(0), _box2DRender(0), _world(0)
{
    //
    _world = new b2World(b2Vec2(0, 0));
    if (0)
    {
        _box2DRender = new box2DRender;
        _box2DRender->SetFlags(b2Draw::e_shapeBit);
        _world->SetDebugDraw(_box2DRender);
    }
    
    // contact listener
    _world->SetContactListener(EntityManager::getInstancePtr());    
    
    {
        b2BodyDef bodyDef;
        _groundBody = _world->CreateBody(&bodyDef);
    }
    
    // wall 
    {
        b2BodyDef bd;
        bd.type = b2_staticBody;
        
        b2Body* b = _world->CreateBody(&bd);
        b2EdgeShape s;
        
        b2FixtureDef fd;
        fd.friction = 0;
        fd.shape = &s;
        
        //
        s.Set(b2Vec2(0, 0), b2Vec2(p2m(320), 0));
        b->CreateFixture(&fd);
        //
        s.Set(b2Vec2(p2m(320), 0), b2Vec2(p2m(320), p2m(480)));
        b->CreateFixture(&fd);
        //
        s.Set(b2Vec2(0, 0), b2Vec2(0, p2m(480)));
        b->CreateFixture(&fd);
        //
        s.Set(b2Vec2(0, p2m(480)), b2Vec2(p2m(320), p2m(480)));
        b->CreateFixture(&fd);
        // car top right
        s.Set(b2Vec2(p2m(160), p2m(0)), b2Vec2(p2m(160), p2m(140)));
        b->CreateFixture(&fd);
        // car top left
        s.Set(b2Vec2(p2m(160), p2m(240)), b2Vec2(p2m(160), p2m(480)));
        b->CreateFixture(&fd);
    }
    // event
    EventManager::getInstancePtr()->subscribeEvent(eEvent_LevelFinished, this);
}

PhysicsManager::~PhysicsManager()
{
    //
    // event
    EventManager::getInstancePtr()->unsubscribeEvent(eEvent_LevelFinished, this);
    //
    delete _world;
    delete _box2DRender;
}

void PhysicsManager::update(float secondsElapsed)
{
    _world->Step(secondsElapsed, 2, 1);
    _world->ClearForces();
}

void PhysicsManager::render()
{
    _world->DrawDebugData();
}
bool PhysicsManager::touchBegin(float x, float y)
{
    if (_mouseJoint)
    {
        return true;
    }
    b2AABB aabb;
    static const float scSize = 10.0;
    aabb.lowerBound = b2Vec2(p2m(x - scSize), p2m(y - scSize));
    aabb.upperBound = b2Vec2(p2m(x + scSize), p2m(y + scSize));
    
    _focus = 0;
    _world->QueryAABB(this, aabb);  
    
    if (_focus) 
    {
        b2MouseJointDef mjd;
        mjd.bodyA = _groundBody;
        mjd.bodyB = _focus;
        mjd.collideConnected = true;
        mjd.maxForce = 300 * _focus->GetMass();
        mjd.target = b2Vec2(p2m(x), p2m(y));
        
        _mouseJoint = (b2MouseJoint*)_world->CreateJoint(&mjd);
        _focus->SetAwake(true);
    }
    
    return true;
}

bool PhysicsManager::touchEnd(float x, float y)
{
    _focus = 0;
    
    if (_mouseJoint)
    {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = 0;
    }
    return true;
}

bool PhysicsManager::touchMoved(float x, float y, float previousX, float previousY)
{    
    if (_mouseJoint)
    {
        _mouseJoint->SetTarget(b2Vec2(p2m(x), p2m(y)));
    }
    return true;
}

bool PhysicsManager::ReportFixture(b2Fixture *fixture)
{
    if(fixture)
        _focus = fixture->GetBody();
    return true;
}

b2Body* PhysicsManager::createBody(float x, float y)
{
    //body definition
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(p2m(x), p2m(y));
    myBodyDef.angle = 0;
    myBodyDef.angularVelocity = 0;
    myBodyDef.angularDamping = 1;
//    myBodyDef.fixedRotation = true;
    
    b2Body* b = _world->CreateBody(&myBodyDef);
    
    b2CircleShape s;
    s.m_radius = p2m(16);
    
    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &s;
    myFixtureDef.density = 1;
    myFixtureDef.restitution = 0.3;
    myFixtureDef.friction = 0.5;
    b->CreateFixture(&myFixtureDef);
    
    //
    return b;
}

void PhysicsManager::onEvent(sEvent *e)
{
    if (e == NULL)
    {
        return;
    }
    switch (e->eventID) 
    {
        case eEvent_Null:
        {
            
        }
        break;
        case eEvent_LevelFinished:
        {
            if (_mouseJoint)
            {
                _world->DestroyJoint(_mouseJoint);
                _mouseJoint = 0;
            }
        }
        break;    
        default:
            break;
    }
}