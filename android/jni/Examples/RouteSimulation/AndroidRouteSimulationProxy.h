/*
 * AndroidRouteSimulationProxy.h
 */

#ifndef ANDROIDROUTESIMULATIONPROXY_H_
#define ANDROIDROUTESIMULATIONPROXY_H_

#include "AndroidExampleProxy.h"
#include "AndroidRouteSimulationExampleView.h"
#include <jni.h>

namespace Examples
{
class AndroidRouteSimulationProxy : public AndroidExampleProxy
{
public:
	AndroidRouteSimulationProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue);

	void ToggleFollowCamera(Examples::AndroidRouteSimulationExampleView* pExample);
	void ChangeDirection(Examples::AndroidRouteSimulationExampleView* pExample);
	void IncreaseSpeed(Examples::AndroidRouteSimulationExampleView* pExample);
	void DecreaseSpeed(Examples::AndroidRouteSimulationExampleView* pExample);
	void ToggleFollowDirection(Examples::AndroidRouteSimulationExampleView* pExample);
	void ToggleSideOfRoad(Examples::AndroidRouteSimulationExampleView* pExample);
};
}

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleFollowCamera(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeObjectProxyPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ChangeFollowDirection(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeObjectProxyPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_IncreaseSpeedFollowed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeObjectProxyPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_DecreaseSpeedFollowed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeObjectProxyPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleDirectFollow(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeObjectProxyPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleSideOfRoadToDriveOn(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeObjectProxyPtr);
}

#endif /* ANDROIDROUTESIMULATIONPROXY_H_ */
