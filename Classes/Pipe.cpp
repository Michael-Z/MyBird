//
//  Pipe.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-18.
//
//

#include "Pipe.h"
#include "Utils.h"

Pipe::Pipe(int idx):isPassed(false), pipeIndex(idx), doHasGold(false){
    
}

Pipe::~Pipe(){
    
}

Pipe* Pipe::create(int idx)
{
    Pipe *pi = new Pipe(idx);
    if (pi && pi->init()) {
        pi->autorelease();
        return pi;
    }
    else {
        CC_SAFE_DELETE(pi);
        return NULL;
    }
}

bool Pipe::init(){
    if (!AniNode::init()) {
        return false;
    }
    
    pipePadding = 50;
    int pipeTop = CCDirector::sharedDirector()->getWinSize().height -  100;
    int pipeBottom = 200;
    centerH = pipeBottom + rand() % (pipeTop - pipeBottom + 1);
    
    int count = (pipeIndex - 1) / 20 + 1;
    int nmb = count % 2 == 1 ? 1 : 2;
    
    //up
    char buffer[10];
    sprintf(buffer, "pipeUp_%d", nmb);
    pipeUp = Utils::createSprite(buffer);
    pipeUp->setAnchorPoint(ccp(0.0, 1.0));
    pipeUp->setPosition(ccp(0.0, centerH - pipePadding));
    this->addChild(pipeUp);
    this->setContentSize(CCSizeMake(pipeUp->getContentSize().width, pipeUp->getContentSize().height + 2 * pipePadding));
    
    
    //down
    char bufferDown[10];
    sprintf(bufferDown, "pipeDown_%d", nmb);
    pipeDown = Utils::createSprite(bufferDown);
    pipeDown->setAnchorPoint(ccp(0.0, 0.0));
    pipeDown->setPosition(ccp(0.0, centerH + pipePadding));
    this->addChild(pipeDown);
    
    //gold
    int has = rand() % 2;
    if (has == 1) {
        //gold
        gold = Utils::createSprite("gold_1");
        this->addChild(gold);
        gold->setPosition(ccp(this->getContentSize().width * 0.5, centerH));
        
        CCArray *goldAnimArray = Utils::createAnimArray("gold", 4);
        CCAnimation *goldAnimation = CCAnimation::createWithSpriteFrames(goldAnimArray, 0.1f);
        CCAnimate *goldAnimate = CCAnimate::create(goldAnimation);
        gold->runAction(CCRepeatForever::create(goldAnimate));
        
        //add
        add = Utils::createSprite("addOne");
        add->setPosition(ccpAdd(gold->getPosition(), ccp(0, 10)));
        this->addChild(add);
        add->setVisible(false);
        
        doHasGold = true;
    }
    else {
        gold = NULL;
        add = NULL;
        doHasGold = false;
    }
    
    return true;
}

float Pipe::getCenterH(){
    return centerH;
}

float Pipe::getPipePadding(){
    return pipePadding;
}

void Pipe::setPassed(const bool state)
{
    isPassed = state;
}

bool Pipe::getPassed()
{
    return isPassed;
}

bool Pipe::hasGold()
{
    return doHasGold;
}

CCRect Pipe::getGoldHotRect()
{
    CCPoint poi = this->convertToWorldSpace(CCPointZero);
    return CCRectMake(poi.x + gold->getPositionX() - gold->getContentSize().width * 0.5, poi.y + gold->getPositionY() - gold->getContentSize().height * 0.5, gold->getContentSize().width, gold->getContentSize().height);
}

void Pipe::eatGold()
{
    doHasGold = false;
    this->removeChild(gold);
        
    add->setVisible(true);
    add->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(0, 30)), CCCallFunc::create(this, callfunc_selector(Pipe::cleanAdd)), NULL));
    
}

void Pipe::cleanAdd()
{
    this->removeChild(add);
}


