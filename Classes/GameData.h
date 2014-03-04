//
//  GameData.h
//  testShao3
//
//  Created by shaozhen on 14-2-21.
//
//

#ifndef __testShao3__GameData__
#define __testShao3__GameData__

#include "cocos2d.h"

USING_NS_CC;

class GameData : public CCObject
{
public:
    GameData();
    
    virtual ~GameData();
    
    virtual bool init();
    
    static GameData* instance();
    
    CC_PROPERTY(int, gd_highScore, GDHighScore);
    CC_PROPERTY(int, gd_gold, GDGold);
    
    
private:
    void saveSettings();
    
    bool load();
    
    void initData();

protected:
    bool gd_isBeginner;


};

#endif /* defined(__testShao3__GameData__) */
