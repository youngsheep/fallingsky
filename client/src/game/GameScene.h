#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameBlock.h"

class FLGame : public cocos2d::CCLayer
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
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(FLGame);

protected:
    void generate_block();
    void fill_block();

    bool can_move_x(bool left);
    bool can_move_y();

protected:
    int m_BlockSpeed;

    
};

#endif // __HELLOWORLD_SCENE_H__
