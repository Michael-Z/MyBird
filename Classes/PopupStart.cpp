//
//  PopupStart.cpp
//  MyBird
//
//  Created by yuchen on 14-3-4.
//
//

#include "PopupStart.h"
#include "Utils.h"
#include "GameGlobal.h"

PopupStart::PopupStart(CCScene *scene, const int zorder, PopupEventDelegate *delegate):_scene(scene), _zorder(zorder), _delegate(delegate), _lastPressedItem(-1)
{
    
}

PopupStart::~PopupStart()
{
    if (_buttonArray != NULL) {
        CC_SAFE_RELEASE_NULL(_buttonArray);
    }
}

PopupStart* PopupStart::create(cocos2d::CCScene *scene, const int zorder, PopupEventDelegate *delegate)
{
    PopupStart *pStart = new PopupStart(scene, zorder, delegate);
    if (pStart && pStart->init()) {
        pStart->autorelease();
        return pStart;
    }
    else {
        CC_SAFE_DELETE(pStart);
        return NULL;
    }
}

bool PopupStart::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    //vars
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);
    
    //title
    title = Utils::createSprite("title");
    title->setPosition(ccpAdd(center, ccp(0, 90)));
    this->addChild(title);
    
    //play btn
    play = AniButton::create(KMenuRestart, Utils::createSprite("btn_play"));
    play->setAnchorPoint(ccp(0.5, 0.5));
    play->setPosition(ccpAdd(center, ccp(-60, -60)));
    this->addChild(play);
    
    //record
    share = AniButton::create(KMenuRecord, Utils::createSprite("btn_wx"));
    share->setAnchorPoint(ccp(0.5, 0.5));
    share->setPosition(ccpAdd(center, ccp(60, -60)));
    this->addChild(share);
    
    //buttonArray
    _buttonArray = CCArray::create();
    _buttonArray->retain();
    _buttonArray->addObject(play);
    _buttonArray->addObject(share);
    
    
    //touch events
    this->setTouchEnabled(true);
    
    //add
    _scene->addChild(this, _zorder, KLayerTagPopupStart);
    
    return true;
}

void PopupStart::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -_zorder, true);
}

bool PopupStart::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    
    _lastPressedItem = Utils::buttonHitTest(pos, _buttonArray);
    if (_lastPressedItem >= 0) {
        AniButton *btn = (AniButton*)_buttonArray->objectAtIndex(_lastPressedItem);
        btn->touch();
    }
    return true;
}

void PopupStart::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    
    if (_lastPressedItem >= 0 && _lastPressedItem == Utils::buttonHitTest(pos, _buttonArray)) {
        AniButton *btn = (AniButton*)_buttonArray->objectAtIndex(_lastPressedItem);
        btn->click();
        
        int bid = btn->getAniButtonBid();
        this->clickItem(bid);
    }
}

void PopupStart::clickItem(int bid)
{
    if (_delegate != NULL) {
        _delegate->onPopupEventMenuCommand(this, bid);
    }
    
    if (bid == KMenuRestart) {
        this->dismiss();
    }
}

void PopupStart::dismiss()
{
    if (_delegate != NULL) {
        _delegate->onPopupEventDismiss(this);
    }
    
    this->removeFromParentAndCleanup(true);
}


