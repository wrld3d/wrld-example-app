// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ANDROIDROUTESIMULATIONPROXY_H_
#define ANDROIDROUTESIMULATIONPROXY_H_

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleFollowCamera(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ChangeFollowDirection(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_IncreaseSpeedFollowed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_DecreaseSpeedFollowed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleDirectFollow(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleSideOfRoadToDriveOn(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);
}

#endif /* ANDROIDROUTESIMULATIONPROXY_H_ */
