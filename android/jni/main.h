// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef MAIN_H_
#define MAIN_H_

#include <jni.h>

extern "C"
{
	JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* pvt);

	JNIEXPORT long JNICALL Java_com_eegeo_NativeJniCalls_createNativeCode(JNIEnv* jenv, jobject obj, jobject activity, jobject assetManager, jfloat dpi);
	JNIEXPORT void JNICALL Java_com_eegeo_NativeJniCalls_destroyNativeCode(JNIEnv* jenv, jobject obj);
	JNIEXPORT void JNICALL Java_com_eegeo_NativeJniCalls_pauseNativeCode(JNIEnv* jenv, jobject obj);
	JNIEXPORT void JNICALL Java_com_eegeo_NativeJniCalls_resumeNativeCode(JNIEnv* jenv, jobject obj);
	JNIEXPORT void JNICALL Java_com_eegeo_NativeJniCalls_setNativeSurface(JNIEnv* jenv, jobject obj, jobject surface);
	JNIEXPORT void JNICALL Java_com_eegeo_NativeJniCalls_updateNativeCode(JNIEnv* jenv, jobject obj, jfloat deltaSeconds);

	//input
	JNIEXPORT void JNICALL Java_com_eegeo_EegeoSurfaceView_processNativePointerDown(JNIEnv* jenv, jobject obj,
	        jint primaryActionIndex,
	        jint primaryActionIdentifier,
	        jint numPointers,
	        jfloatArray x,
	        jfloatArray y,
	        jintArray pointerIdentity,
	        jintArray pointerIndex);

	JNIEXPORT void JNICALL Java_com_eegeo_EegeoSurfaceView_processNativePointerUp(JNIEnv* jenv, jobject obj,
	        jint primaryActionIndex,
	        jint primaryActionIdentifier,
	        jint numPointers,
	        jfloatArray x,
	        jfloatArray y,
	        jintArray pointerIdentity,
	        jintArray pointerIndex);

	JNIEXPORT void JNICALL Java_com_eegeo_EegeoSurfaceView_processNativePointerMove(JNIEnv* jenv, jobject obj,
	        jint primaryActionIndex,
	        jint primaryActionIdentifier,
	        jint numPointers,
	        jfloatArray x,
	        jfloatArray y,
	        jintArray pointerIdentity,
	        jintArray pointerIndex);
};

#endif /* MAIN_H_ */
