// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationViewJni.h"
#include "MyPinCreationInitiationView.h"
#include "MyPinCreationConfirmationView.h"

JNIEXPORT void JNICALL Java_com_eegeo_mypincreation_MyPinCreationJniMethods_StartButtonPressed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ExampleApp::MyPinCreation::View::MyPinCreationInitiationView* pView = reinterpret_cast<ExampleApp::MyPinCreation::View::MyPinCreationInitiationView*>(nativeObjectPtr);
    pView->OnSelected();
}

JNIEXPORT void JNICALL Java_com_eegeo_mypincreation_MyPinCreationJniMethods_ConfirmationCancelButtonPressed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ExampleApp::MyPinCreation::View::MyPinCreationConfirmationView* pView = reinterpret_cast<ExampleApp::MyPinCreation::View::MyPinCreationConfirmationView*>(nativeObjectPtr);
    pView->OnDismissed();
}

JNIEXPORT void JNICALL Java_com_eegeo_mypincreation_MyPinCreationJniMethods_ConfirmationOkButtonPressed(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ExampleApp::MyPinCreation::View::MyPinCreationConfirmationView* pView = reinterpret_cast<ExampleApp::MyPinCreation::View::MyPinCreationConfirmationView*>(nativeObjectPtr);
    pView->OnConfirmed();
}

