//
//  GameUI.h
//  MyBird
//
//  Created by yuchen on 14-3-11.
//
//

#ifndef __MyBird__GameUI__
#define __MyBird__GameUI__

#include <iostream>
#include "cocos2d.h"
#include "AniButton.h"
#include "PopupEventDelegate.h"
USING_NS_CC;

class GameUI : public CCLayer
{
public:
    GameUI(CCScene *scene, const int zorder, PopupEventDelegate *delegate);
    ~GameUI();
    static GameUI* create(CCScene *scene, const int zorder, PopupEventDelegate *delegate, CCPoint pos);
    virtual bool init(CCPoint pos);
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void clickItem(const int bid);
    
private:
    AniButton *_shop;
    
    CCScene *_scene;
    int _zorder;
    PopupEventDelegate *_delegate;
    
    CCArray *_buttonArray;
    int _lastPressedItem;
};

#endif /* defined(__MyBird__GameUI__) */
