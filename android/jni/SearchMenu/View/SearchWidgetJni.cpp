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


JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_OnSearchResultNavigationRequest(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jint index)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchMenu::View::SearchWidgetView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchWidgetView*>(nativeObjectPtr);
    pView->OnNavigationRequest((int)index);
}

JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_OnSearchbarTextChanged(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jstring text)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchMenu::View::SearchWidgetView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchWidgetView*>(nativeObjectPtr);
    const char* chars = jenv->GetStringUTFChars(text, 0);
    std::string newText = chars;
    jenv->ReleaseStringUTFChars(text, chars);

    pView->OnSearchbarTextChanged(newText);
}


JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_SelectedItem(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jstring text,
        jint sectionIndex,
        jint itemIndex)
{
    ASSERT_UI_THREAD

    const char* chars = jenv->GetStringUTFChars(text, 0);
    std::string menuText = chars;
    jenv->ReleaseStringUTFChars(text, chars);

    ExampleApp::SearchMenu::View::SearchWidgetView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchWidgetView*>(nativeObjectPtr);
        pView->HandleItemSelected(menuText, sectionIndex, itemIndex);
}

JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_ViewPushesControlsOffscreen(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchMenu::View::SearchWidgetView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchWidgetView*>(nativeObjectPtr);
    pView->HandleViewOpenCompleted();
}

JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_ViewAllowsControlsOnscreen(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchMenu::View::SearchWidgetView* pView = reinterpret_cast<ExampleApp::SearchMenu::View::SearchWidgetView*>(nativeObjectPtr);
    pView->HandleViewCloseCompleted();
}