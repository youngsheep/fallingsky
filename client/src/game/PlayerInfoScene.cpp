//
//  PlayerInfoScene.cpp
//  HelloCpp
//
//  Created by yy on 14-5-12.
//
//

#include "PlayerInfoScene.h"
#include "GameScene.h"

//extern void registerWeiboLogin(cocos2d::CCObject* obj);

USING_NS_CC;

CCScene* PlayerInfo::scene()
{
    CCScene *scene = CCScene::create();
    PlayerInfo *layer = PlayerInfo::create();
    scene->addChild(layer,1);
    return scene;
}

bool PlayerInfo::init()
{
    CCMenuItemFont *item = CCMenuItemFont::create(" LOGIN ", this, menu_selector(PlayerInfo::loginCallback) );
    item->setFontSizeObj(20);
    item->setFontName("Marker Felt");
    
    CCMenu* menu = CCMenu::create( item , NULL);
    addChild(menu);
    
    return true;
}

void PlayerInfo::loginCallback(CCObject* pSender)
{
    //registerWeiboLogin(this);
    CCTransitionFadeBL* transition = CCTransitionFadeBL::create(1, FLGame::scene());
    if (transition)
    {
        CCDirector::sharedDirector()->replaceScene(transition);
    }
}