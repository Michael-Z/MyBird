//
//  PopupShop.h
//  MyBird
//
//  Created by yuchen on 14-3-10.
//
//

#ifndef __MyBird__PopupShop__
#define __MyBird__PopupShop__

#include "AniButton.h"
#include "cocos2d.h"
#include "PopupEventDelegate.h"
USING_NS_CC;

class PopupShop : public CCLayer
{
public:
    PopupShop(CCScene *scene, const int zorder, PopupEventDelegate *delegate);
    ~PopupShop();
    static PopupShop* create(CCScene *scene, const int zorder, PopupEventDelegate *delegate);
    virtual bool init();
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void clickItem(const int bid);
    void dismiss();
    
private:
    CCScene *_scene;
    int _zorder;
    PopupEventDelegate *_delegate;
    
    CCSprite *_panel;
    AniButton *_btn1;
    AniButton *_btn2;
    AniButton *_btn3;
    AniButton *_close;
    
    CCArray *_buttonArray;
    int _lastPressedItem;

    
};

#endif /* defined(__MyBird__PopupShop__) */
