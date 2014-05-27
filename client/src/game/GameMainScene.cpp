//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by yy on 14-5-26.
//
//

#include "GameMainScene.h"
#include "LoadingScene.h"
#include "net/GameProtoHandler.h"
#include "common/FLTextInput.h"
#include "entity/FLPlayer.h"

extern void registerWeiboLogin();

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

CCScene* GameMainLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameMainLayer *layer = GameMainLayer::create();
    scene->addChild(layer,1);
    return scene;
}

bool GameMainLayer::init()
{
    TouchGroup::init();
    Layout* layout = static_cast<Layout*>(GUIReader::shareReader()->
                                          widgetFromJsonFile
                                          ("ui/fallingsky-ui-main.ExportJson"));
    Button* btn = static_cast<Button*>(layout->getChildByName("menu"));
    if(btn){
        btn->addTouchEventListener(this,toucheventselector(GameMainLayer::menuCallback));
    }
    
    ImageView* image = static_cast<ImageView*>(layout->getChildByName("portrait"));
    if (image) {
    }
    
    Label* nickname = static_cast<Label*>(layout->getChildByName("nickname"));
    if (nickname) {
        nickname->setText(FLPlayer::GetInstance().GetNickName());
    }
    
    addWidget(layout);
    return true;
}

void GameMainLayer::onEnter()
{
    GameProtoHandler::GetInstance().RegisterProtoHandler(this);
    TouchGroup::onEnter();
}

void GameMainLayer::onExit()
{
    GameProtoHandler::GetInstance().UnRegisterProtoHandler(this);
    TouchGroup::onExit();
}

void GameMainLayer::menuCallback(CCObject* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        ((Button*)pSender)->setEnabled(false);
        GameProtoHandler::GetInstance().StartBattleReq();
    }
}

void GameMainLayer::Response(std::string route,int result)
{
    if (route.compare("game.battleHandler.start") == 0)
    {
        if(result == 0)
        {
            //CCTransitionFadeBL* transition = CCTransitionFadeBL::create(1, LoadingScene::scene(LOADING_STATE_APP_START));
            //if (transition)
            {
                CCDirector::sharedDirector()->replaceScene(FLGame::scene());
            }
        }
    }
}