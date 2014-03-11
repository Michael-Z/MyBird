//
//  GameScene.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-14.
//
//

#include "GameScene.h"
#include "GameGlobal.h"
#include "Utils.h"
#include "PopupStart.h"
#include "PopupResult.h"
#include "PopupSave.h"
#include "GameData.h"
#include "AudioController.h"
#include "CCShake.h"
#include "PopupShop.h"
#include <cmath>
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../proj.android/jni/hellocpp/UtilsJNI.h"
#endif

#define Z_LAYERCOLOR    10
#define Z_BG            0
#define Z_ACTIONNODE    1
#define Z_PIPE          1
#define Z_LAND          2
#define Z_BIRD          3
#define Z_SCORE         4
#define Z_STATETIP      4
#define Z_HELP          4
#define Z_RESULT        5
#define Z_GOLD          6

CCScene* GameScene::_scene = NULL;

CCScene* GameScene::scene(){
    _scene = CCScene::create();
    GameScene* layer = GameScene::create();
    _scene->addChild(layer, KLayerOrderGame);
    PopupStart::create(_scene, KLayerOrderPopupStart, layer);
    return _scene;
}

GameScene::GameScene():GameState(1), score(0), lastPressedItem(-1), newRecord(false), dieCount(0), pipeCount(0), goldCount(GameData::instance()->getGDGold()), birdInvincible(false), resurCount(0)
{

}

GameScene::~GameScene(){
    if (pipesArray != NULL) {
        pipesArray->release();
        pipesArray = NULL;
    }
    
    if (buttonArray != NULL) {
        buttonArray->release();
        buttonArray = NULL;
    }
}

bool GameScene::init(){
    if ( !CCLayer::init() ) {
        return false;
    }
    //
    srand(time(0));
    //
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);
    CCPoint visOri = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //load resource
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game_source.plist");
    AudioController::sharedInstance()->preloadEffect("sfx_wing");
    
    color = CCLayerColor::create(ccc4(255, 255, 255, 255));
    this->addChild(color, Z_LAYERCOLOR);
    color->setOpacity(0);
    
    //bg
    bg = Utils::createSprite("bg_1");
    bg->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.5));
    this->addChild(bg, Z_BG);
    
    //actionNode for land and pipe
    actionNode = CCNode::create();
    this->addChild(actionNode, Z_ACTIONNODE);
    
    //land
    land = Utils::createSprite("land");
    land->setAnchorPoint(ccp(0.0, 0.0));
    land->setPosition(ccp(0.0, 0.0));
    actionNode->addChild(land, Z_LAND);
    //land action
    CCAction *landMove = CCRepeatForever::create (CCSequence::create(CCMoveTo::create(LandMoreWidth/SpeedLand, ccp(-LandMoreWidth, 0)), CCMoveTo::create(0, ccp(0, 0)), NULL));
    landMove->setTag(ActionTagLandMove);
    land->runAction(landMove);
    
    //bird
    bird = Bird::create();
    this->addChild(bird, Z_BIRD);
    bird->setPosition(ccpAdd(center, ccp(0, 20)));
    bird->setInit();
    //bird action
    CCMoveBy *birdMove = CCMoveBy::create(0.5, ccp(0, 10));
    CCRepeatForever *upDown = CCRepeatForever::create(CCSequence::create(birdMove, birdMove->reverse(), NULL));
    upDown->setTag(ActionTagBirdUpDown);
    bird->runAction(upDown);
    
    //score
    scoreTip = CompnNumber::create();
    scoreTip->setCount(0, COMPNNUMBERMODE_BIG, 0);
    scoreTip->setAnchorPoint(ccp(0.5, 0.5));
    scoreTip->setPosition(ccpAdd(center,ccp(0, 150)));
    this->addChild(scoreTip, Z_SCORE);
    scoreTip->setVisible(false);
    
    //stateTipReady
    stateTipReady = Utils::createSprite("text_getready");
    stateTipReady->setPosition(ccpAdd(center, ccp(0,60)));
    this->addChild(stateTipReady, Z_STATETIP);
    stateTipReady->setOpacity(0);
    
    //goldIcon
    goldIcon = Utils::createSprite("gold_1");
    goldIcon->setAnchorPoint(ccp(0, 1));
    goldIcon->setPosition(ccp(20, visOri.y + visSize.height - 20));
    this->addChild(goldIcon, Z_GOLD);
    //goldIcon animate
    CCArray *goldAnimArray = Utils::createAnimArray("gold", 4);
    CCAnimation *goldAnimation = CCAnimation::createWithSpriteFrames(goldAnimArray, 0.1f);
    CCAnimate *goldAnimate = CCAnimate::create(goldAnimation);
    goldIcon->runAction(CCRepeatForever::create(goldAnimate));
    
    //goldNmb
    goldNmb = CompnNumber::create();
    goldNmb->setCount(goldCount, COMPNNUMBERMODE_SCORE, 0);
    goldNmb->setAnchorPoint(ccp(0, 0.5));
    goldNmb->setPosition(ccp(goldIcon->getPositionX() + goldIcon->getContentSize().width + 2, goldIcon->getPositionY() - goldIcon->getContentSize().height * 0.5));
    this->addChild(goldNmb, Z_GOLD);
    
    //goldShop
