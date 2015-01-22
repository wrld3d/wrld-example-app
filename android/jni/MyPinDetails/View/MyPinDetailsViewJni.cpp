// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewJni.h"
#include "MyPinDetailsView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_mypindetails_MyPinDetailsJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::MyPinDetails::View::MyPinDetailsView* pView = reinterpret_cast<ExampleApp::MyPinDetails::View::MyPinDetailsView*>(nativeObjectPtr);
    pView->OnDismiss();
}

JNIEXPORT void JNICALL Java_com_eegeo_mypindetails_MyPinDetailsJniMethods_RemovePinButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::MyPinDetails::View::MyPinDetailsView* pView = reinterpret_cast<ExampleApp::MyPinDetails::View::MyPinDetailsView*>(nativeObjectPtr);
    pView->OnRemove();
}

