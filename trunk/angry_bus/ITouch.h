#ifndef _ITouch_
#define _ITouch_
struct ITouch
{
    virtual void touchBegin(float x, float y) = 0;
    virtual void touchMoved(float x, float y, float previousX, float previousY) = 0;
    virtual void touchEnd(float x, float y) = 0;
};
#endif
