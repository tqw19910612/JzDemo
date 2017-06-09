//
//  MyTool.cpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#include "MyTool.hpp"


USING_NS_CC;

MyTool::MyTool()
{
    
}

MyTool::~MyTool()
{
    
}

MyTool* MyTool::m_pInstance = NULL;
MyTool* MyTool::getInstance()
{
    if (m_pInstance == NULL) {
        m_pInstance = new MyTool();
    }
    return m_pInstance;
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
    JNIEXPORT void JNICALL Java_com_eju_cy_jz_AppActivity_androidSayHello(JNIEnv *env, jobject thiz, jstring b, jint a)
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
