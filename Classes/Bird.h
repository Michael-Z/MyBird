//
//  Bird.h
//  testShao3
//
//  Created by shaozhen on 14-2-22.
//
//

#ifndef __testShao3__Bird__
#define __testShao3__Bird__

#include "cocos2d.h"
#include "AniNode.h"

USING_NS_CC;

class Bird : public AniNode
{
public:
    CREATE_FUNC(Bird);
    
    ~Bird();
    
    virtual bool init();
    
    void setInit(int idx);
    
    void setInit();
    
    void die();
    
    int getBirdIdx();
protected:
    CCSprite *_bird;
    
    CCArray *_birdFrams;
    
    int _birdIdx;
};



#endif /* defined(__testShao3__Bird__) */
