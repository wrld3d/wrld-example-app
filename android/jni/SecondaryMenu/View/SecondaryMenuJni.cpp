// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SecondaryMenuJni.h"
#include "SecondaryMenuView.h"
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

    ExampleApp::SecondaryMenu::View::SecondaryMenuView* pView = reinterpret_cast<ExampleApp::SecondaryMenu::View::SecondaryMenuView*>(nativeObjectPtr);
    pView->OnSearch(queryString);
}
