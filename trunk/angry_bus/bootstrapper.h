#ifndef _bootstrapper_
#define _bootstrapper_

#include "IRender.h"
#include <vector>
#include "StateMachine.h"
#include "ITouch.h"
#include "b2WorldCallbacks.h"
#include "b2MouseJoint.h"
#include "b2DistanceJoint.h"

class Entity;
class b2World;
class b2Draw;
class b2Fixture;

class BootStrapper: public ITouch, public b2QueryCallback
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
    //
    virtual void touchBegin(float x, float y);
    virtual void touchMoved(float x, float y, float previousX, float previousY);
    virtual void touchEnd(float x, float y);
    
    //
    virtual bool ReportFixture(b2Fixture* fixture);
private:
    void update(float secondsElapsed);
    void render();
    bool registerPrograms();
private:
    b2World*    _world;
    b2Draw*     _box2DRender;
    b2Body*     _focus;
    b2Body*     _groundBody;
    b2MouseJoint* _mouseJoint;
};

#endif
