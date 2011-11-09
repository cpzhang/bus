#include "bootstrapper.h"
#include "ServicesProvider.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ShaderManager.h"
#include "ProgramManager.h"
#include "TextureManager.h"
#include "Shader.h"
#include "box2DRender.h"
#include <Box2D/Box2d.h>
#include <iostream>


BootStrapper::BootStrapper()
:_focus(0), _mouseJoint(0)
{
    
}

BootStrapper::~BootStrapper()
{
    
}

void BootStrapper::applyRender(eRender e)
{
    ServicesProvider::getInstancePtr()->setRender(e);
}

bool BootStrapper::initSingletons()
{
    new ServicesProvider;
    new EntityManager;
    new ShaderManager;
    new ProgramManager;
    new TextureManager;
    new StateMachine;

    return true;
}

bool BootStrapper::create()
{
    //
    StateMachine::getInstancePtr()->createStates();
    
    //
    registerPrograms();
    
    //
    ServicesProvider::getInstancePtr()->getRender()->setClearColor(0.1, 0.1, 0.1, 1.0);
    
    //
    _world = new b2World(b2Vec2(0, 0));
    _box2DRender = new box2DRender;
    _box2DRender->SetFlags(b2Draw::e_shapeBit);
    _world->SetDebugDraw(_box2DRender);
    // contact listener
    _world->SetContactListener(EntityManager::getInstancePtr());    
    
    {
        b2BodyDef bodyDef;
        _groundBody = _world->CreateBody(&bodyDef);
    }
    
    {
        //body definition
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;
        myBodyDef.position.Set(p2m(160), p2m(200));
        myBodyDef.angle = 1;
        
        b2CircleShape s;
        s.m_radius = p2m(16);
        
        //fixture definition
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &s;
        myFixtureDef.density = 1;
        myFixtureDef.restitution = 0.3;
        myFixtureDef.friction = 0.5;
        
        //create dynamic bodies
        b2Body* b = _world->CreateBody(&myBodyDef);
        
       // b->SetUserData(e);
       // e->setBody(b);
        b->SetAwake(true); 
        
        b->CreateFixture(&myFixtureDef);
        
        for (int i = 0; i != 20; ++i)
        {
            myBodyDef.position.Set(p2m(16*i), p2m(20*i));
            _world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
        }
    }
    
    // wall 
    {
        b2BodyDef bd;
        bd.type = b2_staticBody;
        
        b2Body* b = _world->CreateBody(&bd);
        b2EdgeShape s;
        
        b2FixtureDef fd;
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
    }
    
    return true;
}

void BootStrapper::destroy()
{
    delete ProgramManager::getInstancePtr();
    delete ShaderManager::getInstancePtr();
    delete ServicesProvider::getInstancePtr();
    delete EntityManager::getInstancePtr();
    delete StateMachine::getInstancePtr();

    //
    delete _world;
    delete _box2DRender;
}
void BootStrapper::run(float secondsElapsed)
{
    update(secondsElapsed);
    render();
}

void BootStrapper::update(float secondsElapsed)
{
    _world->Step(secondsElapsed, 8, 5);
    _world->ClearForces();
    StateMachine::getInstancePtr()->update(secondsElapsed);
}

void BootStrapper::render()
{
    ServicesProvider::getInstance().getRender()->beginFrame(true, false);
    StateMachine::getInstancePtr()->render();
    _world->DrawDebugData();
    ServicesProvider::getInstance().getRender()->endFrame();
}

void BootStrapper::setViewPort(int width, int height)
{
    ServicesProvider::getInstancePtr()->getRender()->setViewPort(width, height);
}

bool BootStrapper::registerPrograms()
{
    //
    
    if (0) 
    {
        if(!ShaderManager::getInstancePtr()->createAndBuildShader("vs", "fuck.vs", Shader::eShaderType_Vertex)) return false;
        if(!ShaderManager::getInstancePtr()->createAndBuildShader("fs", "fuck.fs", Shader::eShaderType_Fragment)) return false;
        if(!ProgramManager::getInstancePtr()->createAndBuildProgram("fuck", "vs", "fs")) return false;
    }
    
    //
    if(!ShaderManager::getInstancePtr()->createAndBuildShader("diffuse_vs", "diffuse.vs", Shader::eShaderType_Vertex)) return false;
    if(!ShaderManager::getInstancePtr()->createAndBuildShader("diffuse_fs", "diffuse.fs", Shader::eShaderType_Fragment)) return false;
    if(!ProgramManager::getInstancePtr()->createAndBuildProgram("diffuse", "diffuse_vs", "diffuse_fs")) return false;
    
    //
    //
    if(!ShaderManager::getInstancePtr()->createAndBuildShader("texture_vs", "texture.vs", Shader::eShaderType_Vertex)) return false;
    if(!ShaderManager::getInstancePtr()->createAndBuildShader("texture_fs", "texture.fs", Shader::eShaderType_Fragment)) return false;
    if(!ProgramManager::getInstancePtr()->createAndBuildProgram("texture", "texture_vs", "texture_fs")) return false;
    
    
    return true;
}

void BootStrapper::touchBegin(float x, float y)
{
    if (_mouseJoint)
    {
        return;
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
}

void BootStrapper::touchEnd(float x, float y)
{
    _focus = 0;
    
    if (_mouseJoint)
    {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = 0;
    }
}

void BootStrapper::touchMoved(float x, float y, float previousX, float previousY)
{    
    if (_mouseJoint)
    {
        _mouseJoint->SetTarget(b2Vec2(p2m(x), p2m(y)));
    }
}

bool BootStrapper::ReportFixture(b2Fixture *fixture)
{
    if(fixture)
        _focus = fixture->GetBody();
}
