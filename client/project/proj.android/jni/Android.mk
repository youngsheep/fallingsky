LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../src/game/AppDelegate.cpp \
                   ../../../src/game/GameScene.cpp \
                   ../../../src/game/GameBlock.cpp \
                   ../../../src/game/PlayerInfoScene.cpp \
                   ../../../src/game/RegisterScene.cpp \
		   ../../../src/game/LoadingScene.cpp \
                   ../../../src/common/FLTextInput.cpp \
                   ../../../src/common/PomeloConnection.cpp \
                   ../../../src/common/ResMgr.cpp \
                   ../../../src/config/srcgen/testConfigHolder.cpp \
                   ../../../src/entity/FLBattle.cpp \
                   ../../../src/entity/FLPlayer.cpp \
                   ../../../src/net/BattleRequest.cpp \
                   ../../../src/net/GameProtoHandler.cpp \
                   ../../../src/net/LoginRequest.cpp \
                   ../../../src/net/pushEventHandler.cpp \
                   ../../../src/net/roleRequest.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../src/

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += pomelo_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,libpomelo)
