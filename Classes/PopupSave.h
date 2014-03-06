//
//  PopupSave.h
//  MyBird
//
//  Created by yuchen on 14-3-4.
//
//

#ifndef __MyBird__PopupSave__
#define __MyBird__PopupSave__

#include "cocos2d.h"
#include "PopupEventDelegate.h"
#include "AniButton.h"
#include "CompnNumber.h"

USING_NS_CC;

class PopupSave : public CCLayer
{
public:
    PopupSave(CCScene *scene, const int zorder, PopupEventDelegate *delegate, int cost);
    ~PopupSave();
    static PopupSave* create(CCScene *scene, const int zorder, PopupEventDelegate *delegate, int cost);
    virtual bool init();
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void clickItem(int bid);
    void dismiss();
    
private:
    CCSprite *_title;
    CCSprite *_panel;
    AniButton *_close;
    AniButton *_ok;
    CCSprite *_gold;
    CompnNumber *_nmb;
    
    CCScene *_scene;
    int _zorder;
    PopupEventDelegate *_delegate;
    int _cost;
    
    CCArray *_buttonArray;
    int _lastPressedItem;
};

#endif /* defined(__MyBird__PopupSave__) */
