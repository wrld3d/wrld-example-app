// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinOnMapJni.h"
#include "WorldPinOnMapViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_worldpinonmapview_WorldPinOnMapViewJniMethods_HandleClick(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ASSERT_UI_THREAD

	ExampleApp::WorldPins::WorldPinOnMapViewController* pController = reinterpret_cast<ExampleApp::WorldPins::WorldPinOnMapViewController*>(nativeObjectPtr);
	pController->HandleWorldPinOnMapClicked();
}

