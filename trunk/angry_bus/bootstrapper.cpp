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
    _triangle = EntityManager::getInstancePtr()->createEntity("triangle");
    return true;
}

void BootStrapper::destroy()
{
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
}

void BootStrapper::setViewPort(int width, int height)
{
    ServicesProvider::getInstancePtr()->getRender()->setViewPort(width, height);
}