/*
 * AndroidRouteSimulationProxy.cpp
 */

#include "AndroidRouteSimulationProxy.h"
#include "AndroidRouteSimulationExampleView.h"
#include "RouteSimulationActionMessage.h"

using namespace Examples;

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleFollowCamera(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	pExample->SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::ToggleFollowCamera));
}


JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ChangeFollowDirection(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	pExample->SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::ToggleCameraDirection));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_IncreaseSpeedFollowed(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	pExample->SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::IncreaseSpeed));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_DecreaseSpeedFollowed(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	pExample->SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::DecreaseSpeed));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleDirectFollow(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	pExample->SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::ToggleRotateToFollow));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleSideOfRoadToDriveOn(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	pExample->SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::ChangeSideOfRoad));
}
