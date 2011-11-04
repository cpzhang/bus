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

BootStrapper::BootStrapper()
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

    return true;
}

bool BootStrapper::create()
{
    _triangle = EntityManager::getInstancePtr()->createEntity("triangle");
    registerPrograms();
    ServicesProvider::getInstancePtr()->getRender()->setClearColor(0.0, 0.0, 0.3, 1.0);

    //
    _world = new b2World(b2Vec2(0, -10));
    _box2DRender = new box2DRender;
    _box2DRender->SetFlags(b2Draw::e_shapeBit);
    _world->SetDebugDraw(_box2DRender);
    {
        //body definition
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;
        
        //shape definition
        b2PolygonShape polygonShape;
        polygonShape.SetAsBox(10, 10); //a 2x2 rectangle
        
        //fixture definition
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &polygonShape;
        myFixtureDef.density = 1;
        
        //create dynamic bodies
        for (int i = 0; i < 10; i++) {
            myBodyDef.position.Set(12 * i, 300);
            _world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
        }
        
        //a static body
        myBodyDef.type = b2_staticBody;
        myBodyDef.position.Set(10, 20);
        b2Body* staticBody = _world->CreateBody(&myBodyDef);
        
        //add a fixture to the static body
        polygonShape.SetAsBox( 50, 10, b2Vec2(100, 100), 10);
        staticBody->CreateFixture(&myFixtureDef);
    }
    return true;
}

void BootStrapper::destroy()
{
    delete ProgramManager::getInstancePtr();
    delete ShaderManager::getInstancePtr();
    delete ServicesProvider::getInstancePtr();
    delete EntityManager::getInstancePtr();
    //
    delete _world;
}
void BootStrapper::run(float secondsElapsed)
{
    update(secondsElapsed);
    render();
}

void BootStrapper::update(float secondsElapsed)
{
    _world->Step(1.0/60.0, 8, 3);
    //_stateMachine.update(secondsElapsed);
}

void BootStrapper::render()
{
    ServicesProvider::getInstance().getRender()->beginFrame(true, false);
    _triangle->render();
    //_stateMachine.render();
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
