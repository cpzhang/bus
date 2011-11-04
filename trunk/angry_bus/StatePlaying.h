#ifndef _StatePlaying_
#define _StatePlaying__
#include "IState.h"
class StatePlaying : public IState
{
public:
    StatePlaying();
    ~StatePlaying();

    void render();
    void update(float secondsElapsed);
private:
};
#endif

