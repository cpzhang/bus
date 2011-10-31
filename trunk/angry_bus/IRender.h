//
//  IRender.h
//  angry_bus
//
//  Created by suning on 11-10-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
//
#ifndef _IRender_
#define _IRender_

enum eRender
{
    eRender_ES1,
    eRender_ES2,
    eRender_Size,
};

struct IRender
{
    virtual void setViewPort(int width, int height) = 0;
    virtual void setClearColor(float red, float green, float blue, float alpha) = 0;
    virtual void clear(bool color, bool depth) = 0;
    virtual void beginFrame(bool color, bool depth) = 0;
    virtual void update(float time_step) = 0;
    virtual void setVertexAttributePointer(unsigned int index,
                                           unsigned int  size,
                                           unsigned int  type,
                                           bool  normalized,
                                           int  stride,
                                           const void*  pointer) = 0;
    virtual void drawArrays(int mode, int first, int count) = 0;
    virtual ~IRender(){};
    static IRender* create(eRender e);
};

#endif