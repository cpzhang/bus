#ifndef angry_bus_Timer_h
#define angry_bus_Timer_h

#include "Common.h"
#include "Singleton.h"

class ITimerHandler
{
public:
    virtual void onTimer(int sequence) = 0;
};

class Timer
{
public:
    Timer()
    :_timer_handler(0), _sequence(0), _how_many_times_should_do(0), _interval(0), _last_call_stamp(0), _first_call_stamp(-1.0), _is_limit_how_many_times(false)
    {
    }
    bool operator == (const Timer* t)
    {
        return (_timer_handler == t->_timer_handler) && (_sequence == t->_sequence);
    }
    bool isMyTime()
    {
        if (_first_call_stamp >= 0)
        {
            return _last_call_stamp >= _first_call_stamp;
        }
        
        if (_is_limit_how_many_times)
        {
            return (_last_call_stamp >= _interval) && (_how_many_times_should_do > 0);
        }
        
        return (_last_call_stamp >= _interval);
    }
    void onTimer()
    {
        _timer_handler->onTimer(_sequence);
        _last_call_stamp = 0;
        if (_is_limit_how_many_times)
        {
            --_how_many_times_should_do;
        }
        if (_first_call_stamp >= 0)
        {
            _first_call_stamp = -1;
        }
    }
    ITimerHandler* _timer_handler;
    int _sequence;
    int _how_many_times_should_do;
    float _interval;
    float _last_call_stamp;
    float _first_call_stamp;
    bool _is_limit_how_many_times;
};

class TimerManager: public Singleton<TimerManager>
{
public:
    bool addTimer(Timer* t)
    {
        for (TimerVector::iterator i = _timers.begin(); i != _timers.end(); ++i)
        {
            if (*i == t)
            {
                return false;
            }
        }
        _timers.push_back(t);
        return true;
    }
    bool removeTimer(Timer* t)
    {
        for (TimerVector::iterator i = _timers.begin(); i != _timers.end(); ++i)
        {
            if (*i == t)
            {
                _timers.erase(i);
                return true;
            }
        }
        
        return false;
    }
    void update(float secondsElapsed)
    {
        for (TimerVector::iterator i = _timers.begin(); i != _timers.end(); ++i)
        {
            Timer* t = *i;
            t->_last_call_stamp += secondsElapsed;
            if (t->isMyTime()) 
            {
                t->onTimer();
            }
        }
    }
private:
    typedef std::vector<Timer*> TimerVector;
    TimerVector _timers;
};
#endif
