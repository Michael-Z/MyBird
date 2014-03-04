//
//  AudioController.h
//  MyFish
//
//  Created by yuchen on 14-3-1.
//
//

#ifndef __MyFish__AudioController__
#define __MyFish__AudioController__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;

class AudioController : public CCObject
{
public:
    AudioController();
    ~AudioController();
    static AudioController* sharedInstance();
    bool init();
    const char* getFullPath(const char* name);
    
    //bg
    void preloadBgMusic(const char* name);
    void playBgMusic(const char* name, bool loop = true);
    void stopBgMusic();
    void pauseBgMusic();
    void resumeBgMusic();
    void rePlayBgMusic();
    bool isBgMusicPlaying();
    void setBgMusicVolume(float volume);//0.0~1.0
    float getBgMusicVolume();
    
    //effect
    void preloadEffect(const char* name);
    unsigned int playEffect(const char* name, bool loop = false);
    void stopEffect(unsigned int soundId);
    void stopAllEffects();
    void pauseEffect(unsigned int soundId);
    void resumeEffect(unsigned int soundId);
    void pauseAllEffects();
    void resumeAllEffects();
    void unloadEffect(const char* name);
    void setEffectsVolume(float volume);//0.0~1.0
    float getEffectsVolume();
    
    //end
    void end();
};

#endif /* defined(__MyFish__AudioController__) */
