//
//  AniButton.h
//  MyFish
//
//  Created by yuchen on 14-2-28.
//
//

#ifndef __MyFish__AniButton__
#define __MyFish__AniButton__

#include "cocos2d.h"
#include "AniNode.h"

USING_NS_CC;

class AniButton : public AniNode
{
public:
    AniButton();
    ~AniButton();
    virtual bool init(const int bid, CCNode *upNode, CCNode *downNode, int type);
    static AniButton* create(const int bid, CCNode *upNode, CCNode *downNode = NULL, int type = 1);
    
    //aniButton_type : 1.按下松开效果 2.切换
    CC_SYNTHESIZE(int, aniButton_type, AniButtonType);
    CC_SYNTHESIZE_READONLY(int, aniButton_bid, AniButtonBid);
    
    void touch();
    void click();
    
private:
    CCNode *aniButton_up, *aniButton_down;
};

#endif /* defined(__MyFish__AniButton__) */
