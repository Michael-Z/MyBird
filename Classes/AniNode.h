//
//  AniNode.h
//  testShao3
//
//  Created by shaozhen on 14-2-22.
//
//

#ifndef __testShao3__AniNode__
#define __testShao3__AniNode__

#include "cocos2d.h"

USING_NS_CC;

class AniNode : public CCNode
{
public:
    AniNode();
    
    virtual bool init();
    
    virtual void update(float delta);
    
    CC_SYNTHESIZE(CCPoint, aniNode_moveSpeed, AniNodeMoveSpeed);
    CC_SYNTHESIZE(CCPoint, aniNode_accMoveSpeed, AniNodeAccMoveSpeed);
    CC_SYNTHESIZE(float, aniNode_rotateSpeed, AniNodeRotateSpeed);
    CC_SYNTHESIZE(float, aniNode_accRotateSpeed, AniNodeAccRotateSpeed);
    
    //hot rect
    virtual void setAniNodeHotRect(const CCRect &rect);
    virtual void scaleAniNodeHotRect(float flactor);
    virtual void scaleAniNodeHotRect(float flactorX, float flactorY);
    virtual CCRect getAniNodeHotRect();
private:
    CCRect aniNode_hotRect;

};

#endif /* defined(__testShao3__AniNode__) */
