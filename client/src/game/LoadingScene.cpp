//
//  LoadingScene.cpp
//  HelloCpp
//
//  Created by yy on 14-5-25.
//
//

#include "LoadingScene.h"
#include "GameScene.h"
#include "net/GameProtoHandler.h"
#include "RegisterScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

CCScene* LoadingScene::scene(int state)
{
    CCScene *scene = CCScene::create();
    LoadingScene *layer = LoadingScene::create();
    layer->SetState(state);
    scene->addChild(layer,1);
    return scene;
}

bool LoadingScene::init()
{
    TouchGroup::init();
    Layout* layout = static_cast<Layout*>(GUIReader::shareReader()->
                                          widgetFromJsonFile
                                          ("ui/fallingsky-ui-loading.ExportJson"));  
    addWidget(layout);
    return true;
}

void LoadingScene::onEnter()
{
    GameProtoHandler::GetInstance().RegisterProtoHandler(this);
    TouchGroup::onEnter();
}

void LoadingScene::onExit()
{
    GameProtoHandler::GetInstance().UnRegisterProtoHandler(this);
    TouchGroup::onExit();
}

void LoadingScene::Response(std::string route,int result)
{
    if (route.compare("connector.entryHandler.entry") == 0) {
        if(result == 0)
        {
        }
        else if (result < 0)
        {
        }
    }
}

void LoadingScene::ChangeScene()
{
    switch (m_loadingState)
    {
    case LOADING_STATE_APP_START:
        {
            CCTransitionFadeBL* transition = CCTransitionFadeBL::create(1, FLGame::scene());
            if (transition)
            {
                CCDirector::sharedDirector()->replaceScene(transition);
            }
            break;
        }
    case LOADING_STATE_GAME_START:
        break;
    case LOADING_STATE_GAME_END:
        break;
    default:
        break;
    }
}