// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationDetailsViewJni.h"
#include "PoiCreationDetailsViewController.h"

JNIEXPORT void JNICALL Java_com_eegeo_poicreationdetails_PoiCreationDetailsJniMethods_CloseButtonPressed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr)
{
	ExampleApp::PoiCreationDetails::PoiCreationDetailsViewController* pController = reinterpret_cast<ExampleApp::PoiCreationDetails::PoiCreationDetailsViewController*>(nativeObjectPtr);
	pController->HandleCloseButtonPressed();
}

JNIEXPORT void JNICALL Java_com_eegeo_poicreationdetails_PoiCreationDetailsJniMethods_SubmitButtonPressed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr)
{
	//ExampleApp::PoiCreationDetails::PoiCreationDetailsViewController* pController = reinterpret_cast<ExampleApp::PoiCreationDetails::PoiCreationDetailsViewController*>(nativeObjectPtr);
	//pController->HandleConfirmButtonPressed(title, desc, image, shouldShare);
}

