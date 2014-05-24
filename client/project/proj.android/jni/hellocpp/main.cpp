#include "game/AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include "entity/FLPlayer.h"
#include "net/GameProtoHandler.h"
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
    //if(!s_jniInit)
    {
        JniMethodInfo minfo;
        bool ret = JniHelper::getStaticMethodInfo(minfo,"com.nilgame.fallingsky.HelloCpp","getInst","()Ljava/lang/Object;");
        if(ret)
        {
            s_thisz = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

            ret = JniHelper::getMethodInfo(s_weiboAuth,"com.nilgame.fallingsky.HelloCpp","doWeiboAuth","()V");
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
    //if(!s_jniInit)
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

void Java_com_nilgame_fallingsky_HelloCpp_OnWeiboAuth(JNIEnv*  env, jobject thiz,jstring uid , jstring token)
{
	const char *uidstr = env->GetStringUTFChars(uid, NULL);
	const char *tokenstr = env->GetStringUTFChars(token, NULL);

	FLPlayer::GetInstance().SetUid(uidstr);
	FLPlayer::GetInstance().SetWeiboToken(tokenstr);

	GameProtoHandler::GetInstance().DoLogin(uidstr, tokenstr);

	env->ReleaseStringUTFChars(uid, uidstr);
	env->ReleaseStringUTFChars(token, tokenstr);
}

}
