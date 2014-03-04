//
//  AudioController.cpp
//  MyFish
//
//  Created by yuchen on 14-3-1.
//
//

#include "AudioController.h"

#define AudioExtension ".mp3"
#define AudilPath       "music/"

AudioController* _instance = NULL;

AudioController::AudioController()
{
    
}

AudioController::~AudioController()
{
    
}

AudioController* AudioController::sharedInstance()
{
    if (_instance == NULL) {
        _instance = new AudioController();
        if (!_instance->init()) {
            CC_SAFE_DELETE(_instance);
        }
    }
    return  _instance;
}

bool AudioController::init()
{
    return true;
}

const char* AudioController::getFullPath(const char *name)
{
    string full = AudilPath + string(name) +AudioExtension;
    return full.c_str();
}

//bg
void AudioController::preloadBgMusic(const char *name)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(this->getFullPath(name));
}

void AudioController::playBgMusic(const char *name, bool loop)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(this->getFullPath(name), loop);
}

void AudioController::stopBgMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void AudioController::pauseBgMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AudioController::resumeBgMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AudioController::rePlayBgMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
}

bool AudioController::isBgMusicPlaying()
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}

void AudioController::setBgMusicVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

float AudioController::getBgMusicVolume()
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}

//effect
void AudioController::preloadEffect(const char *name)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(this->getFullPath(name));
}

unsigned int AudioController::playEffect(const char *name, bool loop)
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(this->getFullPath(name), loop);
}

void AudioController::stopEffect(unsigned int soundId)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(soundId);
}

void AudioController::stopAllEffects()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void AudioController::pauseEffect(unsigned int soundId)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseEffect(soundId);
}

void AudioController::resumeEffect(unsigned int soundId)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeEffect(soundId);
}

void AudioController::pauseAllEffects()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void AudioController::resumeAllEffects()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void AudioController::unloadEffect(const char *name)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect(this->getFullPath(name));
}

void AudioController::setEffectsVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

float AudioController::getEffectsVolume()
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->getEffectsVolume();
}

//end
void AudioController::end()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->end();
}







