//
//  RenderES2.cpp
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "RenderES2.h"
RenderES2::RenderES2()
{
   
}

void RenderES2::setViewPort(int width, int height)
{
    //
    glGenRenderbuffers(1, &_render_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer);
    //
    glGenRenderbuffers(1, &_depth_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    //
    glGenFramebuffers(1, &_frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _render_buffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depth_buffer);
    //
    glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer);
    //
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}

void RenderES2::update(float time_step)
{
    
}

RenderES2::~RenderES2()
{
    glDeleteFramebuffers(1, &_frame_buffer);
    glDeleteRenderbuffers(1, &_render_buffer);
}

void RenderES2::setClearColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void RenderES2::clear(bool color, bool depth)
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

void RenderES2::beginFrame(bool color, bool depth)
{
    glClearColor(0.0, 0.5, 0.0, 1.0);
    clear(color, depth); 
}