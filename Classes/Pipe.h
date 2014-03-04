//
//  Pipe.h
//  testShao3
//
//  Created by shaozhen on 14-2-18.
//
//

#ifndef __testShao3__Pipe__
#define __testShao3__Pipe__

#include "cocos2d.h"
#include "AniNode.h"

USING_NS_CC;

class Pipe : public AniNode{

public:
    Pipe(int idx);
    virtual ~Pipe();
    virtual bool init();
    
    static Pipe* create(int idx);
    
    float getCenterH();
    
    float getPipePadding();
    
    void setPassed(const bool state);
    
    bool getPassed();
    
    bool hasGold();
    
    CCRect getGoldHotRect();
    
    void eatGold();
    
    void cleanAdd();
private:
    CCSprite *pipeUp;
    CCSprite *pipeDown;
    CCSprite *gold;
    CCSprite *add;
    
    float pipePadding;
    float centerH;
    
    bool isPassed;
    int pipeIndex;
    bool doHasGold;
};

#endif /* defined(__testShao3__Pipe__) */
