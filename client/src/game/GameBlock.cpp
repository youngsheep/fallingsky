#include "GameBlock.h"
#include "sprite_nodes/CCSprite.h"
#include "support/CCPointExtension.h"

USING_NS_CC;

const int BLOCK_TYPE_VALUE[][4][4] = {
    {
         {1, 1, 0, 0}
        ,{1, 1, 0, 0}
        ,{0, 0, 0, 0}
        ,{0, 0, 0, 0}
    },
    {
         {2, 0, 0, 0}
        ,{2, 0, 0, 0}
        ,{2, 2, 0, 0}
        ,{0, 0, 0, 0}
    },
    {
         {0, 3, 0, 0}
        ,{3, 3, 3, 0}
        ,{0, 0, 0, 0}
        ,{0, 0, 0, 0}
    },
    {
         {4, 4, 0, 0}
        ,{0, 4, 4, 0}
        ,{0, 0, 0, 0}
        ,{0, 0, 0, 0}
    },
    {
         {0, 5, 5, 0}
        ,{5, 5, 0, 0}
        ,{0, 0, 0, 0}
        ,{0, 0, 0, 0}
    },
    {
         {0, 6, 0, 0}
        ,{0, 6, 0, 0}
        ,{6, 6, 0, 0}
        ,{0, 0, 0, 0}
    },
    {
         {7, 7, 7, 7}
        ,{0, 0, 0, 0}
        ,{0, 0, 0, 0}
        ,{0, 0, 0, 0}
    }
};

FLGameBlock::FLGameBlock(void)
{
    initWithFile("block.png",16);
}


FLGameBlock::~FLGameBlock(void)
{
}

void FLGameBlock::InitBlock(int type)
{
    CCAssert(type >= 0 && type < 7 , "type error!");
    InitItem((const int*)BLOCK_TYPE_VALUE[type]);

    SetBlockXY(8,-4);

}

void FLGameBlock::InitItem(const int* bItem)
{
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0 ; j < 4; j++)
        {
            m_block[i][j] = *(bItem+i*4+j);

            if (m_block[i][j] != 0)
            {
                CCRect rect = CCRectMake(1,1,GAME_BLOCK_SIZE,GAME_BLOCK_SIZE);
                CCSprite* item = CCSprite::createWithTexture(this->getTexture(),rect);
                item->setPosition( ccp(j*GAME_BLOCK_SIZE, i*GAME_BLOCK_SIZE) );
                item->setAnchorPoint(ccp(0,0));
                addChild(item);
            }
        }
    }
}

void FLGameBlock::SetBlockXY(int x, int y)
{
    m_blockX = x;
    m_blockY = y;

    setPosition(x*GAME_BLOCK_SIZE,y*GAME_BLOCK_SIZE);
    CCLOG("bloc x :%f  block y :%f",getPositionX(),getPositionY());
}

int FLGameBlock::GetBlockStatus(int x ,int y)
{
    CCAssert(x >= 0 && x < 4 , "x error!");
    CCAssert(y >= 0 && y < 4 , "y error!");

    return m_block[x][y];
}
