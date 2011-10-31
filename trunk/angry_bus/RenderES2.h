//
//  RenderES2.h
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _RenderES2_
#define _RenderES2_

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "IRender.h"

class RenderES2 : public IRender
{
public:
    virtual void setViewPort(int width, int height);
    virtual void setClearColor(float red, float green, float blue, float alpha);
    virtual void clear(bool color, bool depth);
    virtual void beginFrame(bool color, bool depth);
    virtual void update(float time_step);
public:
    RenderES2();
    ~RenderES2();
private:
    GLuint  _frame_buffer;
    GLuint  _render_buffer;
    GLuint  _depth_buffer;
};
#endif