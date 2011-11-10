#include "StateMachine.h"
#include "StateEntryPoint.h"
#include "StateAboutUs.h"
#include "StatePlaying.h"

StateMachine::StateMachine()
:_currentState(eState_EntryPoint)
{
    
}

StateMachine::~StateMachine()
{
    for (size_t i = 0; i != _states.size(); ++i)
    {
        if (_states[i])
        {
            delete _states[i];
            _states[i] = 0;
        }
    }
    _states.clear();
}

bool StateMachine::createStates()
{
    _states.push_back(new StateEntryPoint);
    _states.push_back(new StateAboutUs);
    _states.push_back(0);
    _states.push_back(new StatePlaying);
    
    return true;
}

void StateMachine::goNext(eState s)
{
    _currentState = s;
}

void StateMachine::render()
{
    _states[_currentState]->render();
}

void StateMachine::update(float secondsElapsed)
{
    _states[_currentState]->update(secondsElapsed);    
}

bool StateMachine::touchBegin(float x, float y)
{
    return _states[_currentState]->touchBegin(x, y);
}

bool StateMachine::touchMoved(float x, float y, float previousX, float previousY)
{
    return _states[_currentState]->touchMoved(x, y, previousX, previousY);
}

bool StateMachine::touchEnd(float x, float y)
{
    return _states[_currentState]->touchEnd(x, y);
}