//
//  GameMainScene.h
//  HelloCpp
//
//  Created by yy on 14-5-26.
//
//

#ifndef __HelloCpp__GameMainScene__
#define __HelloCpp__GameMainScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "net/GameProtoHandler.h"

class GameMainLayer : public cocos2d::ui::TouchGroup, public IGameProtoHandler
{
public:
    GameMainLayer(){}
    virtual ~GameMainLayer(){}
    
    virtual bool init();
    // CCLayer
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    //IGameProtoHandler
    virtual void Response(std::string route,int result);
    
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCallback(CCObject* pSender,cocos2d::ui::TouchEventType type);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameMainLayer);
};


#endif /* defined(__HelloCpp__GameMainScene__) */
