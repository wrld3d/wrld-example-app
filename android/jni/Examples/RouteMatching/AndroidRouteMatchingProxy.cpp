/*
 * AndroidRouteMatchingProxy.cpp
 */

#include "AndroidRouteMatchingProxy.h"
#include "AndroidRouteMatchingExampleView.h"
#include "ToggleRouteMatchingMessage.h"

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteMatchingExampleHud_ToggleRouteMatching(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteMatchingExampleView* pExample = (Examples::AndroidRouteMatchingExampleView*)(nativeObjectPtr);
	pExample->SendMessage(new Examples::ToggleRouteMatchingMessage(pExample));
}


