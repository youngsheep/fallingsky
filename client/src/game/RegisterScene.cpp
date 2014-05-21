//
//  RegisterScene.cpp
//  HelloCpp
//
//  Created by yy on 14-5-16.
//
//

#include "RegisterScene.h"
//#include "GameScene.h"
#include "net/GameProtoHandler.h"
#include "common/FLTextInput.h"

extern void registerWeiboLogin();

USING_NS_CC;

CCScene* RegisterLayer::scene()
{
    CCScene *scene = CCScene::create();
    RegisterLayer *layer = RegisterLayer::create();
    scene->addChild(layer,1);
    return scene;
}

bool RegisterLayer::init()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //FLTextInput* TextField = FLTextInput::textFieldWithPlaceHolder("Input Text", "Marker Felt", 30);
    //TextField->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 200));
    //this->addChild(TextField);
    
    CCMenuItemFont *item = CCMenuItemFont::create(" Register ", this, menu_selector(RegisterLayer::registerCallback) );
    item->setFontSizeObj(20);
    item->setFontName("Marker Felt");
    
    CCMenu* menu = CCMenu::create( item , NULL);
    addChild(menu);
    
    return true;
}

void RegisterLayer::registerCallback(CCObject* pSender)
{

}