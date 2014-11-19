// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsViewJni.h"
#include "MyPinDetailsViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_mypindetails_MyPinDetailsJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ASSERT_UI_THREAD

	ExampleApp::MyPinDetails::MyPinDetailsViewController* pController = reinterpret_cast<ExampleApp::MyPinDetails::MyPinDetailsViewController*>(nativeObjectPtr);
	pController->HandleCloseButtonPressed();
}

