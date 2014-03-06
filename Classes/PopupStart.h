//
//  PopupStart.h
//  MyBird
//
//  Created by yuchen on 14-3-4.
//
//

#ifndef __MyBird__PopupStart__
#define __MyBird__PopupStart__

#include "cocos2d.h"
#include "AniButton.h"
#include "PopupEventDelegate.h"

USING_NS_CC;

class PopupStart : public CCLayer
{
public:
    PopupStart(CCScene *scene, const int zorder, PopupEventDelegate *delegate);
    ~PopupStart();
    static PopupStart* create(CCScene *scene, const int zorder, PopupEventDelegate *delegate);
    virtual bool init();
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void clickItem(int bid);
    void dismiss();
    
private:
    CCSprite *title;
    AniButton *play;
    AniButton *share;
    
    CCScene *_scene;
    int _zorder;
    PopupEventDelegate *_delegate;
    
    CCArray *_buttonArray;
    int _lastPressedItem;
    
};

#endif /* defined(__MyBird__PopupStart__) */
