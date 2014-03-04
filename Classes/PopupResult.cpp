//
//  PopupResult.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-19.
//
//

#include "PopupResult.h"
#include "Utils.h"
#include "GameGlobal.h"
#include "AudioController.h"

PopupResult::PopupResult(CCScene *scene, const int zorder, PopupEventDelegate *delegate, int score, int bestScore, bool newRecord):_scene(scene), _zorder(zorder), _delegate(delegate), _score(score), _bestScore(bestScore), _isNewRecord(newRecord), _lastPressedItem(-1){
    
}

PopupResult::~PopupResult(){
    if (_buttonArray != NULL) {
        _buttonArray->release();
        _buttonArray = NULL;
    }
}

PopupResult* PopupResult::create(CCScene *scene, const int zorder, PopupEventDelegate *delegate, int score, int bestScore, bool newRecord){
    PopupResult* pop = new PopupResult(scene, zorder, delegate, score, bestScore, newRecord);
    if (pop && pop->init()) {
        pop->autorelease();
        return pop;
    }
    else{
        delete pop;
        pop = NULL;
        return NULL;
    }
}

bool PopupResult::init(){
    if (!CCLayer::init()) {
        return false;
    }
    //base
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);
    
    //over
    _over = Utils::createSprite("text_gameover");
    _over->setPosition(ccpAdd(center, ccp(0, 100)));
    this->addChild(_over);
    _over->setVisible(false);
    
    
    //panel
    _panel = CCNode::create();
    _panel->setPosition(ccpAdd(center, ccp(0, 0)));
    this->addChild(_panel);
    //bg
    _resultBg = Utils::createSprite("resultPanle");
    _panel->addChild(_resultBg);
    _resultBg->setVisible(false);
    
    //medal
    _medal = NULL;
    _flash = NULL;
    //_score = 31;
    if (_score >= 10) {
        int a = _score/10;
        int b = a%9 - 1;
        char *buffer[] = {"medal_1", "medal_2", "medal_3", "medal_4", "medal_5", "medal_6", "medal_7", "medal_8"};
        _medal = Utils::createSprite(buffer[b]);
        _medal->setPosition(ccpAdd(_resultBg->getPosition(), ccp(-65, -5)));
        _panel->addChild(_medal);
        _medal->setVisible(false);
        
        _flash = CCSprite::createWithSpriteFrameName("flash_1");
        _panel->addChild(_flash);
        randFlashPosition();
        
        CCArray *goldAnimArray = Utils::createAnimArray("flash", 3);
        CCAnimation *goldAnimation = CCAnimation::createWithSpriteFrames(goldAnimArray, 0.1f);
        CCAnimate *goldAnimate = CCAnimate::create(goldAnimation);
        _flash->runAction(CCRepeatForever::create(CCSequence::create(goldAnimate, CCCallFunc::create(this, callfunc_selector(PopupResult::randFlashPosition)))));
        _flash->setVisible(false);
        
    }
    
    //score
    _cnScore = CompnNumber::create();
    _cnScore->setCount(0, COMPNNUMBERMODE_SCORE, 2);
    _cnScore->setAnchorPoint(ccp(1, 0));
    _cnScore->setPosition(ccpAdd(_resultBg->getPosition(), ccp(90, 5)));
    _panel->addChild(_cnScore);
    _cnScore->setVisible(false);
    
    //bestScore
    _cnBestScore = CompnNumber::create();
    _cnBestScore->setCount(_bestScore, COMPNNUMBERMODE_SCORE, 2);
    _cnBestScore->setAnchorPoint(ccp(1, 0));
    _cnBestScore->setPosition(ccpAdd(_cnScore->getPosition(), ccp(0, -40)));
    _panel->addChild(_cnBestScore);
    _cnBestScore->setVisible(false);
    
    //new
    _newRecord = NULL;
    if (_isNewRecord) {
        _newRecord = Utils::createSprite("new");
        _newRecord->setPosition(ccpAdd(_cnBestScore->getPosition(), ccp(-50,15)));
        _panel->addChild(_newRecord);
        _newRecord->setVisible(false);
    }
    
    //restart
    reStart = AniButton::create(KMenuRestart, Utils::createSprite("btn_play"));
    reStart->setAnchorPoint(ccp(0.5, 0.5));
    reStart->setPosition(ccpAdd(center, ccp(-60, -100)));
    this->addChild(reStart);
    reStart->setVisible(false);
    
    //record
    record = AniButton::create(KMenuRecord, Utils::createSprite("btn_wx"));
    record->setAnchorPoint(ccp(0.5, 0.5));
    record->setPosition(ccpAdd(center, ccp(60, -100)));
    this->addChild(record);
    record->setVisible(false);
    
    //buttonArray
    _buttonArray = CCArray::create();
    _buttonArray->retain();
    _buttonArray->addObject(reStart);
    _buttonArray->addObject(record);
    
    //add
    _scene->addChild(this, _zorder, KLayerTagPopupResult);
    this->setVisible(false);
    
    //touch events
    this->setTouchEnabled(true);
    
    return  true;
}

