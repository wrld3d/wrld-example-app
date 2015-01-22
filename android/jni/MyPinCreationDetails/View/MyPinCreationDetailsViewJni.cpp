// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsViewJni.h"
#include "MyPinCreationDetailsView.h"

JNIEXPORT void JNICALL Java_com_eegeo_mypincreationdetails_MyPinCreationDetailsJniMethods_CloseButtonPressed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsView* pView = reinterpret_cast<ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsView*>(nativeObjectPtr);
    pView->OnDismissed();
}

JNIEXPORT void JNICALL Java_com_eegeo_mypincreationdetails_MyPinCreationDetailsJniMethods_SubmitButtonPressed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsView* pView = reinterpret_cast<ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsView*>(nativeObjectPtr);
    pView->OnConfirmed();
}

