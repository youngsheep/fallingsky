//
//  FLMsgBox.cpp
//  HelloCpp
//
//  Created by yy on 14-5-29.
//
//

#include "FLMsgBox.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

CCScene* FLMsgBox::scene()
{
    CCScene *scene = CCScene::create();
    FLMsgBox *layer = FLMsgBox::create();
    scene->addChild(layer,1);
    return scene;
}

bool FLMsgBox::init()
{
    const CCSize& winsize = CCDirector::sharedDirector()->getWinSize();
    TouchGroup::init();
    Layout* layout = static_cast<Layout*>(GUIReader::shareReader()->
                                          widgetFromJsonFile
                                          ("ui/fallingsky-ui-msgbox.ExportJson"));
    if (layout) {
        const CCSize& boxsize = layout->getSize();
        CCSize pos = winsize /2 - boxsize /2;
        layout->setPosition(ccp(pos.width,pos.height));
    }
    
    Button* btn = static_cast<Button*>(layout->getChildByName("yes"));
    if(btn){
        btn->addTouchEventListener(this,toucheventselector(FLMsgBox::YesCallback));
    }
    
    btn = static_cast<Button*>(layout->getChildByName("no"));
    if(btn){
        btn->addTouchEventListener(this,toucheventselector(FLMsgBox::NoCallback));
    }
    
    m_pTitle = static_cast<Label*>(layout->getChildByName("titile"));
    if (m_pTitle) {
        m_pTitle->retain();
    }
    addWidget(layout);
    return true;
}

void FLMsgBox::YesCallback(CCObject* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        removeFromParent();
    }
}

void FLMsgBox::NoCallback(CCObject* pSender,TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        removeFromParent();
    }
}
