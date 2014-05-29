#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "net/GameProtoHandler.h"
#include "GameBlock.h"

class FLGameUI : public cocos2d::ui::TouchGroup,public IGameProtoHandler
{
public:
    FLGameUI();
    virtual ~FLGameUI();

    virtual bool init();
    // CCLayer
    virtual void onEnter();
    virtual void onExit();

    //IGameProtoHandler
    virtual void Response(std::string route,int result);

    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(FLGameUI);

protected:
    FLGame* m_pMyGame;
    FLGame* m_pOppGame;
};

enum 
{
    enuMyGameArea_Tag = 0,
    enuEnemyGameArea_Tag
};

class FLGame : public cocos2d::ui::TouchGroup
{
    CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXLayer*, _background, Background);
    CC_SYNTHESIZE_RETAIN(FLGameBlock*, _gameBlock, GameBlock);

public:
    FLGame();
    virtual ~FLGame();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    virtual void update(float delta);
    
    // implement the "static node()" method manually
    CREATE_FUNC(FLGame);

public:
    bool CheckXMove();
    void GenerateBlock(int type);

protected:

    void fill_block();
    bool can_move_y();
    void check_score();

protected:
    int m_BlockSpeed;
    int m_BlockHeight;
    bool m_isBlockMove;
    
public:
    //connection
    //static LoginRequest m_loginReq;
    //static FLBattle m_battle;
};

#endif // __HELLOWORLD_SCENE_H__
