// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_poicreationdetails_PoiCreationDetailsJniMethods_CloseButtonPressed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_poicreationdetails_PoiCreationDetailsJniMethods_SubmitButtonPressed(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr);
}

