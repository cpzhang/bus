#ifndef _RenderES2_
#define _RenderES2_

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "IRender.h"
#include "Color.h"
class RenderES2 : public IRender
{
public:
    virtual void setViewPort(int width, int height);
    virtual void setClearColor(float red, float green, float blue, float alpha);
    virtual void clear(bool color, bool depth);
    virtual void beginFrame(bool color, bool depth);
    virtual void endFrame();
    virtual void update(float time_step);
    virtual void setVertexAttributePointer(unsigned int index,
                                           unsigned int  size,
                                           unsigned int  type,
                                           bool  normalized,
                                           int  stride,
                                           const void*  pointer);
    virtual void drawArrays(int mode, int first, int count);
    virtual void enable(unsigned int cap);
    virtual void disable(unsigned int cap);
    virtual bool isEnabled(unsigned int cap);
    virtual void blendFunc(unsigned int sfactor, unsigned int dfactor);
public:
    RenderES2();
    ~RenderES2();
private:
    GLuint  _frame_buffer;
    GLuint  _render_buffer;
    GLuint  _depth_buffer;
    GLint   _width;
    GLint   _height;
    Color   _clearColor;
};
#endif
