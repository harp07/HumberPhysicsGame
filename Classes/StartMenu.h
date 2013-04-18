#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#define SCALE 0.75f
#define X_OFFSET 0
#define Y_OFFSET 35

class StartMenu : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuStartCall(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(StartMenu);
};

