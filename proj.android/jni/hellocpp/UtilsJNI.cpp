//
//  UtilsJNI.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-21.
//
//

#include "cocos2d.h"
#include "UtilsJNI.h"
#include "GameScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

#define CLASS_NAME	"com/ShaoGame/Bird/MyBird"

using namespace cocos2d;
extern "C"
{

	int JNI_getInt(const char *key, int defaultValue)
	{
		JniMethodInfo t;
		if(!JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getInt", "(Ljava/lang/String;I)I")){
			return 0;
		}

		jstring str = t.env->NewStringUTF(key);
		int v = defaultValue;
		int result = t.env->CallStaticIntMethod(t.classID, t.methodID, str, v);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);

		return result;
	}


	void JNI_setInt(const char *key, int value)
    {
    	JniMethodInfo t;
    	if (!JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setInt", "(Ljava/lang/String;I)V")) {
    		return;
    	}

    	jstring str = t.env->NewStringUTF(key);
    	int v = value;
    	t.env->CallStaticVoidMethod(t.classID, t.methodID, str, v);
    	t.env->DeleteLocalRef(str);
    	t.env->DeleteLocalRef(t.classID);
    }

    bool JNI_getBool(const char *key, bool defaultValue)
    {
    	JniMethodInfo t;
    	if(!JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getBool", "(Ljava/lang/String;Z)Z")){
    		return false;
    	}

    	jstring str = t.env->NewStringUTF(key);
    	bool v = defaultValue;
    	bool result = t.env->CallStaticBooleanMethod(t.classID, t.methodID, str, v);
    	t.env->DeleteLocalRef(str);
    	t.env->DeleteLocalRef(t.classID);

    	return result;
    }

    void JNI_setBool(const char *key, bool value)
    {
    	JniMethodInfo t;
    	if(!JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setBool", "(Ljava/lang/String;Z)V")){
    		return;
    	}

    	jstring str = t.env->NewStringUTF(key);
		bool v = value;
		t.env->CallStaticVoidMethod(t.classID, t.methodID, str, v);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);
    }

    void JNI_showAdsScreen()
    {
    	JniMethodInfo t;
		if(!JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showAdsScreen", "()V")){
			return;
		}
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
    }

    void JNI_closeAdsScreen()
	{
		JniMethodInfo t;
		if(!JniHelper::getStaticMethodInfo(t, CLASS_NAME, "closeAdsScreen", "()V")){
			return;
		}
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

    void JNI_sendToWX()
	{
		JniMethodInfo t;
		if(!JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sendToWX", "()V")){
			return;
		}
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

    void JNI_sendFeeMessage(int cost, int count)
	{
		JniMethodInfo t;
		if (!JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sendFeeMessage", "(II)V")) {
			return;
		}

		int v1 = cost;
		int v2 = count;
		t.env->CallStaticVoidMethod(t.classID, t.methodID, v1, v2);
		t.env->DeleteLocalRef(t.classID);
	}

    void Java_com_ShaoGame_Bird_MyBird_purchaseComplete(JNIEnv *env, jobject thiz, jboolean succ)
    {
    	bool status = (bool)succ;
    	GameScene::purchaseComplete(status);
    }
}
