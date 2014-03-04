//
//  Utils.h
//  testShao3
//
//  Created by shaozhen on 14-2-18.
//
//

#ifndef __testShao3__Utils__
#define __testShao3__Utils__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Utils : public CCObject{
public:
    //for this game only
    static CCSprite* createSprite(const char *name);
    
    //for common all
    static CCArray* createAnimArray(const string &name, int count);
    
    static CCArray* createAnimArray(const string &name, int begin, int end);
    
    static int hitTest(const CCPoint &pos, const vector<CCRect> &regions);
    
    static int buttonHitTest(const CCPoint &pos, CCArray *buttonArray);
    
    static bool rectHit(CCRect a, CCRect b);
    
    static vector<string> componentsSeparatedByString(const string &str, const string &delim);
};

#endif /* defined(__testShao3__Utils__) */
