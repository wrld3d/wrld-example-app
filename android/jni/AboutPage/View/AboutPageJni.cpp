// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageJni.h"
#include "AboutPageView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_aboutpageview_AboutPageViewJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::AboutPage::View::AboutPageView* pView = reinterpret_cast<ExampleApp::AboutPage::View::AboutPageView*>(nativeObjectPtr);
    pView->CloseTapped();
}

JNIEXPORT void JNICALL Java_com_eegeo_aboutpageview_AboutPageViewJniMethods_LogoLongPress(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::AboutPage::View::AboutPageView* pView = reinterpret_cast<ExampleApp::AboutPage::View::AboutPageView*>(nativeObjectPtr);
    pView->ShowHiddenText();
}
