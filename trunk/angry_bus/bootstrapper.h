//
//  bootstrapper.h
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _bootstrapper_
#define _bootstrapper_

#include "IRender.h"
class Entity;
class BootStrapper
{
public:
    BootStrapper();
    ~BootStrapper();

    bool create();
    void destroy();
    void applyRender(eRender e);
    void setViewPort(int width, int height);
    void run(float secondsElapsed);
private:
    void update(float secondsElapsed);
    void render();
private:
    Entity* _triangle;
};

#endif