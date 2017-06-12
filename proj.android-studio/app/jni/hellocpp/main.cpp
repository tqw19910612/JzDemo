#include <memory>

#include <android/log.h>
#include <jni.h>

#include "AppDelegate.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

namespace {
std::unique_ptr<AppDelegate> appDelegate;
}

void cocos_android_app_init(JNIEnv* env) {
    LOGD("cocos_android_app_init");
    appDelegate.reset(new AppDelegate());
}

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
JNIEXPORT void JNICALL Java_com_eju_cy_jz_app_AppActivity_androidSayHello(JNIEnv *env, jobject thiz, jstring b, jint a)
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