//    goldShop = AniButton::create(KMenuShop, Utils::createSprite("goldToShop"));
//    goldShop->setAnchorPoint(ccp(0, 0.5));
//    goldShop->setPosition(goldNmb->getPosition() + ccp(goldNmb->getContentSize().width + 2, 0));
//    this->addChild(goldShop);
    //game ui
    GameUI::create(_scene, KLayerOrderGameUI, this, goldNmb->getPosition() + ccp(goldNmb->getContentSize().width + 2, 0));
    
    //help
    help = Utils::createSprite("tip_help");
    help->setPosition(ccpAdd(center, ccp(0, -20)));
    this->addChild(help, Z_HELP);
    help->setOpacity(0);
        
    //pipesArray
    pipesArray = CCArray::create();
    pipesArray->retain();
    
    //buttonsArray
    buttonArray = CCArray::create();
    buttonArray->retain();
    //buttonArray->addObject(goldShop);
    
    //touch events
    this->setTouchEnabled(true);
    
    //
    //setStatus(GameReady);
    
    return true;
}

void GameScene::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("game_source");
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("game_source.pvr.ccz");
    
    CCLayer::onExit();
}

void GameScene::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -KLayerOrderGame, true);
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCPoint pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    
    lastPressedItem = Utils::buttonHitTest(pos, buttonArray);
    if (lastPressedItem >= 0) {
        AniButton *btn = (AniButton*)buttonArray->objectAtIndex(lastPressedItem);
        btn->touch();
        return true;
    }
    
    
    if (GameState == GameReady) {
        setStatus(GameRun);
        
        birdJump();
    }
    else if (GameState == GameRun) {
        birdJump();
        
    }
    else if (GameState == GameEnd) {

    }
    
    
    return true;
}

void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCPoint pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    
    if (lastPressedItem >= 0 && lastPressedItem == Utils::buttonHitTest(pos, buttonArray)) {
        AniButton *btn = (AniButton*)buttonArray->objectAtIndex(lastPressedItem);
        btn->click();
        clickItem(btn->getAniButtonBid());
    }
}

void GameScene::birdJump()
{
    bird->unscheduleUpdate();
    CCRotateTo *rotateUp = CCRotateTo::create(0.4, -20);
    CCRotateTo *rotateDown = CCRotateTo::create(0.7, 90);
    CCSequence *seq = CCSequence::create(CCEaseSineOut::create(rotateUp), CCEaseSineIn::create(rotateDown), NULL);
    bird->runAction(seq);
        
    bird->setAniNodeAccMoveSpeed(ccp(0, -800));
    bird->setAniNodeMoveSpeed(ccp(0, 300));
    bird->scheduleUpdate();
    
    this->scheduleOnce(schedule_selector(GameScene::playSfxWing), 0.1);
    //AudioController::instance()->playSfx("sfx_wing");
}

