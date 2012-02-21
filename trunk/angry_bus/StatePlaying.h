#ifndef _StatePlaying_
#define _StatePlaying__
#include "IState.h"
#include "Node.h"
#include "Timer.h"
class StatePlaying : public IState, public ITimerHandler
{
public:
    StatePlaying();
    ~StatePlaying();

    void render();
    void update(float secondsElapsed);
    virtual void start();
    
    virtual bool touchBegin(float x, float y);
    virtual bool touchMoved(float x, float y, float previousX, float previousY);
    virtual bool touchEnd(float x, float y);
    //
    virtual void onTimer(int sequence);
public:
    bool loadScene(eScene c);
    bool isInBus(Entity* e);
    bool isReady();
    int get001(int score);
    int get010(int score);
    int get100(int score);
    void nextLevel();
    void theSameLevelAgain();
    void createPassengers(int num);
    bool isWinner();
    void onWinner();
    void onLoser();
    void stopThisLevel();
    void changeTimer(int i);
private:
    void resetTimer();
    void beginLevel();
    void resetPassengers();
private:
    Node<Entity>* _uiRoot;
    Node<Entity>* _uiResult;
    std::vector<Entity*> _passengers;
    std::vector<Entity*> _passengersPool;
    Entity* _ready_go;
    Entity* _clock;
    Entity* _count_down01;
    Entity* _count_down10;
//    int _ready_go_time;
    int _working_time;
    int _score;
    std::vector<std::string> _scoreTextures;
    Timer _ready_timer;
    Timer _go_timer;
    Timer _count_down_timer;
    //bool _isReady;
    bool _isTimeOut;
    int _level;
    eScene _scene;
    int _timer_offset;
};
#endif

