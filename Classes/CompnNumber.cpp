//
//  CompnNumber.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-19.
//
//

#include "CompnNumber.h"
#include "Utils.h"

char *CompnNumber::fontArray[4][10]={
    {
        "number_big_0",
        "number_big_1",
        "number_big_2",
        "number_big_3",
        "number_big_4",
        "number_big_5",
        "number_big_6",
        "number_big_7",
        "number_big_8",
        "number_big_9"
        
    },
    {
        "number_normal_0",
        "number_normal_1",
        "number_normal_2",
        "number_normal_3",
        "number_normal_4",
        "number_normal_5",
        "number_normal_6",
        "number_normal_7",
        "number_normal_8",
        "number_normal_9"
    },
    {
        "number_small_0",
        "number_small_1",
        "number_small_2",
        "number_small_3",
        "number_small_4",
        "number_small_5",
        "number_small_6",
        "number_small_7",
        "number_small_8",
        "number_small_9"
    },
    {
        "number_gold_0",
        "number_gold_1",
        "number_gold_2",
        "number_gold_3",
        "number_gold_4",
        "number_gold_5",
        "number_gold_6",
        "number_gold_7",
        "number_gold_8",
        "number_gold_9"
    }
};


CompnNumber::CompnNumber():_padding(0),_mode(COMPNNUMBERMODE_BIG),_count(-1){
    

}

CompnNumber::~CompnNumber(){
    if (countsArray != NULL) {
        countsArray->release();
        countsArray = NULL;
    }
}

bool CompnNumber::init(){
    if (!CCNode::init()) {
        return false;
    }
    
    countsArray = CCArray::create();
    countsArray->retain();
    
    return true;
}

void CompnNumber::setCount(int count, int mode, int padding){
    _mode = mode;
    
    if (_count != count) {
        _count = count;
        _padding = padding;
        
        //clear
        for (int i=0; i < countsArray->count(); i++)
        {
            this->removeChild((CCSprite*)countsArray->objectAtIndex(i));
        }
        countsArray->removeAllObjects();
        totalWidth = 0;
        
        //add
        char buffer[5];
        sprintf(buffer, "%d", _count);
        for (int i=0; i < strlen(buffer); i++)
        {
            //
            //string str = "font_" ;
            //str = str + buffer[i];
            //或者
            //stringstream ss;
            //ss << "font_" << buffer[i];
            //string str = ss.str();
            string str = fontArray[_mode][buffer[i] - '0'];
            
            CCSprite *sprite = Utils::createSprite(str.c_str());
            countsArray->addObject(sprite);
            
            totalWidth += sprite->getContentSize().width + _padding;
        }
        
        totalHeight = ((CCSprite*)countsArray->objectAtIndex(0))->getContentSize().height;
        totalWidth -= _padding;
        this->setContentSize(CCSizeMake(totalWidth, totalHeight));
        
        //setPosition
        for (int i=0; i < countsArray->count(); i++)
        {
            CCSprite *child = (CCSprite*)countsArray->objectAtIndex(i);
            this->addChild(child);
            child->setAnchorPoint(ccp(0, 0));
            if (i == 0)
            {
                child->setPosition(ccp(0, 0));
            }
            else
            {
                CCSprite *last = (CCSprite*)countsArray->objectAtIndex(i-1);
                child->setPosition(ccpAdd(last->getPosition(), ccp(last->getContentSize().width + _padding, 0)));
            }
            
        }

    }
}

void CompnNumber::setCount(int count){
    setCount(count, _mode, _padding);
}



