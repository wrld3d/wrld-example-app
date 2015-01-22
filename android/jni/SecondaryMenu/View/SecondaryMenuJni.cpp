// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SecondaryMenuJni.h"
#include "SecondaryMenuViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_secondarymenu_SecondaryMenuViewJniMethods_PerformSearchQuery(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jstring searchQuery)
{
	ASSERT_UI_THREAD

	const char* chars = jenv->GetStringUTFChars(searchQuery, 0);
	std::string queryString = chars;
	jenv->ReleaseStringUTFChars(searchQuery, chars);

	ExampleApp::SecondaryMenu::SecondaryMenuViewController* pController = reinterpret_cast<ExampleApp::SecondaryMenu::SecondaryMenuViewController*>(nativeObjectPtr);
	pController->HandleSearch(queryString);
}
