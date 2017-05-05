// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <jni.h>
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

JNIEXPORT void JNICALL Java_com_eegeo_searchresultpoiview_SearchResultPoiViewJniMethods_AvailabilityChanged(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
	jstring availability)
{
    ASSERT_UI_THREAD

	const char* chars = jenv->GetStringUTFChars(availability, 0);
	std::string availabilityString = chars;
	jenv->ReleaseStringUTFChars(availability, chars);

    ExampleApp::SearchResultPoi::View::SearchResultPoiView* pView = reinterpret_cast<ExampleApp::SearchResultPoi::View::SearchResultPoiView*>(nativeObjectPtr);
    pView->HandleAvailabilityChanged(availabilityString);
}

