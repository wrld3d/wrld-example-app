// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRouteMatchingProxy.h"
#include "AndroidRouteMatchingExampleView.h"
#include "ToggleRouteMatchingMessage.h"

using namespace Examples;

AndroidRouteMatchingProxy::AndroidRouteMatchingProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue)
	: AndroidExampleProxy(messageQueue)
{

}

void AndroidRouteMatchingProxy::ToggleRouteMatching(Examples::AndroidRouteMatchingExampleView* pExample)
{
	SendMessage(new Examples::ToggleRouteMatchingMessage(pExample));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteMatchingExampleHud_ToggleRouteMatching(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jlong nativeCallerProxyPtr)
{
	Examples::AndroidRouteMatchingExampleView* pExample = (Examples::AndroidRouteMatchingExampleView*)(nativeObjectPtr);
	Examples::AndroidRouteMatchingProxy* pProxy = (Examples::AndroidRouteMatchingProxy*)(nativeCallerProxyPtr);
	pProxy->ToggleRouteMatching(pExample);
}


