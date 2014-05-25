//
//  PlayerInfoScene.cpp
//  HelloCpp
//
//  Created by yy on 14-5-12.
//
//

#include "PlayerInfoScene.h"
#include "GameScene.h"
#include "net/GameProtoHandler.h"
#include "RegisterScene.h"

extern void registerWeiboLogin();

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

CCScene* PlayerInfo::scene()
{
    CCScene *scene = CCScene::create();
    PlayerInfo *layer = PlayerInfo::create();
    scene->addChild(layer,1);
    return scene;
}

bool PlayerInfo::init()
{
    TouchGroup::init();
    Layout* layout = static_cast<Layout*>(GUIReader::shareReader()->
                                          widgetFromJsonFile
                                          ("ui/fallingsky-ui-login.ExportJson"));
    Button* btn = static_cast<Button*>(layout->getChildByName("login"));
    if(btn){
        btn->addTouchEventListener(this,toucheventselector(PlayerInfo::loginCallback));
        btn->setScale9Enabled(true);
    }

    addWidget(layout);

    
    GameProtoHandler::GetInstance().ConnectGameSvr("198.199.100.95", 3010);
    
    return true;
}

void PlayerInfo::onEnter()
{
    GameProtoHandler::GetInstance().RegisterProtoHandler(this);
    TouchGroup::onEnter();
}

void PlayerInfo::onExit()
{
    GameProtoHandler::GetInstance().UnRegisterProtoHandler(this);
    TouchGroup::onExit();
}

void PlayerInfo::loginCallback(CCObject* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED) {
        registerWeiboLogin();
        //Response("connector.entryHandler.entry",100);
    }
}

void PlayerInfo::Response(std::string route,int result)
{
    if (route.compare("connector.entryHandler.entry") == 0) {
        if (result == 100) {
            CCTransitionFadeBL* transition = CCTransitionFadeBL::create(2, RegisterLayer::scene());
            if (transition)
            {
                CCDirector::sharedDirector()->replaceScene(RegisterLayer::scene());
            }
        }
        else if(result == 0)
        {
            CCTransitionFadeBL* transition = CCTransitionFadeBL::create(1, FLGame::scene());
            if (transition)
            {
                CCDirector::sharedDirector()->replaceScene(transition);
            }
        }
        else if (result < 0)
        {
            
        }
    }
}