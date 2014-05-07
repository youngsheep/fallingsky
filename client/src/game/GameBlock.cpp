#include "GameBlock.h"
#include "sprite_nodes/CCSprite.h"
#include "support/CCPointExtension.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "GameScene.h"

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

FLGameBlock::FLGameBlock(FLGame& pGame)
    : m_pGame(pGame)
    , m_state(GAME_BLOCK_STATE_IDLE)
{
    initWithFile("block.png",16);
}


FLGameBlock::~FLGameBlock(void)
{
}

void FLGameBlock::InitBlock(int type)
{
    CCAssert(type >= 0 && type < 7 , "type error!");
    
    removeAllChildren();
    InitItem((const int*)BLOCK_TYPE_VALUE[type]);

    SetBlockXY(8,0);
    setVisible(true);
    SetState(GAME_BLOCK_STATE_IDLE);

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

void FLGameBlock::rotate()
{
    int temp[4][4] = {{0}};
    for (int i = 0; i < 4; i++) {
        for (int j = 0 ; j < 4; j++) {
            temp[i][j] = m_block[3-j][i];
        }
    }
    
    removeAllChildren();
    InitItem((const int*)temp);
}

void FLGameBlock::SetBlockXY(int x, int y)
{
    m_blockX = x;
    m_blockY = y;

    setPosition(x*GAME_BLOCK_SIZE,y*GAME_BLOCK_SIZE);
    //CCLOG("pos x :%.0f  pos y :%.0f",getPositionX(),getPositionY());
    //CCLOG("block x :%d  block y :%d",m_blockX,m_blockY);
}

int FLGameBlock::GetBlockStatus(int x ,int y)
{
    CCAssert(x >= 0 && x < 4 , "x error!");
    CCAssert(y >= 0 && y < 4 , "y error!");

    return m_block[x][y];
}

void FLGameBlock::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
    CCSpriteBatchNode::onEnter();
}

void FLGameBlock::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSpriteBatchNode::onExit();
}

CCRect FLGameBlock::rect()
{
    return CCRectMake(0, 0, 4 * GAME_BLOCK_SIZE, 4 * GAME_BLOCK_SIZE);
}

bool FLGameBlock::containsTouchLocation(CCTouch *touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool FLGameBlock::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    if (m_state > GAME_BLOCK_STATE_IDLE) {
        return false;
    }
    
    if (containsTouchLocation(touch)) {
        return true;
    }
    return false;
}

void FLGameBlock::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
    CCPoint delta = touch->getDelta();
    if (m_state == GAME_BLOCK_STATE_IDLE
        && abs(delta.x * 2) < abs(delta.y) && abs(delta.y) > 10)
    {
        m_pGame.scheduleUpdate();
        m_state = GAME_BLOCK_STATE_V_MOVING;
    }
    else if((m_state == GAME_BLOCK_STATE_IDLE && abs(delta.y * 2) < abs(delta.x) )
            || m_state == GAME_BLOCK_STATE_H_MOVING)
    {
        CCLOG("delta x : %.0f , y %.0f " , delta.x,delta.y);
        setPosition(getPositionX() + delta.x, getPositionY());
        m_blockX = int (getPositionX() / GAME_BLOCK_SIZE);
        m_pGame.CheckXMove();
        m_state = GAME_BLOCK_STATE_H_MOVING;
    }
}

void FLGameBlock::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    if (m_state == GAME_BLOCK_STATE_IDLE) {
        CCPoint delta = touch->getDelta();
        if (delta.getLength() < 3) {
            rotate();
        }
    }
    else if(m_state == GAME_BLOCK_STATE_H_MOVING)
    {
        m_blockX = int (getPositionX() / GAME_BLOCK_SIZE + 0.5);
        SetBlockXY(m_blockX, m_blockY);
        m_state = GAME_BLOCK_STATE_IDLE;
    }
    
}
