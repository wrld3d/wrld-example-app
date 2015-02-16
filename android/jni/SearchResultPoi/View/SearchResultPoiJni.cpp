// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiJni.h"
#include "SearchResultPoiView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_searchresultpoiview_SearchResultPoiViewJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchResultPoi::View::SearchResultPoiView* pView = reinterpret_cast<ExampleApp::SearchResultPoi::View::SearchResultPoiView*>(nativeObjectPtr);
    pView->HandleCloseClicked();
}

JNIEXPORT void JNICALL Java_com_eegeo_searchresultpoiview_SearchResultPoiViewJniMethods_TogglePinnedButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchResultPoi::View::SearchResultPoiView* pView = reinterpret_cast<ExampleApp::SearchResultPoi::View::SearchResultPoiView*>(nativeObjectPtr);
    pView->HandlePinToggleClicked();
}