void GameScene::playSfxWing()
{
    AudioController::sharedInstance()->playEffect("sfx_wing");
}

void GameScene::birdFall(){
    float v = 300;
    float distance = bird->getPositionY() - (land->getContentSize().height + 10);
    float durMove = distance/v;
    CCMoveBy *moveBy = CCMoveBy::create(durMove, ccp(0, -distance));
    CCEaseSineIn *ease = CCEaseSineIn::create(moveBy);
    CCSequence *seq  = CCSequence::create(ease, CCCallFunc::create(this, callfunc_selector(GameScene::showSave)), NULL);
    bird->runAction(seq);
}

void GameScene::birdDie(bool dieReasonFall){
    bird->stopAllActions();
    bird->die();
    dieCount++;
    
    setStatus(GameEnd);
  
    if (dieReasonFall) {
        showSave();
        AudioController::sharedInstance()->playEffect("sfx_hit");
    }
    else {
        birdFall();
        AudioController::sharedInstance()->playEffect("sfx_die");
    }
    
}

void GameScene::showSave()
{
//    resurCount = dieCount;
//    if (goldCount >= resurCount) {
//    //if (dieCount <= 3 && goldCount >= 10 * dieCount) {
//        PopupSave::create(_scene, KLayerOrderPopupSave, this, resurCount);
//    }
//    else {
//        showResult();
//    }
    resurCount = dieCount;
    popupSave = PopupSave::create(_scene, KLayerOrderPopupSave, this, resurCount);
}

void GameScene::showResult()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (dieCount >= 3) {
		JNI_showAdsScreen();
	}
#endif
    //show
    PopupResult *result = PopupResult::create(_scene, KLayerOrderPopupResult, this, score, GameData::instance()->getGDHighScore(), newRecord);
    result->show();
}

