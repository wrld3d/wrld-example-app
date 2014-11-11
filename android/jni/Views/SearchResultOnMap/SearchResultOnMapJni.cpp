// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapJni.h"
#include "SearchResultOnMapViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_searchresultonmapview_SearchResultOnMapViewJniMethods_HandleClick(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ASSERT_UI_THREAD

	ExampleApp::SearchResultOnMap::SearchResultOnMapViewController* pController = reinterpret_cast<ExampleApp::SearchResultOnMap::SearchResultOnMapViewController*>(nativeObjectPtr);
	pController->HandleSearchResultOnMapClicked();
}

