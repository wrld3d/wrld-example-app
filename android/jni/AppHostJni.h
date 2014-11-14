// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_mobileexampleapp_NativeJniCalls_revealApplicationUi(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_mobileexampleapp_NativeJniCalls_handleApplicationUiCreatedOnNativeThread(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);
}
