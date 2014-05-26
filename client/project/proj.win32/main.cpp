#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "net/GameProtoHandler.h"
#include "entity/FLPlayer.h"

USING_NS_CC;

void registerWeiboLogin()
{
    FLPlayer& player = FLPlayer::GetInstance();
    player.SetUid("1449516883");
    player.SetWeiboToken("2.00ZYBGaBrInXhC5fd379312ddlQZkB");
    GameProtoHandler::GetInstance().ConnectGameSvr("198.199.100.95", 3010);
    GameProtoHandler::GetInstance().DoLogin(player.GetUid(),player.GetWeiboToken());
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("HelloCpp");
    eglView->setFrameSize(960, 640);
    return CCApplication::sharedApplication()->run();
}
