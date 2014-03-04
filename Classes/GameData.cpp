//
//  GameData.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-21.
//
//

#include "GameData.h"

#define ANDROIDSAVEBYUSERDEFAULT    1
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../proj.android/jni/hellocpp/UtilsJNI.h"
#endif

GameData::GameData()
{
};

GameData::~GameData()
{
};

static GameData* _instance = NULL;

GameData* GameData::instance()
{
    if (_instance == NULL) {
        _instance = new GameData();
        
        if (!_instance->init()) {
            CC_SAFE_DELETE(_instance);
        }
        
        if (!_instance->load()) {
            _instance->initData();
        }
        
    }
    return _instance;
}

bool GameData::init()
{
    return  true;
}

bool GameData::load()
{
    
#if (ANDROIDSAVEBYUSERDEFAULT == 1 && CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    gd_isBeginner = JNI_getBool("IsBeginner", true);
	if (gd_isBeginner) {
		return false;
	}
    gd_highScore = JNI_getInt("HighScore", 0);
    gd_gold = JNI_getInt("Gold", 0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCUserDefault* read = CCUserDefault::sharedUserDefault();
    gd_isBeginner = read->getBoolForKey("IsBeginner", true);
    if (gd_isBeginner) {
        return false;
    }
    gd_highScore = read->getIntegerForKey("HighScore", 0);
    gd_gold = read->getIntegerForKey("Gold", 0);
#endif
    
    return true;
}

void GameData::initData()
{
    gd_isBeginner = false;
    gd_highScore = 0;
    gd_gold = 0;
    
    saveSettings();
}

void GameData::saveSettings()
{
    
#if (ANDROIDSAVEBYUSERDEFAULT == 1 && CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JNI_setBool("IsBeginner", gd_isBeginner);
    JNI_setInt("HighScore", gd_highScore);
    JNI_setInt("Gold", gd_gold);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCUserDefault* write = CCUserDefault::sharedUserDefault();
    write->setBoolForKey("IsBeginner", gd_isBeginner);
    write->setIntegerForKey("HighScore", gd_highScore);
    write->setIntegerForKey("Gold", gd_gold);
    write->flush();
#endif
    
}

void GameData::setGDHighScore(const int score)
{
    gd_highScore = score;
    saveSettings();
}

int GameData::getGDHighScore()
{
    return gd_highScore;
}

void GameData::setGDGold(const int gold)
{
    gd_gold = gold;
    saveSettings();
}

int GameData::getGDGold()
{
    return gd_gold;
}




