// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassJni.h"
#include "CompassViewController.h"

JNIEXPORT void JNICALL Java_com_eegeo_compass_CompassViewJniMethods_HandleClick(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ExampleApp::Compass::CompassViewController* pController = reinterpret_cast<ExampleApp::Compass::CompassViewController*>(nativeObjectPtr);
	pController->HandleClick();
}

