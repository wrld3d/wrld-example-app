// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_poicreation_PoiCreationJniMethods_StartButtonPressed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_poicreation_PoiCreationJniMethods_ConfirmationCancelButtonPressed(
			JNIEnv* jenv, jobject obj,
		    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_poicreation_PoiCreationJniMethods_ConfirmationOkButtonPressed(
				JNIEnv* jenv, jobject obj,
			    jlong nativeObjectPtr);
}

