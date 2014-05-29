//
//  LoadingScene.h
//  HelloCpp
//
//  Created by yy on 14-5-25.
//
//

#ifndef __HelloCpp__LoadingScene__
#define __HelloCpp__LoadingScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "net/GameProtoHandler.h"

enum{
    LOADING_STATE_APP_START = 0,
    LOADING_STATE_GAME_START,
    LOADING_STATE_GAME_END
};
class LoadingScene : public cocos2d::ui::TouchGroup,public IGameProtoHandler
{
public:
    LoadingScene()
    : m_loadingState(LOADING_STATE_APP_START)
    , m_loadingStep(0)
    {}
    virtual ~LoadingScene(){}
    
    virtual bool init();
    // CCLayer
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    //IGameProtoHandler
    virtual void Response(std::string route,int result,json::Value data = json::object());
    
    static cocos2d::CCScene* scene(int state);
    
    void StartLoadingSchdule();
    void AppStartLoading(float delta);

    // implement the "static node()" method manually
    CREATE_FUNC(LoadingScene);
    
    void ChangeScene();

    void SetState(int state){m_loadingState = state;}
    
private:
    int m_loadingState;
    int m_loadingStep;
    
};


#endif /* defined(__HelloCpp__LoadingScene__) */
