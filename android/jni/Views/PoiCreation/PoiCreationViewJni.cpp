// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationViewJni.h"
#include "PoiCreationButtonViewController.h"
#include "PoiCreationConfirmationViewController.h"

JNIEXPORT void JNICALL Java_com_eegeo_poicreation_PoiCreationJniMethods_StartButtonPressed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr)
{
	ExampleApp::PoiCreation::PoiCreationButtonViewController* pController = reinterpret_cast<ExampleApp::PoiCreation::PoiCreationButtonViewController*>(nativeObjectPtr);
	pController->Selected();
}

JNIEXPORT void JNICALL Java_com_eegeo_poicreation_PoiCreationJniMethods_ConfirmationCancelButtonPressed(
			JNIEnv* jenv, jobject obj,
		    jlong nativeObjectPtr)
{
	ExampleApp::PoiCreation::PoiCreationConfirmationViewController* pController = reinterpret_cast<ExampleApp::PoiCreation::PoiCreationConfirmationViewController*>(nativeObjectPtr);
	pController->HandleCancelSelected();
}

JNIEXPORT void JNICALL Java_com_eegeo_poicreation_PoiCreationJniMethods_ConfirmationOkButtonPressed(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr)
{
	ExampleApp::PoiCreation::PoiCreationConfirmationViewController* pController = reinterpret_cast<ExampleApp::PoiCreation::PoiCreationConfirmationViewController*>(nativeObjectPtr);
	pController->HandleConfirmSelected();
}

