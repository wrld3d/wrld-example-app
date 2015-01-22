// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassJni.h"
#include "CompassViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_compass_CompassViewJniMethods_HandleClick(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ASSERT_UI_THREAD

	ExampleApp::Compass::CompassViewController* pController = reinterpret_cast<ExampleApp::Compass::CompassViewController*>(nativeObjectPtr);
	pController->HandleClick();
}

