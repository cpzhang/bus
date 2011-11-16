#include "SoundManager.h"

SoundManager::SoundManager()
:_enable(true)
{
    
}

SoundManager::~SoundManager()
{
    
}

void SoundManager::play(const std::string &name)
{
    
}

void SoundManager::play()
{
    _enable = true;
}

void SoundManager::stop()
{
    _enable = false;
}

bool SoundManager::isEnable()
{
    return _enable; 
}