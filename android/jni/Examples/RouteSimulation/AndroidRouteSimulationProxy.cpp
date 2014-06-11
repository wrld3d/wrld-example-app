/*
 * AndroidRouteSimulationProxy.cpp
 */

#include "AndroidRouteSimulationProxy.h"
#include "AndroidRouteSimulationExampleView.h"
#include "RouteSimulationActionMessage.h"

using namespace Examples;

AndroidRouteSimulationProxy::AndroidRouteSimulationProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue)
	: AndroidExampleProxy(messageQueue)
{

}

void AndroidRouteSimulationProxy::ToggleFollowCamera(Examples::AndroidRouteSimulationExampleView* pExample)
{
	SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::ToggleFollowCamera));
}

void AndroidRouteSimulationProxy::ChangeDirection(Examples::AndroidRouteSimulationExampleView* pExample)
{
	SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::ToggleCameraDirection));
}

void AndroidRouteSimulationProxy::IncreaseSpeed(Examples::AndroidRouteSimulationExampleView* pExample)
{
	SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::IncreaseSpeed));
}

void AndroidRouteSimulationProxy::DecreaseSpeed(Examples::AndroidRouteSimulationExampleView* pExample)
{
	SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::DecreaseSpeed));
}

void AndroidRouteSimulationProxy::ToggleFollowDirection(Examples::AndroidRouteSimulationExampleView* pExample)
{
	SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::ToggleRotateToFollow));
}

void AndroidRouteSimulationProxy::ToggleSideOfRoad(Examples::AndroidRouteSimulationExampleView* pExample)
{
	SendMessage(new RouteSimulationActionMessage(pExample, &AndroidRouteSimulationExampleView::ChangeSideOfRoad));
}


JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleFollowCamera(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jlong nativeObjectProxyPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	Examples::AndroidRouteSimulationProxy* pProxy = (Examples::AndroidRouteSimulationProxy*)(nativeObjectProxyPtr);

	pProxy->ToggleFollowCamera(pExample);
}


JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ChangeFollowDirection(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jlong nativeObjectProxyPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	Examples::AndroidRouteSimulationProxy* pProxy = (Examples::AndroidRouteSimulationProxy*)(nativeObjectProxyPtr);

	pProxy->ChangeDirection(pExample);
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_IncreaseSpeedFollowed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jlong nativeObjectProxyPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	Examples::AndroidRouteSimulationProxy* pProxy = (Examples::AndroidRouteSimulationProxy*)(nativeObjectProxyPtr);

	pProxy->IncreaseSpeed(pExample);
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_DecreaseSpeedFollowed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jlong nativeObjectProxyPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	Examples::AndroidRouteSimulationProxy* pProxy = (Examples::AndroidRouteSimulationProxy*)(nativeObjectProxyPtr);

	pProxy->DecreaseSpeed(pExample);
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleDirectFollow(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jlong nativeObjectProxyPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	Examples::AndroidRouteSimulationProxy* pProxy = (Examples::AndroidRouteSimulationProxy*)(nativeObjectProxyPtr);

	pProxy->ToggleFollowDirection(pExample);
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleSideOfRoadToDriveOn(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jlong nativeObjectProxyPtr)
{
	Examples::AndroidRouteSimulationExampleView* pExample = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	Examples::AndroidRouteSimulationProxy* pProxy = (Examples::AndroidRouteSimulationProxy*)(nativeObjectProxyPtr);

	pProxy->ToggleSideOfRoad(pExample);
}
