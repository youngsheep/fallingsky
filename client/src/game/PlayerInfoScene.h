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

class PlayerInfo : public cocos2d::CCLayer
{
public:
    PlayerInfo(){}
    virtual ~PlayerInfo(){}
    
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    // a selector callback
    void loginCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(PlayerInfo);
};

#endif /* defined(__HelloCpp__PlayerInfoScene__) */
