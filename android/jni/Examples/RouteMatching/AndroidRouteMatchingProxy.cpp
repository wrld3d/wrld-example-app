// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRouteMatchingProxy.h"
#include "AndroidRouteMatchingExampleView.h"

using namespace Examples;

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteMatchingExampleHud_ToggleRouteMatching(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::AndroidRouteMatchingExampleView* pExample = (Examples::AndroidRouteMatchingExampleView*)(nativeObjectPtr);

	pExample->ToggleMatching();
}


