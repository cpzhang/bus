#ifndef _StateAboutUs__
#define _StateAboutUs___
#include "IState.h"
class StateAboutUs : public IState
{
public:
    StateAboutUs();
    ~StateAboutUs();

    void render();
    void update(float secondsElapsed);
private:
}
#endif

