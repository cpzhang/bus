#ifndef _IState_
#define _IState_
#include "ITouch.h"
enum eState
{
    eState_EntryPoint = 0,
    eState_AboutUs,
    eState_LevelSelection,
    eState_Playing,
    eState_Size,
};

enum eScene
{
    eScene_City,
    eScene_WetLand,
    eScene_Glacier,
    eScene_Size,
};

class IState: public ITouch
{
public:
    virtual void render() = 0;
    virtual void update(float secondsElapsed) = 0;
    virtual void start() = 0;
    static bool _IsReady;
};
#endif
