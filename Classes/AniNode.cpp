//
//  AniNode.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-22.
//
//

#include "AniNode.h"

AniNode::AniNode():aniNode_accMoveSpeed(ccp(0, 0)), aniNode_moveSpeed(ccp(0, 0)), aniNode_rotateSpeed(0), aniNode_accRotateSpeed(0)
{
    
}

bool AniNode::init()
{
    if (!CCNode::init()) {
        return false;
    }
    return true;
}

void AniNode::update(float delta)
{
    if (ccpLength(aniNode_moveSpeed) != 0 || ccpLength(aniNode_accMoveSpeed) != 0) {
        CCPoint dis = ccpAdd(ccpMult(aniNode_moveSpeed, delta), ccpMult(aniNode_accMoveSpeed, 0.5 * delta * delta));
        this->setPosition(ccpAdd(this->getPosition(), dis));
        aniNode_moveSpeed = ccpAdd(aniNode_moveSpeed, ccpMult(aniNode_accMoveSpeed, delta));
    }    
    
    if (aniNode_rotateSpeed != 0 || aniNode_accRotateSpeed != 0) {
        float rot = aniNode_rotateSpeed * delta + 0.5 * aniNode_accRotateSpeed * delta * delta;
        this->setRotation(this->getRotation() + rot);
        aniNode_rotateSpeed = aniNode_rotateSpeed + aniNode_accRotateSpeed * delta;
    }    
    
}

void AniNode::setAniNodeHotRect(const cocos2d::CCRect &rect)
{
    aniNode_hotRect = rect;
}

void AniNode::scaleAniNodeHotRect(float flactor)
{
    scaleAniNodeHotRect(flactor, flactor);
}

void AniNode::scaleAniNodeHotRect(float flactorX, float flactorY)
{
    CCSize size = this->getContentSize();
    CCPoint center = ccp(size.width * 0.5, size.height * 0.5);
    aniNode_hotRect = CCRectMake(center.x - size.width * flactorX * 0.5, center.y - size.height * flactorY * 0.5, size.width * flactorX, size.height * flactorY);
}

CCRect AniNode::getAniNodeHotRect()
{
    if (this->isVisible()) {
        CCPoint pos = this->convertToWorldSpace(CCPointZero);
        return CCRectMake(pos.x + aniNode_hotRect.origin.x, pos.y + aniNode_hotRect.origin.y, aniNode_hotRect.size.width, aniNode_hotRect.size.height);
    }
    else {
        return CCRectMake(0, 0, 0, 0);
    }
}


