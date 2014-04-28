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

    } while (0);
  
    return true;
}


void FLGame::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
