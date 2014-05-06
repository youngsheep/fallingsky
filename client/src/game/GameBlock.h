#ifndef _FALLING_SKY_GAME_BLOCK_H_
#define _FALLING_SKY_GAME_BLOCK_H_

#include "sprite_nodes/CCSpriteBatchNode.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "touch_dispatcher/CCTouch.h"
#include "cocoa/CCGeometry.h"

#define GAME_BLOCK_SIZE 32

enum{
    GAME_BLOCK_STATE_IDLE = 0,
    GAME_BLOCK_STATE_H_MOVING,
    GAME_BLOCK_STATE_V_MOVING,
    GAME_BLOCK_STATE_ROTATE,
};

class FLGame;
class FLGameBlock :
    public cocos2d::CCSpriteBatchNode,
    public cocos2d::CCTargetedTouchDelegate
{
public:
    explicit FLGameBlock(FLGame& pGame);
    virtual ~FLGameBlock(void);

    void InitBlock(int type);
    void InitItem(const int* bItem);

    void SetBlockXY(int x, int y);

    int GetBlockX(){return m_blockX;}
    int GetBlockY(){return m_blockY;}

    int GetBlockStatus(int x ,int y);
    
    void SetState(int state){m_state = state;}
    
    virtual void onEnter();
    virtual void onExit();
    
    cocos2d::CCRect rect();
    bool containsTouchLocation(cocos2d::CCTouch *touch);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);

protected:
    void rotate();
    
protected:
    int m_block[4][4];

    int m_blockX;
    int m_blockY;
    
    int m_state;

    FLGame& m_pGame;
};

#endif


