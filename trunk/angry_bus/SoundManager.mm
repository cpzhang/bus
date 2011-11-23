#include "SoundManager.h"
#include <AVFoundation/AVFoundation.h>

AVAudioPlayer* g_player = 0;

SoundManager::SoundManager()
:_enable(true)
{
}

SoundManager::~SoundManager()
{
    [g_player release];
}

void SoundManager::play(const std::string &name)
{
    
}

void SoundManager::play()
{
    _enable = true;
    [g_player play];
}

void SoundManager::stop()
{
    [g_player pause];
    _enable = false;
}

bool SoundManager::isEnable()
{
    return _enable; 
}

bool SoundManager::create()
{
    // Check for the file. "Drumskul" was released as a public domain audio loop on archive.org as part of "loops2try2". 
    NSError *error;
    NSString *path = [[NSBundle mainBundle] pathForResource:@"s" ofType:@"mp3"];
    if (![[NSFileManager defaultManager] fileExistsAtPath:path]) return NO;
    
    // Initialize the player
    g_player = [[AVAudioPlayer alloc] initWithContentsOfURL:[NSURL fileURLWithPath:path] error:&error];
    if (!g_player)
    {
        NSLog(@"Error: %@", [error localizedDescription]);
        return NO;
    }
    
    // Prepare the player and set the loops to, basically, unlimited
    [g_player prepareToPlay];
    [g_player setNumberOfLoops:999999];
    
    return true;
}