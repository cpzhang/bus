#ifndef _StateEntryPoint_
#define _StateEntryPoint_
#include "IState.h"
#include "Node.h"
#include "ITouch.h"

class Entity;
class StateEntryPoint : public IState
{
public:
    StateEntryPoint();
    ~StateEntryPoint();

    void render();
    void update(float secondsElapsed);
    virtual void start();
    
    //
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);
private:
    TransformationNode* _uiRoot;
};
#endif
