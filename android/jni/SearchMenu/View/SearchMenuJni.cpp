// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuJni.h"
#include "SearchMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchMenuViewJniMethods_SelectedItem(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jint itemIndex)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchMenu::View::SearchMenuView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchMenuView*>(nativeObjectPtr);
    pView->HandleSearchItemSelected(itemIndex);
}

JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchMenuViewJniMethods_PerformSearchQuery(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jstring searchQuery)
{
    ASSERT_UI_THREAD

    const char* chars = jenv->GetStringUTFChars(searchQuery, 0);
    std::string queryString = chars;
    jenv->ReleaseStringUTFChars(searchQuery, chars);

    ExampleApp::SearchMenu::View::SearchMenuView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchMenuView*>(nativeObjectPtr);
    pView->SearchPerformed(queryString);
}

JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchMenuViewJniMethods_OnSearchCleared(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchMenu::View::SearchMenuView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchMenuView*>(nativeObjectPtr);
    pView->OnSearchCleared();
}
