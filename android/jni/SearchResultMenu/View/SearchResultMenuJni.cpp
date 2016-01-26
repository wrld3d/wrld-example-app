// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuJni.h"
#include "SearchResultMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_searchresultmenu_SearchResultMenuViewJniMethods_HandleClosed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchResultMenu::View::SearchMenuView* pView = reinterpret_cast<ExampleApp::SearchResultMenu::View::SearchMenuView*>(nativeObjectPtr);
    pView->HandleSearchClosed();
}

