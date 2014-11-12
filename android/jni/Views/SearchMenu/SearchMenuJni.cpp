// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchMenuJni.h"
#include "SearchMenuViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchMenuViewJniMethods_HandleClosed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ASSERT_UI_THREAD

	ExampleApp::SearchMenu::SearchMenuViewController* pController = reinterpret_cast<ExampleApp::SearchMenu::SearchMenuViewController*>(nativeObjectPtr);
	pController->HandleClosed();
}

