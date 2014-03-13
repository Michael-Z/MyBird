//
//  GameScene.h
//  testShao3
//
//  Created by shaozhen on 14-2-14.
//
//

#ifndef __testShao3__GameScene__
#define __testShao3__GameScene__


#include "cocos2d.h"
#include "Pipe.h"
#include "AniButton.h"
#include "CompnNumber.h"
#include "PopupEventDelegate.h"
#include "Bird.h"
#include "GameUI.h"
#include "PopupSave.h"
USING_NS_CC;
using namespace std;

class GameScene : public CCLayer, public PopupEventDelegate {
public:
    GameScene();
    virtual ~GameScene();
    virtual bool init();
    virtual void onExit();
    
    static CCScene* scene();
    
    CREATE_FUNC(GameScene);
    
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void playSfxWing();
    
    void birdJump();
    
    void birdFall();
    
    void birdDie(bool dieReasonFall);
    
    void showSave();
    
    void showResult();
    
    void setStatus(int state);
    
    void setPipes();
    
    void removePipes(CCNode *pipe);
    
    virtual void update(float delta);
    
    bool testBirdHitPipe(Pipe *pipe);
    
    bool testBirdHitGold(Pipe *pipe);
    
    void testPipePassed(Pipe *pipe);
    
    void playSfxPoint();
    
    void clickItem(int bid);
    
    virtual bool onPopupEventMenuCommand(CCLayer* component, const int menuId);
    
    virtual void onPopupEventDismiss(CCLayer* component);
    
    void menuCommand(int menuId);
    
    void setNoInvincible();
    
    static void purchaseComplete(bool status);
    
    void onNativePurchaseComplete(bool status);
    
protected:

private:
    static CCScene *_scene;
    
    CCLayerColor *color;
    CCSprite *bg;
    CCNode *actionNode;
    CCSprite *land;
    Bird *bird;
    CCArray *pipesArray;
    CompnNumber *scoreTip;
    CCSprite *stateTipReady;
    CCSprite *help;
    CCArray *buttonArray;
    CCSprite *goldIcon;
    CompnNumber *goldNmb;
    PopupSave *popupSave;
    //AniButton *goldShop;
    
    int GameState;
    int score;
    int lastPressedItem;
    bool newRecord;
    int dieCount;
    int pipeCount;
    int goldCount;
    bool birdInvincible;
    int resurCount;
    int readyAddGold;
};

#endif /* defined(__testShao3__GameScene__) */
