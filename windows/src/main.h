//// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
//
//#pragma once
//
//#include <jni.h>
//
//extern "C"
//{
//    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* pvt);
//
//    JNIEXPORT long JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_createNativeCode(
//    		JNIEnv* jenv, jobject obj,
//    		jobject activity,
//    		jobject assetManager,
//    		jfloat dpi,
//    		jint density);
//
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_destroyNativeCode(JNIEnv* jenv, jobject obj);
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_pauseNativeCode(JNIEnv* jenv, jobject obj);
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_resumeNativeCode(JNIEnv* jenv, jobject obj);
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_setNativeSurface(JNIEnv* jenv, jobject obj, jobject surface);
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_stopUpdatingNativeCode(JNIEnv* jenv, jobject obj);
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_updateNativeCode(JNIEnv* jenv, jobject obj, jfloat deltaSeconds);
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_updateUiViewCode(JNIEnv* jenv, jobject obj, jfloat deltaSeconds);
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_destroyApplicationUi(JNIEnv* jenv, jobject obj);
//
//    //input
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_EegeoSurfaceView_processNativePointerDown(JNIEnv* jenv, jobject obj,
//            jint primaryActionIndex,
//            jint primaryActionIdentifier,
//            jint numPointers,
//            jfloatArray x,
//            jfloatArray y,
//            jintArray pointerIdentity,
//            jintArray pointerIndex);
//
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_EegeoSurfaceView_processNativePointerUp(JNIEnv* jenv, jobject obj,
//            jint primaryActionIndex,
//            jint primaryActionIdentifier,
//            jint numPointers,
//            jfloatArray x,
//            jfloatArray y,
//            jintArray pointerIdentity,
//            jintArray pointerIndex);
//
//    JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_EegeoSurfaceView_processNativePointerMove(JNIEnv* jenv, jobject obj,
//            jint primaryActionIndex,
//            jint primaryActionIdentifier,
//            jint numPointers,
//            jfloatArray x,
//            jfloatArray y,
//            jintArray pointerIdentity,
//            jintArray pointerIndex);
//};
//
