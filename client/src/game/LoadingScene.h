//
//  LoadingScene.h
//  HelloCpp
//
//  Created by yy on 14-5-25.
//
//

#ifndef __HelloCpp__LoadingScene__
#define __HelloCpp__LoadingScene__

class LoadingScene : public cocos2d::ui::TouchGroup,public IGameProtoHandler
{
public:
    LoadingScene(){}
    virtual LoadingScene(){}
    
    virtual bool init();
    // CCLayer
    virtual void onEnter();
    virtual void onExit();
    
    //IGameProtoHandler
    virtual void Response(std::string route,int result);
    
    
    // a selector callback
    void loginCallback(CCObject* pSender,cocos2d::ui::TouchEventType type);
    
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    CREATE_FUNC(LoadingScene);
    
    void SetState(int state){m_loadingState = state;}
    
private:
    int m_loadingState;
    
};


#endif /* defined(__HelloCpp__LoadingScene__) */