void PopupResult::randFlashPosition()
{
    if (_medal != NULL && _flash != NULL) {
        int x = int(-_medal->getContentSize().width * 0.5) + rand() % ((int)(_medal->getContentSize().width) + 1);
        int y = int(-_medal->getContentSize().height * 0.5) + rand() % ((int)(_medal->getContentSize().height) + 1);
        
        _flash->setPosition(ccpAdd(_medal->getPosition(), ccp(x, y)));
    }
}

void PopupResult::show()
{
    _enabled = false;
    this->setVisible(true);
    _entryEffectStep = 1;
    
    this->scheduleOnce(schedule_selector(PopupResult::schedualEntryEffect), 0.2);
}

void PopupResult::schedualEntryEffect()
{
    //base
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);
    
    if (_entryEffectStep == 1) {
        _entryEffectStep = 2;
        _over->setVisible(true);
        
        CCMoveBy *move = CCMoveBy::create(0.1, ccp(0, 10));
        CCSequence *seq = CCSequence::create(move, move->reverse(), CCDelayTime::create(0.5), CCCallFunc::create(this, callfunc_selector(PopupResult::schedualEntryEffect)), NULL);
        _over->runAction(seq);
        AudioController::sharedInstance()->playEffect("sfx_swooshing");
    }
    else if (_entryEffectStep == 2) {
        _entryEffectStep = 3;
                
        CCPoint panelPos = _panel->getPosition();
        _panel->setPosition(ccp(screenSize.width * 0.5, -_resultBg->getContentSize().height));
        _resultBg->setVisible(true);
        _cnBestScore->setVisible(true);
        if (_newRecord != NULL) {
            _newRecord->setVisible(true);
        }
        
        CCMoveTo *move = CCMoveTo::create(0.5, panelPos);
        CCSequence *seq = CCSequence::create(move, CCCallFunc::create(this, callfunc_selector(PopupResult::schedualEntryEffect)), NULL);
        _panel->runAction(seq);
        AudioController::sharedInstance()->playEffect("sfx_swooshing");
    }
    else if (_entryEffectStep == 3) {
        _entryEffectStep = 4;
        _cnScore->setVisible(true);
        
        float single = 0.05;
        if (_score > 0) {
            _scoreAnimationStep = 1;
            this->schedule(schedule_selector(PopupResult::showScoreAnimation), single, _score - 1, 0);
        }
        this->unschedule(schedule_selector(PopupResult::schedualEntryEffect));
        this->schedule(schedule_selector(PopupResult::schedualEntryEffect), single * _score);
        
        
    }
    else if (_entryEffectStep == 4) {
        _entryEffectStep = 5;
        if (_medal != NULL) {
             _medal->setVisible(true);
            _flash->setVisible(true);
        }
       
        
        this->unschedule(schedule_selector(PopupResult::schedualEntryEffect));
        this->schedule(schedule_selector(PopupResult::schedualEntryEffect), 0.5);
    }
    else if (_entryEffectStep == 5) {
        _entryEffectStep = 6;
        reStart->setVisible(true);
        record->setVisible(true);
        _enabled = true;
        
        this->unschedule(schedule_selector(PopupResult::schedualEntryEffect));
    }
    
}

void PopupResult::showScoreAnimation()
{
    _cnScore->setCount(_scoreAnimationStep);
    _scoreAnimationStep++;
}

void PopupResult::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -KLayerOrderPopupResult, true);
}

bool PopupResult::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!_enabled)
    {
        return false;
    }
    
    CCPoint pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    
    _lastPressedItem = Utils::buttonHitTest(pos, _buttonArray);
    if (_lastPressedItem >= 0) {
        AniButton *btn = (AniButton*)_buttonArray->objectAtIndex(_lastPressedItem);
        btn->touch();
    }
    return true;
}

void PopupResult::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!_enabled) {
        return;
    }
    
    CCPoint pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    
    if (_lastPressedItem >= 0 && _lastPressedItem == Utils::buttonHitTest(pos, _buttonArray)) {
        AniButton *btn = (AniButton*)_buttonArray->objectAtIndex(_lastPressedItem);
        btn->click();
        
        int bid = btn->getAniButtonBid();
        this->clickItem(bid);
        
    }
}

void PopupResult::clickItem(int bid)
{
    if (_delegate != NULL) {
        _delegate->onPopupEventMenuCommand(this, bid);
    }
    
    if (bid == KMenuRestart) {
        this->dismiss();
    }
}

void PopupResult::dismiss()
{
    if (_delegate != NULL) {
        _delegate->onPopupEventDismiss(this);
    }
    
    this->removeFromParentAndCleanup(true);
}

