// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiJni.h"
#include "SearchResultPoiViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_searchresultpoiview_SearchResultPoiViewJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ASSERT_UI_THREAD

	ExampleApp::SearchResultPoi::SearchResultPoiViewController* pController = reinterpret_cast<ExampleApp::SearchResultPoi::SearchResultPoiViewController*>(nativeObjectPtr);
	pController->HandleCloseButtonPressed();
}

