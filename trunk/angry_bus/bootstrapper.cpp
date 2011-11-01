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

bool BootStrapper::create()
{
    new ServicesProvider;
    new EntityManager;
    new ShaderManager;
    new ProgramManager;
    _triangle = EntityManager::getInstancePtr()->createEntity("triangle");
    return true;
}

void BootStrapper::destroy()
{
    delete ProgramManager::getInstancePtr();
    delete ShaderManager::getInstancePtr();
    delete ServicesProvider::getInstancePtr();
    delete EntityManager::getInstancePtr();
}
void BootStrapper::run(float secondsElapsed)
{
    update(secondsElapsed);
    render();
}

void BootStrapper::update(float secondsElapsed)
{
    
}

void BootStrapper::render()
{
    ServicesProvider::getInstance().getRender()->beginFrame(true, false);
    _triangle->render();
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
}