void GameScene::setStatus(int state){
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);
    
    GameState = state;
    if (state == GameReady) {
        
        //
        newRecord = false;
        pipeCount = 0;
        dieCount = 0;
        //remove pipes if have
        for (int i = pipesArray->count()-1; i >= 0; i--) {
            Pipe *pi = (Pipe*)pipesArray->objectAtIndex(i);
            actionNode->removeChild(pi);
        }
        pipesArray->removeAllObjects();
        
        //score
        score = 0;
        scoreTip->setCount(score);
        scoreTip->setVisible(true);
        
        //show
        stateTipReady->setOpacity(255);
        help->setOpacity(255);
        
        //bg
        CCArray *bgAnimArray = Utils::createAnimArray("bg", 2);
        int bgRand = 0 + rand() % (1 - 0 + 1);
        bg->setDisplayFrame((CCSpriteFrame *)bgAnimArray->objectAtIndex(bgRand));
        
        //bird
        bird->stopAllActions();
        bird->die();
        CCMoveBy *birdMove = CCMoveBy::create(0.5, ccp(0, 10));
        CCRepeatForever *upDown = CCRepeatForever::create(CCSequence::create(birdMove, birdMove->reverse(), NULL));
        upDown->setTag(ActionTagBirdUpDown);
        bird->runAction(upDown);
        bird->setInit();
        bird->setPosition(ccpAdd(center, ccp(-60, 0)));
        bird->setRotation(0);

        //land
        land->stopAllActions();
        CCAction *landMove = CCRepeatForever::create (CCSequence::create(CCMoveTo::create(LandMoreWidth/SpeedLand, ccp(-LandMoreWidth, 0)), CCMoveTo::create(0, ccp(0, 0)), NULL));
        landMove->setTag(ActionTagLandMove);
        land->runAction(landMove);
    }
    else if (state == GameRun) {
        //resur
        if (birdInvincible) {
            this->scheduleOnce(schedule_selector(GameScene::setNoInvincible), 3);
            //land
            land->stopAllActions();
            CCAction *landMove = CCRepeatForever::create (CCSequence::create(CCMoveTo::create(LandMoreWidth/SpeedLand, ccp(-LandMoreWidth, 0)), CCMoveTo::create(0, ccp(0, 0)), NULL));
            landMove->setTag(ActionTagLandMove);
            land->runAction(landMove);
            
            //pipe
            for (int i = 0 ; i < pipesArray->count(); i++) {
                Pipe *pi = (Pipe*)pipesArray->objectAtIndex(i);
                pi->setAniNodeMoveSpeed(ccp(-SpeedPipe, 0));
                pi->scheduleUpdate();
            }
        }
        
        //bird cancel upDown
        bird->stopActionByTag(ActionTagBirdUpDown);
        
        //tip and help fade action
        float durFade = 0.1;
        CCFadeOut *fade1 = CCFadeOut::create(durFade);
        CCFadeOut *fade2 = (CCFadeOut*)fade1->copy();
        stateTipReady->runAction(fade1);
        help->runAction(fade2);
        
        this->unscheduleUpdate();
        this->scheduleUpdate();
        this->unschedule(schedule_selector(GameScene::setPipes));
        this->schedule(schedule_selector(GameScene::setPipes), (screenSize.width/2 + 30)/SpeedPipe, kCCRepeatForever, 1);
    }
    else if (state == GameEnd) {
        this->unscheduleUpdate();
        this->unschedule(schedule_selector(GameScene::setPipes));
        //pipe action
        for (int i = 0 ; i < pipesArray->count(); i++) {
            Pipe *pi = (Pipe*)pipesArray->objectAtIndex(i);
            //pi->stopActionByTag(ActionTagPipeMove);
            pi->setAniNodeMoveSpeed(ccp(0, 0));
            pi->unscheduleUpdate();
        }
        
        //land action
        land->stopAllActions();
        
        //layerColor
        color->runAction(CCSequence::create(CCFadeIn::create(0.1), CCFadeOut::create(0.1), NULL));
        
        //actionNode
        actionNode->runAction(CCShake::createWithStrength(0.5, 20, 5));
        
        //best score
        int highScore = GameData::instance()->getGDHighScore();
        if (score > highScore) {
            GameData::instance()->setGDHighScore(score);
            newRecord = true;
        }
        
        //gold
        GameData::instance()->setGDGold(goldCount);
    }
    
}

void GameScene::setPipes(){
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    //pipe
    Pipe *pipe1 = Pipe::create(++pipeCount);
    actionNode->addChild(pipe1, Z_PIPE);
    pipe1->setAnchorPoint(ccp(0.0, 0.0));
    pipe1->setPosition(ccp(screenSize.width, 0));
    pipesArray->addObject(pipe1);
    //action    
    pipe1->setAniNodeMoveSpeed(ccp(-SpeedPipe, 0));
    pipe1->scheduleUpdate();
}

void GameScene::removePipes(CCNode *pipe){
    pipesArray->removeObject(pipe);
    actionNode->removeChild(pipe);
}

void GameScene::update(float delta){
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    if (GameState == GameRun && pipesArray != NULL && pipesArray->count() > 0) {
        //update score and gold
        scoreTip->setCount(score);
        goldNmb->setCount(goldCount);
        
        //rotate to 90
        if (bird->getRotation() >= 90) {
            bird->setAniNodeAccRotateSpeed(0);
            bird->setAniNodeRotateSpeed(0);
        }
        
        //hit land
        if (bird->getPositionY() <= land->getContentSize().height + 20) {
            birdDie(true);
            return;
        }
        
        //hit pipe
        for (int i = pipesArray->count() - 1; i >= 0; i--) {
            Pipe *pi = (Pipe*)pipesArray->objectAtIndex(i);
            
            //pipe should remove
            if (pi->getPositionX() < -(PipeWidth + screenSize.width)) {
                removePipes(pi);
                continue;
            }
            
            //score
            testPipePassed(pi);
            
            //gold
            if (testBirdHitGold(pi)) {
                goldCount++;
                pi->eatGold();
            }
            
            //hit
            if (!birdInvincible && testBirdHitPipe(pi)) {
                birdDie(false);
            }
        }
        
        
    }
}

