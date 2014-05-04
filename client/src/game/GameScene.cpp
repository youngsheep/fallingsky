#include "GameScene.h"

USING_NS_CC;

CCScene* FLGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FLGame *layer = FLGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

FLGame::FLGame()
{
    _tileMap = NULL;
    _background = NULL;
    _gameBlock = NULL;

    m_BlockSpeed = 2;
}

FLGame::~FLGame()
{
}
// on "init" you need to initialize your instance
bool FLGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    do 
    {    
        this->setTileMap(CCTMXTiledMap::create("bg.tmx"));
        this->setBackground(_tileMap->layerNamed("back"));
        this->addChild(_tileMap, -1);

        generate_block();

    } while (0);
  
    scheduleUpdate();
    return true;
}

void FLGame::update(float delta)
{
    if (can_move_y(m_BlockSpeed))
    {
        const CCPoint& p = getGameBlock()->getPosition();
        getGameBlock()->setPosition(p.x,p.y + m_BlockSpeed);
    }
    else
    {
        if (getGameBlock()->GetBlockY() <= 0 )
        {
            //gameover
            unscheduleUpdate();
        }
        else
        {
            fill_block();
            generate_block();
        }
    }

}

void FLGame::generate_block()
{
    int type = rand()%7;
    setGameBlock(new FLGameBlock());
    getGameBlock()->InitBlock(type);
    getTileMap()->addChild(getGameBlock());
}

void FLGame::fill_block()
{
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ;j++)
        {
            if (getGameBlock()->GetBlockStatus(i,j) != 0)
            {
                int bgx = j + getGameBlock()->GetBlockX();
                int bgy = i + getGameBlock()->GetBlockY() - 4;

                const CCSize& LayerSize = getBackground()->getLayerSize();
                CCAssert((bgy >= 0 && bgy < LayerSize.height) , "error");

                int status = getBackground()->tileGIDAt(ccp(bgx,bgy));
                CCAssert(status == 0 || status == 4 , "this position already have tile" );
               
                getBackground()->setTileGID(1,ccp(bgx,LayerSize.height - bgy));
            }
        }
    }

    getGameBlock()->setVisible(false);
}

bool FLGame::can_move_x(bool left)
{
    CCAssert(getGameBlock(), "move block is null");
    return true;
}

bool FLGame::can_move_y(int offset)
{
    CCAssert(getGameBlock() , "move block is null");

    static int y = GAME_BLOCK_SIZE;

    if (y < GAME_BLOCK_SIZE)
    {
        y += offset;
        return true;
    }

    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ;j++)
        {
            if (getGameBlock()->GetBlockStatus(i,j) != 0)
            {
                int bgx = j + getGameBlock()->GetBlockX();
                int bgy = i + getGameBlock()->GetBlockY() - 3;

                const CCSize& LayerSize = getBackground()->getLayerSize();
                if (bgy < 0)
                {
                    continue;
                }

                if ((bgy >= LayerSize.height - 1))
                {
                    y = GAME_BLOCK_SIZE;
                    return false;
                }

                int status = getBackground()->tileGIDAt(ccp(bgx, LayerSize.height - 1 - bgy));
                if (status > 0 && status != 4)
                {
                    y = GAME_BLOCK_SIZE;
                    return false;
                }                
            }
        }
    }

    getGameBlock()->SetBlockXY(getGameBlock()->GetBlockX(),getGameBlock()->GetBlockY() + y / GAME_BLOCK_SIZE);
    y = 0;
    return true;
}
