#ifndef _bootstrapper_
#define _bootstrapper_

#include "IRender.h"
#include <vector>
#include "ITouch.h"

class BootStrapper: public ITouch
{
public:
    BootStrapper();
    ~BootStrapper();

    bool initSingletons();
    bool create();
    void destroy();
    void applyRender(eRender e);
    void setViewPort(int width, int height);
    void run(float secondsElapsed);
    void memoryWarning();
    //
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);
    
private:
    void update(float secondsElapsed);
    void render();
    bool registerPrograms();
};

#endif
