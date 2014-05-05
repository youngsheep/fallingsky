#ifndef _FALLING_SKY_GAME_BLOCK_H_
#define _FALLING_SKY_GAME_BLOCK_H_

#include "sprite_nodes/CCSpriteBatchNode.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "touch_dispatcher/CCTouch.h"
#include "cocoa/CCGeometry.h"

#define GAME_BLOCK_SIZE 32

class FLGameBlock :
    public cocos2d::CCSpriteBatchNode,
    public cocos2d::CCTargetedTouchDelegate
{
public:
    FLGameBlock(void);
    virtual ~FLGameBlock(void);

    void InitBlock(int type);
    void InitItem(const int* bItem);

    void SetBlockXY(int x, int y);

    int GetBlockX(){return m_blockX;}
    int GetBlockY(){return m_blockY;}

    int GetBlockStatus(int x ,int y);
    
    virtual void onEnter();
    virtual void onExit();
    
    cocos2d::CCRect rect();
    bool containsTouchLocation(cocos2d::CCTouch *touch);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);

protected:
    int m_block[4][4];

    int m_blockX;
    int m_blockY;
};

#endif


