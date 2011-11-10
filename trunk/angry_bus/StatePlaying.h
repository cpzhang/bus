#ifndef _StatePlaying_
#define _StatePlaying__
#include "IState.h"
#include "Node.h"
class StatePlaying : public IState
{
public:
    StatePlaying();
    ~StatePlaying();

    void render();
    void update(float secondsElapsed);
    
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);
private:
    TransformationNode* _uiRoot;
};
#endif

