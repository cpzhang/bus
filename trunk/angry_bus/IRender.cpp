//
//  IRender.cpp
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "IRender.h"
#include "RenderES1.h"
#include "RenderES2.h"
IRender* IRender::create(eRender e)
{
    switch (e) {
        case eRender_ES1:
            return new RenderES1;
            break;
            
        case eRender_ES2:
            return new RenderES2;
            break;
            
        default:
            return 0;
            break;
    }
}
