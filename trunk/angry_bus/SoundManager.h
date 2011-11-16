#ifndef _SoundManager_
#define _SoundManager_
#include "Singleton.h"
class SoundManager: public Singleton<SoundManager>
{
public:
    SoundManager();
    ~SoundManager();
    
    void play(const std::string& name);
    void play();
    void stop();
    bool isEnable();
private:
    bool _enable;
};
#endif
