//
//  Color.cpp
//  angry_bus
//
//  Created by suning on 11-10-31.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Color.h"
Color::Color()
{
    red = 0.0;
    green = 0.0;
    blue = 0.0;
    alpha = 0.0;
}
Color::Color(float r, float g, float b, float a)
{
    red = r; green = g; blue = b; alpha = a;
}
const Color Color::White(1.0, 1.0, 1.0, 1.0);