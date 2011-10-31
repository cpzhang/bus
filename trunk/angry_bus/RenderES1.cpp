//
//  RenderES1.cpp
//  angry_bus
//
//  Created by suning on 11-10-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "RenderES1.h"

RenderES1::RenderES1()
{
    
}

void RenderES1::setViewPort(int width, int height)
{
    
    glGenRenderbuffersOES(1, &_render_buffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, _render_buffer);
    //
    glGenFramebuffersOES(1, &_frame_buffer);
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, _frame_buffer);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, _render_buffer);
    glViewport(0, 0, width, height);
}

void RenderES1::update(float time_step)
{
    
}

RenderES1::~RenderES1()
{
    glDeleteFramebuffersOES(1, &_frame_buffer);
    glDeleteRenderbuffersOES(1, &_render_buffer);
}

void RenderES1::setClearColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void RenderES1::clear(bool color, bool depth)
{
    GLbitfield mask = 0;
    if (color)
    {
        mask |= GL_COLOR_BUFFER_BIT;
    }
    if (depth)
    {
        mask |= GL_DEPTH_BUFFER_BIT;
    }
    glClear(mask);
}
void RenderES1::beginFrame(bool color, bool depth)
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    clear(color, depth); 
}