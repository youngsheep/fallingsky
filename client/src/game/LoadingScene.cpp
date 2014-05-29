//
//  LoadingScene.cpp
//  HelloCpp
//
//  Created by yy on 14-5-25.
//
//

#include "LoadingScene.h"
#include "GameMainScene.h"
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

void LoadingScene::onEnterTransitionDidFinish()
{
    TouchGroup::onEnterTransitionDidFinish();
    StartLoadingSchdule();
}

void LoadingScene::onExit()
{
    GameProtoHandler::GetInstance().UnRegisterProtoHandler(this);
    TouchGroup::onExit();
}

void LoadingScene::Response(std::string route,int result,json::Value data)
{
    if (route.compare("game.roleHandler.info") == 0) {
        if(result == 0)
        {
            m_loadingStep ++;
        }
        else if (result < 0)
        {
        }
    }
}

void LoadingScene::StartLoadingSchdule()
{
    switch (m_loadingState)
    {
        case LOADING_STATE_APP_START:
        {
            CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(LoadingScene::AppStartLoading), this, 0, false);
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
                                             
void LoadingScene::AppStartLoading(float delta)
{
    switch (m_loadingStep) {
        case 0:
        {
            GameProtoHandler::GetInstance().RoleInfoReq();
            m_loadingStep ++;
            break;
        }
        case 1:
            CCLog("wait RoleInfoReq");
            break;
        case 2:
        {
            CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(LoadingScene::AppStartLoading), this);
            ChangeScene();
            m_loadingStep ++;
            break;
        }
            
        default:
            break;
    }
}

void LoadingScene::ChangeScene()
{
    switch (m_loadingState)
    {
    case LOADING_STATE_APP_START:
        {
            CCTransitionSlideInR* transition = CCTransitionSlideInR::create(1, GameMainLayer::scene());
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