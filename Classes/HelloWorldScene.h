#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuChangeSceneCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(HelloWorld);
};

////////////////////////////////////////////////////////////////////////
//
//android方法回调
//
////////////////////////////////////////////////////////////////////////
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif
    JNIEXPORT void JNICALL Java_com_eju_jz_AppActivity_androidSayHello(JNIEnv *env, jobject thiz, jstring b, jint a)
    {
        auto ch1 = env->GetStringUTFChars(b, NULL);
        cocos2d::log("获得android回调数据(%d,%s)",(int)a,ch1);
        env->ReleaseStringUTFChars(b, ch1);
    }
#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////
//
//android方法回调
//
////////////////////////////////////////////////////////////////////////

#endif // __HELLOWORLD_SCENE_H__
