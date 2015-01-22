// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationViewJni.h"
#include "MyPinCreationInitiationViewController.h"
#include "MyPinCreationConfirmationViewController.h"

JNIEXPORT void JNICALL Java_com_eegeo_mypincreation_MyPinCreationJniMethods_StartButtonPressed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr)
{
	ExampleApp::MyPinCreation::MyPinCreationInitiationViewController* pController = reinterpret_cast<ExampleApp::MyPinCreation::MyPinCreationInitiationViewController*>(nativeObjectPtr);
	pController->Selected();
}

JNIEXPORT void JNICALL Java_com_eegeo_mypincreation_MyPinCreationJniMethods_ConfirmationCancelButtonPressed(
			JNIEnv* jenv, jobject obj,
		    jlong nativeObjectPtr)
{
	ExampleApp::MyPinCreation::MyPinCreationConfirmationViewController* pController = reinterpret_cast<ExampleApp::MyPinCreation::MyPinCreationConfirmationViewController*>(nativeObjectPtr);
	pController->HandleCancelSelected();
}

JNIEXPORT void JNICALL Java_com_eegeo_mypincreation_MyPinCreationJniMethods_ConfirmationOkButtonPressed(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr)
{
	ExampleApp::MyPinCreation::MyPinCreationConfirmationViewController* pController = reinterpret_cast<ExampleApp::MyPinCreation::MyPinCreationConfirmationViewController*>(nativeObjectPtr);
	pController->HandleConfirmSelected();
}

