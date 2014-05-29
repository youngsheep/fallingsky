//
//  FLMsgBox.h
//  HelloCpp
//
//  Created by yy on 14-5-29.
//
//

#ifndef __HelloCpp__FLMsgBox__
#define __HelloCpp__FLMsgBox__

#include "cocos2d.h"
#include "cocos-ext.h"

class FLMsgBox : public cocos2d::ui::TouchGroup
{
public:
    FLMsgBox(){}
    virtual ~FLMsgBox()
    {
        if (m_pTitle) {
            m_pTitle->release();
        }
    }
    
    virtual bool init();
    
    // a selector callback
    void YesCallback(CCObject* pSender,cocos2d::ui::TouchEventType type);
    void NoCallback(CCObject* pSender,cocos2d::ui::TouchEventType type);
    
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    CREATE_FUNC(FLMsgBox);
    
protected:
    cocos2d::ui::Label* m_pTitle;
};


#endif /* defined(__HelloCpp__FLMsgBox__) */
