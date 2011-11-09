#ifndef _StateMachine_
#define _StateMachine_
#include <vector>
#include "IState.h"
class StateMachine : public IState, public Singleton<StateMachine>
{
public:
    StateMachine();
    ~StateMachine();

    bool createStates();
    void goNext(eState s);

    virtual void render();
    virtual void update(float secondsElapsed);

private:
    std::vector<IState*> _states;
    eState _currentState;
};
#endif