bool GameScene::testBirdHitGold(Pipe *pipe)
{
    if (pipe->hasGold()) {
        if (Utils::rectHit(pipe->getGoldHotRect(), bird->getAniNodeHotRect())) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool GameScene::testBirdHitPipe(Pipe *pipe)
{
    //
    if (fabsf(bird->getPositionX() - (pipe->getPositionX() + PipeWidth/2)) < (PipeWidth + bird->getContentSize().width - 20)/2 ) {
        if (fabsf(bird->getPositionY() - pipe->getCenterH()) > pipe->getPipePadding() - bird->getContentSize().height/2 + 5) {
            
            AudioController::sharedInstance()->playEffect("sfx_hit");
            return true;
        }
    }
    return false;
}

void GameScene::testPipePassed(Pipe *pipe)
{
    if (!pipe->getPassed() && pipe->getPositionX() + PipeWidth/2 <= bird->getPositionX())
    {
        pipe->setPassed(true);
        score++;
        this->scheduleOnce(schedule_selector(GameScene::playSfxPoint), 0.1);
        //AudioController::instance()->playSfx("sfx_point");
    }
}

void GameScene::playSfxPoint()
{
    AudioController::sharedInstance()->playEffect("sfx_point");
}

void GameScene::clickItem(int bid)
{
    this->menuCommand(bid);
}

bool GameScene::onPopupEventMenuCommand(cocos2d::CCLayer *component, const int menuId)
{
    menuCommand(menuId);
}

void GameScene::onPopupEventDismiss(CCLayer *component)
{
    
}

void GameScene::menuCommand(int menuId)
{
    if (menuId == KMenuRestart) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    	JNI_closeAdsScreen();
#endif
        setStatus(GameReady);
        AudioController::sharedInstance()->playEffect("sfx_swooshing");
    }
    else if (menuId == KMenuRecord) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    	JNI_sendToWX();
#endif
    }
    else if (menuId == KMenuSaveClose) {
        showResult();
    }
    else if (menuId == KMenuSaveOk) {
        //gold not enough
        if (goldCount < resurCount) {
            PopupShop *pShop = PopupShop::create(_scene, KLayerOrderPopupShop, this);
            return;
        }
        
        
        //gold enough
        popupSave->dismiss();
        
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);
        
        //show
        stateTipReady->setOpacity(255);
        help->setOpacity(255);
        
        //bird
        bird->stopAllActions();
        
//        CCMoveBy *birdMove = CCMoveBy::create(0.5, ccp(0, 10));
//        CCRepeatForever *upDown = CCRepeatForever::create(CCSequence::create(birdMove, birdMove->reverse(), NULL));
//        upDown->setTag(ActionTagBirdUpDown);
//        bird->runAction(upDown);
        
        bird->setInit(bird->getBirdIdx());
        bird->setPosition(ccpAdd(center, ccp(-60, 0)));
        bird->setRotation(0);
        
        CCRepeatForever *blink = CCRepeatForever::create(CCBlink::create(1, 5));
        blink->setTag(ActionTagBirdBlink);
        bird->runAction(blink);
        
        birdInvincible = true;
        
        //gold
        goldCount -= resurCount;
        GameData::instance()->setGDGold(goldCount);
        goldNmb->setCount(goldCount);
        
        //game state
        GameState = GameReady;
    }
    else if (menuId == KMenuShop)
    {
        PopupShop *pShop = PopupShop::create(_scene, KLayerOrderPopupShop, this);
    }
    else if (menuId == KMenuShopClose)
    {
        
    }
    else if (menuId == KMenuShopOne)
    {
        
    }
    else if (menuId == KMenuShopTwo)
    {
        
    }
    else if (menuId == KMenuShopThree)
    {
        
    }
}

void GameScene::setNoInvincible()
{
    birdInvincible = false;
    bird->stopActionByTag(ActionTagBirdBlink);
    bird->setVisible(true);
}



