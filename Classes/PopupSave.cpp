//
//  PopupSave.cpp
//  MyBird
//
//  Created by yuchen on 14-3-4.
//
//

#include "PopupSave.h"
#include "Utils.h"
#include "GameGlobal.h"

PopupSave::PopupSave(CCScene *scene, const int zorder, PopupEventDelegate *delegate, int cost):_scene(scene), _zorder(zorder), _delegate(delegate), _cost(cost), _lastPressedItem(-1)
{
    
}

PopupSave::~PopupSave()
{
    if (_buttonArray != NULL) {
        CC_SAFE_RELEASE_NULL(_buttonArray);
    }
}

PopupSave* PopupSave::create(cocos2d::CCScene *scene, const int zorder, PopupEventDelegate *delegate, int cost)
{
    PopupSave *pStart = new PopupSave(scene, zorder, delegate, cost);
    if (pStart && pStart->init()) {
        pStart->autorelease();
        return pStart;
    }
    else {
        CC_SAFE_DELETE(pStart);
        return NULL;
    }
}

bool PopupSave::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    //vars
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);
    
    //panel
    _panel = Utils::createSprite("savePanel");
    _panel->setPosition(center);
    this->addChild(_panel);
    
    //title
    _title = Utils::createSprite("saveTitle");
    _title->setPosition(ccpAdd(center, ccp(0, 50)));
    this->addChild(_title);
    
    //gold
    _gold = Utils::createSprite("gold_1");
    _gold->setAnchorPoint(ccp(0.5, 0.5));
    _gold->setPosition(ccpAdd(center, ccp(-20, 10)));
    this->addChild(_gold);
    //goldIcon animate
    CCArray *goldAnimArray = Utils::createAnimArray("gold", 4);
    CCAnimation *goldAnimation = CCAnimation::createWithSpriteFrames(goldAnimArray, 0.1f);
    CCAnimate *goldAnimate = CCAnimate::create(goldAnimation);
    _gold->runAction(CCRepeatForever::create(goldAnimate));
    
    //label
    _nmb = CompnNumber::create();
    _nmb->setCount(_cost, COMPNNUMBERMODE_SCORE, 0);
    _nmb->setAnchorPoint(ccp(0, 0.5));
    _nmb->setPosition(ccpAdd(center, ccp(0, 10)));
    this->addChild(_nmb);
    
    //close
    _close = AniButton::create(KMenuSaveClose, Utils::createSprite("close"));
    _close->setAnchorPoint(ccp(0.5, 0.5));
    _close->setPosition(ccpAdd(center, ccp(_panel->getContentSize().width * 0.5 - 10, _panel->getContentSize().height * 0.5 - 10)));
    this->addChild(_close);
    
    //ok
    _ok = AniButton::create(KMenuSaveOk, Utils::createSprite("saveBtn"));
    _ok->setAnchorPoint(ccp(0.5, 0.5));
    _ok->setPosition(ccpAdd(center, ccp(0, -25)));
    this->addChild(_ok);
    
    //buttonArray
    _buttonArray = CCArray::create();
    _buttonArray->retain();
    _buttonArray->addObject(_close);
    _buttonArray->addObject(_ok);
    
    
    //touch events
    this->setTouchEnabled(true);
    
    //add
    _scene->addChild(this, _zorder, KLayerTagPopupSave);
    
    return true;
}

void PopupSave::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -_zorder, true);
}

bool PopupSave::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
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

void PopupSave::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
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

void PopupSave::clickItem(int bid)
{
    if (_delegate != NULL) {
        _delegate->onPopupEventMenuCommand(this, bid);
    }
    
    if (bid == KMenuSaveClose || bid == KMenuSaveOk) {
        this->dismiss();
    }
}

void PopupSave::dismiss()
{
    if (_delegate != NULL) {
        _delegate->onPopupEventDismiss(this);
    }
    
    this->removeFromParentAndCleanup(true);
}