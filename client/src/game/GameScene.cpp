#include "GameScene.h"
#include "entity/FLPlayer.h"
#include "net/GameProtoHandler.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

CCScene* FLGameUI::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FLGameUI *myLayer = FLGameUI::create();

    // add layer as a child to scene
    scene->addChild(myLayer,1);
    
    // return the scene
    return scene;
}

FLGameUI::FLGameUI()
    : m_pMyGame(NULL)
    , m_pOppGame(NULL)
{

}

FLGameUI::~FLGameUI()
{
    if (m_pMyGame)
    {
        m_pMyGame->release();
    }
    if (m_pOppGame)
    {
        m_pOppGame->release();
    }
}

bool FLGameUI::init()
{
    TouchGroup::init();
    Layout* layout = static_cast<Layout*>(GUIReader::shareReader()->
        widgetFromJsonFile
        ("ui/fallingsky-ui-game.ExportJson"));

    addWidget(layout);

    FLPlayer& player = FLPlayer::GetInstance();

    Widget* panel1 = layout->getChildByName("game_panel1");
    Widget* panel2 = layout->getChildByName("game_panel2");

    Label* myname = static_cast<Label*>(layout->getChildByName("nickname1"));
    if (myname) {
        myname->setText(player.GetNickName());
    }
    m_pMyGame = FLGame::create(true);
    m_pMyGame->retain();
    m_pMyGame->setPosition(panel1->getPosition());
    addChild(m_pMyGame);

    Label* oppname = static_cast<Label*>(layout->getChildByName("nickname2"));
    ImageView* oppimage = static_cast<ImageView*>(layout->getChildByName("portrait2"));

    if (oppname && oppimage)
    {
        if (player.GetBattle().GetType() == FL_BATTLE_TYPE_PVE)
        {
            oppname->setVisible(false);
            oppimage->setVisible(false);
            panel2->setVisible(false);
        }
        else
        {
            oppname->setText(player.GetBattle().GetOppName());

            m_pOppGame = FLGame::create(false);
            m_pOppGame->retain();
            m_pOppGame->setPosition(panel2->getPosition());
            addChild(m_pOppGame);
        }
    }


    return true;
}

void FLGameUI::onEnter()
{
    GameProtoHandler::GetInstance().RegisterProtoHandler(this);
    TouchGroup::onEnter();
}

void FLGameUI::onExit()
{
    GameProtoHandler::GetInstance().UnRegisterProtoHandler(this);
    TouchGroup::onExit();
}

void FLGameUI::Response(std::string route,int result,json::Value data)
{
    if (route.compare("game.battleHandler.cmd") == 0)
    {
        if (result == 0) {
            m_pMyGame->GenerateBlock(FLPlayer::GetInstance().GetBattle().PickNextBlock());
        }

    }
    else if (route.compare("oppstate") == 0)
    {
        int oppblocktype = data["nextType"].as_integer();
        int oppPosX = data["blockXPos"].as_integer();
        
        m_pOppGame->GenerateBlock(oppblocktype);
        m_pOppGame->getGameBlock()->SetBlockXY(oppPosX, 0);
        
        int flag = data["blockFlag"].as_integer();
        flag %= 4;
        for (int i = 0 ; i < flag; i++) {
            m_pOppGame->getGameBlock()->Rotate();
        }
        
        m_pOppGame->scheduleUpdate();
    }
}

FLGame::FLGame(bool bself)
{
    _tileMap = NULL;
    _background = NULL;
    _gameBlock = NULL;

    m_BlockSpeed = 8;
    m_BlockHeight = 0;
    m_isBlockMove = false;
    
    m_bmyself = bself;
}

FLGame::~FLGame()
{
}
// on "init" you need to initialize your instance
bool FLGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !TouchGroup::init() )
    {
        return false;
    }

    do 
    {
        
        this->setTileMap(CCTMXTiledMap::create("bg.tmx"));
        this->setBackground(_tileMap->layerNamed("block_grid"));
        this->addChild(_tileMap, -1);

        setGameBlock(new FLGameBlock(*this));
        getTileMap()->addChild(getGameBlock());
        if (m_bmyself) {
            GenerateBlock(FLPlayer::GetInstance().GetBattle().PickNextBlock());
        }

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

    int blockoffset = offset / GAME_BLOCK_SIZE_H;

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
            if (m_bmyself) {
                int bx = getGameBlock()->GetBlockX();
                int by = LayerSize.height - getGameBlock()->GetBlockY() - 2;
                GameProtoHandler::GetInstance().BattleCmdReq(bx,by,getGameBlock()->GetBlockFlag());
            }

            if (LayerSize.height - m_BlockHeight < 4 )
            {
                //gameover
                return;
            
            }
            //generate_block();

            return;
        }
    }

    offset = offset % GAME_BLOCK_SIZE_H;
    int inc = blockoffset > 0 ? offset : m_BlockSpeed;
    const CCPoint& p = getGameBlock()->getPosition();
    getGameBlock()->setPosition(p.x,p.y + inc);
}

void FLGame::GenerateBlock(int type)
{
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
                CCAssert(status == 0 || status == 3 , "this position already have tile" );
               
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
            if (status == 0 || status == 3)
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
                if (status > 0 && status != 3)
                {
                    return false;
                }                
            }
        }
    }
    return true;
}
