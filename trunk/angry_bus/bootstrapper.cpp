//
//  bootstrapper.cpp
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "bootstrapper.h"
#include "ServicesProvider.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ShaderManager.h"
#include "ProgramManager.h"
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
    
    return true;
}

bool BootStrapper::create()
{
    _triangle = EntityManager::getInstancePtr()->createEntity("triangle");
    registerPrograms();
    ServicesProvider::getInstancePtr()->getRender()->setClearColor(0.0, 0.0, 0.3, 1.0);

    //
    _world = new b2World(b2Vec2(0, 10));
    _box2DRender = new box2DRender;
    _box2DRender->SetFlags(b2Draw::e_shapeBit);
    _world->SetDebugDraw(_box2DRender);
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
}

void BootStrapper::render()
{
    ServicesProvider::getInstance().getRender()->beginFrame(true, false);
    _triangle->render();
    _world->DrawDebugData();
    ServicesProvider::getInstance().getRender()->endFrame();
}

void BootStrapper::setViewPort(int width, int height)
{
    ServicesProvider::getInstancePtr()->getRender()->setViewPort(width, height);
}

bool BootStrapper::registerPrograms()
{
    ShaderManager::getInstancePtr()->createAndBuildShader("vs", "fuck.vs", Shader::eShaderType_Vertex);
    ShaderManager::getInstancePtr()->createAndBuildShader("fs", "fuck.fs", Shader::eShaderType_Fragment);
    ProgramManager::getInstancePtr()->createAndBuildProgram("fuck", "vs", "fs");
    
    return true;
}
