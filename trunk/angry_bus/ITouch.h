#ifndef _ITouch_
#define _ITouch_
struct ITouch
{
    virtual bool touchBegin(float x, float y) = 0;
    virtual bool touchMoved(float x, float y, float previousX, float previousY) = 0;
    virtual bool touchEnd(float x, float y) = 0;
};
#endif
