//
//  RegisterScene.h
//  HelloCpp
//
//  Created by yy on 14-5-16.
//
//

#ifndef __HelloCpp__RegisterScene_H_
#define __HelloCpp__RegisterScene_H_

#include "cocos2d.h"

class RegisterLayer : public cocos2d::CCLayer
{
public:
    RegisterLayer(){}
    virtual ~RegisterLayer(){}
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void registerCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(RegisterLayer);
};

#endif /* defined(__HelloCpp__RegisterScene_H_) */
