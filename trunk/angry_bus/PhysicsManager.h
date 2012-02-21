#ifndef _PhysicsManager_
#define _PhysicsManager_
#include "ITouch.h"
#include "b2WorldCallbacks.h"
#include "b2MouseJoint.h"
#include "b2DistanceJoint.h"
#include "Singleton.h"
#include "Event.h"
class Entity;
class b2World;
class b2Draw;
class b2Fixture;

class PhysicsManager: public ITouch, public b2QueryCallback, public Singleton<PhysicsManager>,
                      public IEventHandler
{
public:
    PhysicsManager();
    ~PhysicsManager();
public:
    //
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);
    
    //
    virtual bool ReportFixture(b2Fixture* fixture);
    
    //
    virtual void onEvent(sEvent* e); 
public:
    void update(float secondsElapsed);
    void render();
    b2Body* createBody(float x, float y);
private:
    b2World*    _world;
    b2Draw*     _box2DRender;
    b2Body*     _focus;
    b2Body*     _groundBody;
    b2MouseJoint* _mouseJoint;
};
#endif