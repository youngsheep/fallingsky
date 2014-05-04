#ifndef _FALLING_SKY_GAME_BLOCK_H_
#define _FALLING_SKY_GAME_BLOCK_H_

#include "sprite_nodes/CCSpriteBatchNode.h"

#define GAME_BLOCK_SIZE 32

class FLGameBlock :
    public cocos2d::CCSpriteBatchNode
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

protected:
    int m_block[4][4];

    int m_blockX;
    int m_blockY;
};

#endif


