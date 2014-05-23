#include "game/AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

static JniMethodInfo s_weiboAuth;
static jobject s_thisz;
static bool s_jniInit = false;

void InitJni()
{
    if(!s_jniInit)
    {
        JniMethodInfo minfo;
        bool ret = JniHelper::getStaticMethodInfo(minfo,"org.cocos2dx.hellocpp.HelloCpp","getInst","()Ljava/lang/Object;");
        if(ret)
        {
            s_thisz = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

            ret = JniHelper::getMethodInfo(s_weiboAuth,"org.cocos2dx.hellocpp.HelloCpp","doWeiboAuth","()V");
            if(ret)
            {
                CCLog("success init jni");
            }
        }

        s_jniInit = true;

    }
}

void registerWeiboLogin()
{
    //GameProtoHandler::GetInstance().DoLogin("1449516883","2.00ZYBGaBrInXhC5fd379312ddlQZkB");
    if(!s_jniInit)
    {
        InitJni();
    }

    s_weiboAuth.env->CallVoidMethod(s_thisz,s_weiboAuth.methodID);
}

extern "C"
{
    
jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        ccGLInvalidateStateCache();
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        ccDrawInit();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

}
