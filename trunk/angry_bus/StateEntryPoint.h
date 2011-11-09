#ifndef _StateEntryPoint_
#define _StateEntryPoint_
#include "IState.h"
#include "Node.h"
#include "ITouch.h"

class Entity;
class StateEntryPoint : public IState, public ITouch
{
public:
    StateEntryPoint();
    ~StateEntryPoint();

    void render();
    void update(float secondsElapsed);
    
    //
    virtual void touchBegin(float x, float y);
    virtual void touchMoved(float x, float y, float previousX, float previousY);
    virtual void touchEnd(float x, float y);
private:
    TransformationNode<Entity>* _uiRoot;
};
#endif
