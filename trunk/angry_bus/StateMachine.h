#ifndef _StateMachine_
#define _StateMachine_
#include <vector>
#include "IState.h"
#include "Singleton.h"
#include "ITouch.h"

class StateMachine : public IState, public Singleton<StateMachine>
{
public:
    StateMachine();
    ~StateMachine();

    bool createStates();
    void goNext(eState s);

    virtual void render();
    virtual void update(float secondsElapsed);

    //
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);

private:
    std::vector<IState*> _states;
    eState _currentState;
};
#endif
