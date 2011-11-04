#ifndef _StateLevelSelection_
#define _StateLevelSelection__
#include "IState.h"
class StateLevelSelection : public IState
{
public:
    StateLevelSelection();
    ~StateLevelSelection();

    void render();
    void update(float secondsElapsed);
private:
}
#endif

