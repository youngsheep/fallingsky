//
//  PlayerInfoScene.h
//  HelloCpp
//
//  Created by yy on 14-5-12.
//
//

#ifndef __HelloCpp__PlayerInfoScene__
#define __HelloCpp__PlayerInfoScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "net/GameProtoHandler.h"

class PlayerInfo : public cocos2d::ui::TouchGroup,public IGameProtoHandler
{
public:
    PlayerInfo(){}
    virtual ~PlayerInfo(){}
    
    virtual bool init();
    // CCLayer
    virtual void onEnter();
    virtual void onExit();
    
    //IGameProtoHandler
    virtual void Response(std::string route,int result,json::Value data = json::object());

    // a selector callback
    void loginCallback(CCObject* pSender,cocos2d::ui::TouchEventType type);
    
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    CREATE_FUNC(PlayerInfo);
};

#endif /* defined(__HelloCpp__PlayerInfoScene__) */
