//
//  PopupShop.cpp
//  MyBird
//
//  Created by yuchen on 14-3-10.
//
//

#include "PopupShop.h"
#include "Utils.h"
#include "GameGlobal.h"

PopupShop::PopupShop(CCScene *scene, const int zorder, PopupEventDelegate *delegate):_scene(scene), _zorder(zorder), _delegate(delegate), _lastPressedItem(-1)
{
    
}

PopupShop::~PopupShop()
{
    if (_buttonArray != NULL)
    {
        CC_SAFE_RELEASE_NULL(_buttonArray);
    }
}

PopupShop* PopupShop::create(CCScene *scene, const int zorder, PopupEventDelegate *delegate)
{
    PopupShop *pShop = new PopupShop(scene, zorder, delegate);
    if (pShop && pShop->init()) {
        pShop->autorelease();
        return pShop;
    }
    CC_SAFE_DELETE(pShop);
    return NULL;
}

bool PopupShop::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    //vars
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);
    
    //panel
    _panel = Utils::createSprite("goldButPanel");
    _panel->setPosition(center);
    this->addChild(_panel);
    
    //close
    _close = AniButton::create(KMenuShopClose, Utils::createSprite("close"));
    _close->setPosition(center + ccp(96, 79));
    this->addChild(_close);
    
    //label1
    CCLabelTTF *_label1 = CCLabelTTF::create(CCString::createWithFormat("%d", KShopOne)->getCString(), "Consolas", 24);
    _label1->setAnchorPoint(ccp(1, 0.5));
    _label1->setPosition(center + ccp(-10, 57));
    this->addChild(_label1);
    
    //label2
    CCLabelTTF *_label2 = CCLabelTTF::create(CCString::createWithFormat("%d", KShopTwo)->getCString(), "Consolas", 24);
    _label2->setAnchorPoint(ccp(1, 0.5));
    _label2->setPosition(center + ccp(-10, 0));
    this->addChild(_label2);
    
    //label3
    CCLabelTTF *_label3 = CCLabelTTF::create(CCString::createWithFormat("%d", KShopThree)->getCString(), "Consolas", 24);
    _label3->setAnchorPoint(ccp(1, 0.5));
    _label3->setPosition(center + ccp(-10, -57));
    this->addChild(_label3);
    
    //btn1
    _btn1 = AniButton::create(KMenuShopOne, Utils::createSprite("goldBuyBtn"), NULL, 1, CCLabelTTF::create(CCString::createWithFormat("￥ %d", KShopCostOne)->getCString(), "Consolas", 18));
    _btn1->setAnchorPoint(ccp(0, 0.5));
    _btn1->setPosition(_label1->getPosition() + ccp(25, 0));
    this->addChild(_btn1);
    
    //btn2
    _btn2 = AniButton::create(KMenuShopTwo, Utils::createSprite("goldBuyBtn"), NULL, 1, CCLabelTTF::create(CCString::createWithFormat("￥ %d", KShopCostTwo)->getCString(), "Consolas", 18));
    _btn2->setAnchorPoint(ccp(0, 0.5));
    _btn2->setPosition(_label2->getPosition() + ccp(25, 0));
    this->addChild(_btn2);
    
    //btn3
    _btn3 = AniButton::create(KMenuShopThree, Utils::createSprite("goldBuyBtn"), NULL, 1, CCLabelTTF::create(CCString::createWithFormat("￥ %d", KShopCostThree)->getCString(), "Consolas", 18));
    _btn3->setAnchorPoint(ccp(0, 0.5));
    _btn3->setPosition(_label3->getPosition() + ccp(25, 0));
    this->addChild(_btn3);
    
    //buttonArray
    _buttonArray = CCArray::create();
    _buttonArray->retain();
    _buttonArray->addObject(_close);
    _buttonArray->addObject(_btn1);
    _buttonArray->addObject(_btn2);
    _buttonArray->addObject(_btn3);
    
    //touch
    this->setTouchEnabled(true);
    
    //add
    _scene->addChild(this, _zorder, KLayerTagPopupShop);
    
    
    return true;
}

void PopupShop::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -_zorder, true);
}

bool PopupShop::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
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

void PopupShop::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
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

void PopupShop::clickItem(const int bid)
{
    if (_delegate != NULL) {
        _delegate->onPopupEventMenuCommand(this, bid);
    }
    
    if (bid == KMenuShopClose) {
        this->dismiss();
    }

}

void PopupShop::dismiss()
{
    if (_delegate != NULL) {
        _delegate->onPopupEventDismiss(this);
    }
    
    this->removeFromParentAndCleanup(true);
}






