#include "RenderES2.h"
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
RenderES2::RenderES2()
{
   
}

void RenderES2::setViewPort(int width, int height)
{
    _width = width;
    _height = height;
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
/*
 FBO itself does not have any image storage(buffer) in it. Instead, we must attach framebuffer-attachable images (texture or renderbuffer objects) to the FBO. This mechanism allows that FBO quickly switch (detach and attach) the framebuffer-attachable images in a FBO. It is much faster to switch framebuffer-attachable images than to switch between FBOs. And, it saves unnecessary data copies and memory consumption. For example, a texture can be attached to multiple FBOs, and its image storage can be shared by multiple FBOs.
*/
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _render_buffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depth_buffer);
    //
    glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer);
/*
The rules of FBO completeness are:
The width and height of framebuffer-attachable image must be not zero.
If an image is attached to a color attachment point, then the image must have a color-renderable internal format. (GL_RGBA, GL_DEPTH_COMPONENT, GL_LUMINANCE, etc)
If an image is attached to GL_DEPTH_ATTACHMENT_EXT, then the image must have a depth-renderable internal format. (GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT24_EXT, etc)
If an image is attached to GL_STENCIL_ATTACHMENT_EXT, then the image must have a stencil-renderable internal format. (GL_STENCIL_INDEX, GL_STENCIL_INDEX8_EXT, etc)
FBO must have at least one image attached.
All images attached a FBO must have the same width and height.
All images attached the color attachment points must have the same internal format.
*/
    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(result != GL_FRAMEBUFFER_COMPLETE)
    {
	std::cout<<"Failed to create FBO"<<std::endl;
    }
    //
    glViewport(0, 0, width, height);
    //glEnable(GL_DEPTH_TEST);
}

void RenderES2::update(float time_step)
{
    
}

RenderES2::~RenderES2()
{
    glDeleteFramebuffers(1, &_frame_buffer);
    glDeleteRenderbuffers(1, &_render_buffer);
    glDeleteRenderbuffers(1, &_depth_buffer);
}

void RenderES2::setClearColor(float red, float green, float blue, float alpha)
{
    _clearColor.red = red;
    _clearColor.green = green;
    _clearColor.blue = blue;
    _clearColor.alpha = alpha;
    glClearColor(_clearColor.red, _clearColor.green, _clearColor.blue, _clearColor.alpha);
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
    clear(color, depth); 
}

void RenderES2::setVertexAttributePointer(unsigned int index, unsigned int size, unsigned int type, bool normalized, int stride, const void *pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

void RenderES2::drawArrays(int mode, int first, int count)
{
    glDrawArrays(mode, first, count);
}

void RenderES2::enable(unsigned int cap)
{
    glEnable(cap);
}
void RenderES2::disable(unsigned int cap)
{
    glDisable(cap);
}
bool RenderES2::isEnabled(unsigned int cap)
{
    return glIsEnabled(cap);
}
void RenderES2::endFrame()
{
    [[EAGLContext currentContext] presentRenderbuffer:GL_RENDERBUFFER];
}
