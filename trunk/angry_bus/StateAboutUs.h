#ifndef _StateAboutUs__
#define _StateAboutUs___
#include "IState.h"
#include "Node.h"

class StateAboutUs : public IState
{
public:
    StateAboutUs();
    ~StateAboutUs();

    void render();
    void update(float secondsElapsed);
    virtual void start();
    
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);
private:
    Node<Entity>* _uiRoot;
};
#endif

