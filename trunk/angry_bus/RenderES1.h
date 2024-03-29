#ifndef _RenderES1_
#define _RenderES1_

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "IRender.h"

class RenderES1 : public IRender
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
    virtual bool isError();
public:
    RenderES1();
    ~RenderES1();
private:
    GLuint  _frame_buffer;
    GLuint  _render_buffer;
};

#endif
