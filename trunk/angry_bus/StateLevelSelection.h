#ifndef _StateLevelSelection_
#define _StateLevelSelection__
#include "IState.h"
#include "Node.h"
#include "ITouch.h"
class StateLevelSelection : public IState
{
public:
    StateLevelSelection();
    ~StateLevelSelection();

    void render();
    void update(float secondsElapsed);
    virtual void start();
    
    //
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);
private:
    Node<Entity>* _uiRoot;
};
#endif

