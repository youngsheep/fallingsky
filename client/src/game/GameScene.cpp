#include "GameScene.h"
//#include "common/PomeloConnection.h"

USING_NS_CC;

//LoginRequest FLGame::m_loginReq;
//FLBattle FLGame::m_battle;

CCScene* FLGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FLGame *myLayer = FLGame::create();

    // add layer as a child to scene
    scene->addChild(myLayer,1,enuMyGameArea_Tag);

    FLGame *eneLayer = FLGame::create();
    eneLayer->setPositionX(480);
    scene->addChild(eneLayer,1,enuEnemyGameArea_Tag);
    
    //PomeloConnection::getInstance().Connect("127.0.0.1", 3010);
    //FLGame::m_loginReq.DoLogin();
    //FLGame::m_battle.GetRequest().StartBattleReq();
    
    // return the scene
    return scene;
}

FLGame::FLGame()
{
    _tileMap = NULL;
    _background = NULL;
    _gameBlock = NULL;

    m_BlockSpeed = 8;
    m_BlockHeight = 0;
    m_isBlockMove = false;
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
        //CCSprite* bg = CCSprite::create("bg.png");
        //bg->setAnchorPoint(ccp(0,0));
        //addChild(bg,-2);
        
        this->setTileMap(CCTMXTiledMap::create("bg.tmx"));
        this->setBackground(_tileMap->layerNamed("block_grid"));
        this->addChild(_tileMap, -1);

        setGameBlock(new FLGameBlock(*this));
        getTileMap()->addChild(getGameBlock());
        generate_block();

    } while (0);
  
    m_BlockSpeed = 8;
    m_BlockHeight = 0;

    //scheduleUpdate();
    return true;
}

void FLGame::update(float delta)
{
    static int offset = 0;

    offset += m_BlockSpeed;

    int blockoffset = offset / GAME_BLOCK_SIZE;

    for (int i = 0 ; i < blockoffset ; i++)
    {
        if (can_move_y())
        {      
            getGameBlock()->SetBlockXY(getGameBlock()->GetBlockX(),getGameBlock()->GetBlockY() + 1);
        }
        else
        {
            unscheduleUpdate();
            getGameBlock()->SetState(GAME_BLOCK_STATE_IDLE);
            
            fill_block();
            check_score();
            
            const CCSize& LayerSize = getBackground()->getLayerSize();
            if (LayerSize.height - m_BlockHeight < 4 )
            {
                //gameover
                return;
            
            }
            generate_block();

            return;
        }
    }

    offset = offset % GAME_BLOCK_SIZE;
    int inc = blockoffset > 0 ? offset : m_BlockSpeed;
    const CCPoint& p = getGameBlock()->getPosition();
    getGameBlock()->setPosition(p.x,p.y + inc);
}

void FLGame::generate_block()
{
    int type = rand()%7;
    getGameBlock()->InitBlock(type);
}

void FLGame::fill_block()
{
    getGameBlock()->setVisible(false);

    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ;j++)
        {
            if (getGameBlock()->GetBlockStatus(i,j) != 0)
            {
                int bgx = j + getGameBlock()->GetBlockX();
                int bgy = i + getGameBlock()->GetBlockY()+1;

                const CCSize& LayerSize = getBackground()->getLayerSize();
                CCAssert((bgy >= 0 && bgy < LayerSize.height) , "error");

                int status = getBackground()->tileGIDAt(ccp(bgx, LayerSize.height - 1 - bgy));
                CCAssert(status == 0 || status == 4 , "this position already have tile" );
               
                getBackground()->setTileGID(1,ccp(bgx,LayerSize.height - 1 - bgy));

                if (m_BlockHeight < LayerSize.height - 1 - bgy)
                {
                    m_BlockHeight = LayerSize.height - 1 - bgy;
                }
            }
        }
    }
}

void FLGame::check_score()
{
    const CCSize& LayerSize = getBackground()->getLayerSize();
    bool needrefresh = false;
    for(int i = 0 ; i < 4 ;i++)
    {
        int bgy = LayerSize.height - 2 - getGameBlock()->GetBlockY() - i;
        if (bgy < 0 )
            break;
        
        bool isFull = true;
        unsigned int* tiles = getBackground()->getTiles();
        for (int j = 0 ; j < LayerSize.width ; j++)
        {
            int status = *(tiles + int(bgy*LayerSize.width) + j);
            if (status == 0 || status == 4)
            {
                isFull = false;
                break;
            }
        }

        if (isFull)
        {
            needrefresh  = true;
            for (int j = bgy ; j <= m_BlockHeight ; j++)
            {
                int w = LayerSize.width;
                memcpy(tiles + j*w , tiles + (j+1)*w,sizeof(unsigned int)*w);              
            }
            --m_BlockHeight;
        }
    }

    if (needrefresh)
    {
        getBackground()->setupTiles();
    }
}

bool FLGame::CheckXMove()
{
    int blockX = getGameBlock()->GetBlockX();
    const CCSize& LayerSize = getBackground()->getLayerSize();
    if (blockX  >= 0 && blockX <= LayerSize.width - 4)
    {
        return true;
    }

    bool leftCheck = true;

    if (blockX > LayerSize.width /2)
    {
        leftCheck = false;
    }

    int offx = leftCheck ? 3 : 0;
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ;j++)
        {
            int y = leftCheck ? j : 3-j ;
            if (getGameBlock()->GetBlockStatus(i,y) != 0)
            {
                if (leftCheck)
                {
                    if (offx > y)
                    {
                        offx = y;
                        break;
                    }
                }
                else
                {
                    if (offx < y)
                    {
                        offx = y;
                        break;
                    }
                }                             
            }
        }
    }

    int bx = blockX + offx;
    if (leftCheck)
    {
        if (bx <= 0)
        {
            getGameBlock()->SetBlockXY(blockX - bx , getGameBlock()->GetBlockY());
        }
    }
    else
    {
        if (bx >= LayerSize.width - 1)
        {
            getGameBlock()->SetBlockXY(blockX + LayerSize.width - 1 - bx , getGameBlock()->GetBlockY());
        }
    }

    return true;
}

bool FLGame::can_move_y()
{
    CCAssert(getGameBlock() , "move block is null");

    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ;j++)
        {
            if (getGameBlock()->GetBlockStatus(i,j) != 0)
            {
                int bgx = j + getGameBlock()->GetBlockX();
                int bgy = i + getGameBlock()->GetBlockY() + 1;

                const CCSize& LayerSize = getBackground()->getLayerSize();
                if (bgy < 0)
                {
                    continue;
                }

                if ((bgy >= LayerSize.height - 1))
                {
                    return false;
                }

                int status = getBackground()->tileGIDAt(ccp(bgx, LayerSize.height - 2 - bgy));
                if (status > 0 && status != 4)
                {
                    return false;
                }                
            }
        }
    }
    return true;
}

void FLGame::onEnter(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
    CCLayer::onEnter();
}

void FLGame::onExit(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool FLGame::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchBegan");
    return true;
}

void FLGame::ccTouchMoved(CCTouch* touch, CCEvent* event){
    CCLOG("ccTouchMoved");
}

void FLGame::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchEnded");
    //获取离开屏幕时对应的坐标
    CCPoint point = touch->getLocation();
}
