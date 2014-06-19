// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRouteSimulationProxy.h"
#include "AndroidRouteSimulationExampleView.h"

using namespace Examples;

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleFollowCamera(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);

	pExample->ToggleFollowCamera();
}


JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ChangeFollowDirection(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);

	pExample->ToggleCameraDirection();
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_IncreaseSpeedFollowed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);

	pExample->IncreaseSpeed();
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_DecreaseSpeedFollowed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);

	pExample->DecreaseSpeed();
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleDirectFollow(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);

	pExample->ToggleRotateToFollow();
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleSideOfRoadToDriveOn(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);

	pExample->ChangeSideOfRoad();
}
