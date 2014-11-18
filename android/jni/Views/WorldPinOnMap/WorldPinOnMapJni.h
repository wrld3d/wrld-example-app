// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_worldpinonmapview_WorldPinOnMapViewJniMethods_HandleClick(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);
}
