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

    m_BlockSpeed = 1;
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
            if (getGameBlock()->GetBlockY() < 0 )
            {
                //gameover
                unscheduleUpdate();
            }

            fill_block();
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
    setGameBlock(new FLGameBlock());
    getGameBlock()->InitBlock(type);
    getTileMap()->addChild(getGameBlock());
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
            }
        }
    }
}

bool FLGame::can_move_x(bool left)
{
    CCAssert(getGameBlock(), "move block is null");
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
    
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
    CCLayer::onEnter();
}

void FLGame::onExit(){
    
    //CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
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
