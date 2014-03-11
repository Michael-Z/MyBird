//
//  AniButton.cpp
//  MyFish
//
//  Created by yuchen on 14-2-28.
//
//

#include "AniButton.h"
const int AniButtonDownAction = 1;

AniButton::AniButton():aniButton_up(NULL),aniButton_down(NULL),aniButton_label(NULL)
{
    
}

AniButton::~AniButton()
{
    
}

bool AniButton::init(const int bid, CCNode *upNode, CCNode *downNode, int type, CCNode *label)
{
    if (!CCNode::init()) {
        return false;
    }
    
    aniButton_bid = bid;
    aniButton_up = upNode;
    if (downNode != NULL) {
        aniButton_down = downNode;
    }
    aniButton_type = type;
    if (label != NULL) {
        aniButton_label = label;
    }
    
    CCSize size = aniButton_up->getContentSize();
    this->setContentSize(size);
    aniButton_up->setAnchorPoint(ccp(0.5, 0.5));
    aniButton_up->setPosition(size.width * 0.5, size.height * 0.5);
    this->addChild(aniButton_up);
    
    if (aniButton_down != NULL) {
        aniButton_down->setAnchorPoint(ccp(0.5, 0.5));
        aniButton_down->setPosition(size.width * 0.5, size.height * 0.5);
        this->addChild(aniButton_down);
        aniButton_down->setVisible(false);
    }
    
    if (aniButton_label != NULL) {
        aniButton_label->setAnchorPoint(ccp(0.5, 0.5));
        aniButton_label->setPosition(size.width * 0.5, size.height * 0.5);
        this->addChild(aniButton_label);
    }
    
    this->setAniNodeHotRect(CCRectMake(0, 0, size.width, size.height));
    
    return true;
}

AniButton* AniButton::create(const int bid, cocos2d::CCNode *upNode, cocos2d::CCNode *downNode, int type, cocos2d::CCNode *label)
{
    AniButton *abtn = new AniButton();
    if (abtn && abtn->init(bid, upNode, downNode, type, label)) {
        abtn->autorelease();
        return abtn;
    }
    else {
        CC_SAFE_DELETE(abtn);
        return NULL;
    }
}

void AniButton::touch()
{
    if (aniButton_type == 1) {
        if (aniButton_down != NULL) {
            aniButton_down->setVisible(true);
            aniButton_up->setVisible(false);
        }
        else {
            CCScaleTo *scale = CCScaleTo::create(0.1, 1.2);
            CCSequence *seq = CCSequence::create(scale, CCScaleTo::create(0.1, 1), NULL);
            //scale->setTag(AniButtonDownAction);
            aniButton_up->runAction(seq);
        }
    }
}

void AniButton::click()
{
    if (aniButton_type == 1) {
        if (aniButton_down != NULL) {
            aniButton_down->setVisible(false);
            aniButton_up->setVisible(true);
        }
        else {
//            aniButton_up->stopActionByTag(AniButtonDownAction);
//            aniButton_up->setScale(1.2);
//            CCScaleTo *scale = CCScaleTo::create(0.1, 1);
//            aniButton_up->runAction(scale);
        }
    }
    else if (aniButton_type == 2) {
        if (aniButton_up->isVisible()) {
            aniButton_up->setVisible(false);
            aniButton_down->setVisible(true);
        }
        else {
            aniButton_up->setVisible(true);
            aniButton_down->setVisible(false);
        }
    }
}









