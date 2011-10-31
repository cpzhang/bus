//
//  IServicesProvider.cpp
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "ServicesProvider.h"

ServicesProvider::ServicesProvider()
:_render(0)
{
    
}

ServicesProvider::~ServicesProvider()
{
    delete _render;
    _render = 0;
}

IRender* ServicesProvider::getRender()
{
    return _render;
}

void ServicesProvider::setRender(eRender e)
{
    _render = IRender::create(e);
}