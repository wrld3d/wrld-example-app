// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageJni.h"
#include "AboutPageViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_aboutpageview_AboutPageViewJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ASSERT_UI_THREAD

	ExampleApp::AboutPage::AboutPageViewController* pController = reinterpret_cast<ExampleApp::AboutPage::AboutPageViewController*>(nativeObjectPtr);
	pController->HandleCloseButtonPressed();
}

