#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "net/GameProtoHandler.h"

USING_NS_CC;

void registerWeiboLogin()
{
    GameProtoHandler::GetInstance().DoLogin("1449516883","2.00ZYBGaBrInXhC5fd379312ddlQZkB");
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
