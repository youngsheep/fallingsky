//
//  RegisterScene.cpp
//  HelloCpp
//
//  Created by yy on 14-5-16.
//
//

#include "RegisterScene.h"
#include "GameScene.h"
#include "net/GameProtoHandler.h"
#include "common/FLTextInput.h"

extern void registerWeiboLogin();

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

CCScene* RegisterLayer::scene()
{
    CCScene *scene = CCScene::create();
    RegisterLayer *layer = RegisterLayer::create();
    scene->addChild(layer,1);
    return scene;
}

bool RegisterLayer::init()
{
    TouchGroup::init();
    Layout* layout = static_cast<Layout*>(GUIReader::shareReader()->
        widgetFromJsonFile
        ("ui/fallingsky-ui_register.ExportJson"));
    Button* btn = static_cast<Button*>(layout->getChildByName("register"));
    if(btn){
        btn->addTouchEventListener(this,toucheventselector(RegisterLayer::registerCallback));
    }
    
    addWidget(layout);
    return true;
}

void RegisterLayer::onEnter()
{
    GameProtoHandler::GetInstance().RegisterProtoHandler(this);
    TouchGroup::onEnter();
}

void RegisterLayer::onExit()
{
    GameProtoHandler::GetInstance().UnRegisterProtoHandler(this);
    TouchGroup::onExit();
}

void RegisterLayer::registerCallback(CCObject* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        GameProtoHandler::GetInstance().RoleCreateReq("");
    }
}

void RegisterLayer::Response(std::string route,int result)
{
    if(result == 0)
    {
        CCTransitionFadeBL* transition = CCTransitionFadeBL::create(2, FLGame::scene());
        if (transition)
        {
            CCDirector::sharedDirector()->replaceScene(transition);
        }
    }
}
