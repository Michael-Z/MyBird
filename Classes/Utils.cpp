//
//  Utils.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-18.
//
//

#include "Utils.h"
#include "AniButton.h"

//for this game only
CCSprite* Utils::createSprite(const char *name){
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(name);
    return sprite;
};


//for common all
CCArray* Utils::createAnimArray(const string &name, int count){
    return Utils::createAnimArray(name, 1, count);
}

CCArray* Utils::createAnimArray(const string &name, int begin, int end)
{
    CCArray *animArray = CCArray::createWithCapacity(end - begin + 1);

    int idx = begin;
    while (idx <= end) {
        //        stringstream stream;
        //        stream << name << "_" << idx;
        //        string idxName = stream.str();
        
        char buffer[50];
        sprintf(buffer, "%s_%d", name.c_str(), idx);
        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
        animArray->addObject(spriteFrame);
        idx++;
    }
    return animArray;
}

int Utils::hitTest(const cocos2d::CCPoint &pos, const vector<cocos2d::CCRect> &regions){
    int hit = -1;
    if (regions.size() != 0) {
        for (int i = regions.size(); i >= 0; i--) {
            CCRect rc = regions[i];
            if (rc.containsPoint(pos)) {
                hit = i;
                break;
            }
        }
    }
    return hit;
}

int Utils::buttonHitTest(const cocos2d::CCPoint &pos, CCArray *buttonArray){
    int hit = -1;

    if (buttonArray->count()>0) {
        for (int i = 0; i < buttonArray->count(); i++) {
            AniButton *btn = (AniButton*)buttonArray->objectAtIndex(i);
            CCRect rc = btn->getAniNodeHotRect();
            if (rc.containsPoint(pos)) {
                hit = i;
                break;
            }
        }
    }
    return hit;
}

bool Utils::rectHit(cocos2d::CCRect a, cocos2d::CCRect b)
{
    CCPoint centerA = ccp(a.origin.x + a.size.width * 0.5, a.origin.y + a.size.height * 0.5);
    CCPoint centerB = ccp(b.origin.x + b.size.width * 0.5, b.origin.y + b.size.height * 0.5);
    if (fabsf(centerA.x - centerB.x) <= fabsf(a.size.width + b.size.height) * 0.5 && fabsf(centerA.y - centerB.y) <= fabsf(a.size.height + b.size.height) * 0.5) {
        return true;
    }
    else {
        return false;
    }
}

vector<string> Utils::componentsSeparatedByString(const string &str, const string &delim){
    vector<string> tokens;
    string::size_type lastPos = 0;
    string::size_type pos = str.find(delim, lastPos);
    while (string::npos != pos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = pos + delim.size();
        pos = str.find(delim, lastPos);
    }
    tokens.push_back(str.substr(lastPos, str.size() - lastPos));
    return tokens;
}

