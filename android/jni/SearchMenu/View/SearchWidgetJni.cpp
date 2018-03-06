// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchWidgetJni.h"
#include "SearchWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_OnSearchResultsCleared(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchMenu::View::SearchWidgetView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchWidgetView*>(nativeObjectPtr);
    pView->OnSearchResultsCleared();
}

JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_OnSearchResultSelected(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jint index)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchMenu::View::SearchWidgetView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchWidgetView*>(nativeObjectPtr);
    pView->OnSearchResultSelected((int)index);
}
