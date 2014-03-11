//
//  GameUI.cpp
//  MyBird
//
//  Created by yuchen on 14-3-11.
//
//

#include "GameUI.h"
#include "GameGlobal.h"
#include "Utils.h"

GameUI::GameUI(CCScene *scene, const int zorder, PopupEventDelegate *delegate):_scene(scene), _zorder(zorder), _delegate(delegate), _lastPressedItem(-1)
{
    
}

GameUI::~GameUI()
{
    if (_buttonArray != NULL)
    {
        CC_SAFE_RELEASE_NULL(_buttonArray);
    }
}

GameUI* GameUI::create(CCScene *scene, const int zorder, PopupEventDelegate *delegate, CCPoint pos)
{
    GameUI *gameUI = new GameUI(scene, zorder, delegate);
    if (gameUI && gameUI->init(pos)) {
        gameUI->autorelease();
        return gameUI;
    }
    CC_SAFE_DELETE(gameUI);
    return NULL;
}

bool GameUI::init(CCPoint pos)
{
    if (!CCLayer::init()) {
        return false;
    }
    
    _shop = AniButton::create(KMenuShop, Utils::createSprite("goldToShop"));
    _shop->setAnchorPoint(ccp(0, 0.5));
    _shop->setPosition(pos);
    this->addChild(_shop);
    
    //buttonArray
    _buttonArray = CCArray::create();
    _buttonArray->retain();
    _buttonArray->addObject(_shop);
    
    //touch
    this->setTouchEnabled(true);
    
    //add
    _scene->addChild(this, _zorder, KLayerTagGameUI);
    
    return true;
}

void GameUI::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -_zorder, false);
}

bool GameUI::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
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

void GameUI::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
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

void GameUI::clickItem(const int bid)
{
    if (_delegate != NULL) {
        _delegate->onPopupEventMenuCommand(this, bid);
    }
}





