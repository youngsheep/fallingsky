//
//  FLTextInput.cpp
//  HelloCpp
//
//  Created by yy on 14-5-21.
//
//

#include "FLTextInput.h"

USING_NS_CC;

FLTextInput::FLTextInput()
{
    
}

FLTextInput* FLTextInput::textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)
{
    FLTextInput *pRet = new FLTextInput();
    if(pRet && pRet->initWithString("", fontName, fontSize))
    {
        pRet->autorelease();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

// CCLayer
void FLTextInput::onEnter()
{
    
}

void FLTextInput::onExit()
{
    
}

// 初始化光标精灵
void FLTextInput::initCursorSprite(int nHeight)
{
    m_pCursorSprite = new CCSprite();
}

// CCTextFieldDelegate
bool FLTextInput::onTextFieldAttachWithIME(CCTextFieldTTF *pSender)
{
    return true;
}

bool FLTextInput::onTextFieldDetachWithIME(CCTextFieldTTF * pSender)
{
    return true;
}

// CCLayer Touch
bool FLTextInput::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isInTextField(pTouch)) {
        openIME();
        return true;
    }
    return false;
}

void FLTextInput::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    //openIME();
}

bool FLTextInput::isInTextField(cocos2d::CCTouch *pTouch)
{
    return this->getTextureRect().containsPoint(convertTouchToNodeSpaceAR(pTouch));
}

void FLTextInput::openIME()
{
    m_pCursorSprite->setVisible(true);
    this->attachWithIME();
}

void FLTextInput::closeIME()
{
    m_pCursorSprite->setVisible(false);
    this->detachWithIME();
}

bool FLTextInput::onTextFieldInsertText(cocos2d::CCTextFieldTTF *pSender, const char *text, int nLen)
{
    CCLOG("Width: %f", pSender->getContentSize().width);
    CCLOG("Text: %s", text);
    CCLOG("Length: %d", nLen);
    
    m_pInputText->append(text);
    setString(m_pInputText->c_str());
    
    m_pCursorSprite->setPositionX(getContentSize().width);
    
    return true;
}

bool FLTextInput::onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF *pSender, const char *delText, int nLen)
{
    m_pInputText->resize(m_pInputText->size() - nLen);
    setString(m_pInputText->c_str());
    
    m_pCursorSprite->setPositionX(getContentSize().width);
    
    if (m_pInputText->empty()) {
        m_pCursorSprite->setPositionX(0);
    }
    
    return false;
}