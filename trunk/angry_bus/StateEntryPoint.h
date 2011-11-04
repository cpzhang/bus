#ifndef _StateEntryPoint_
#define _StateEntryPoint_
#include "IState.h"
class StateEntryPoint : public IState
{
public:
    StateEntryPoint();
    ~StateEntryPoint();

    void render();
    void update(float secondsElapsed);
private:
    Node<Entity>* _uiRoot;
}
#endif
