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
    
    CCLabelTTF* label = CCLabelTTF::create("input nickname:","Marker Felt", 30);
    label->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 100));
    addChild(label);

    FLTextInput* TextField = FLTextInput::textFieldWithPlaceHolder("Input Text", "Marker Felt", 30);
    TextField->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 100));
    this->addChild(TextField);
    
    CCMenuItemFont *item = CCMenuItemFont::create("Create", this, menu_selector(RegisterLayer::registerCallback) );
    CCMenu* menu = CCMenu::create( item , NULL);
    menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 200));
    addChild(menu);
    
    return true;
}

void RegisterLayer::onEnter()
{
    GameProtoHandler::GetInstance().RegisterProtoHandler(this);
    CCLayer::onEnter();
}

void RegisterLayer::onExit()
{
    GameProtoHandler::GetInstance().UnRegisterProtoHandler(this);
    CCLayer::onExit();
}

void RegisterLayer::registerCallback(CCObject* pSender)
{
    GameProtoHandler::GetInstance().RoleCreateReq("");
}

void RegisterLayer::Response(std::string route,int result)
{
    
}
