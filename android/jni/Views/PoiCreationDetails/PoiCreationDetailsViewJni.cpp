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
	    jlong nativeObjectPtr, jstring title, jstring description, jstring imagePath, jboolean shouldShare)
{
	const char* titlechars = jenv->GetStringUTFChars(title, 0);
	std::string titleString = titlechars;
	jenv->ReleaseStringUTFChars(title, titlechars);

	const char* descChars = jenv->GetStringUTFChars(description, 0);
	std::string descriptionString = descChars;
	jenv->ReleaseStringUTFChars(description, descChars);

	const char* imageChars = jenv->GetStringUTFChars(imagePath, 0);
	std::string imageString = imageChars;
	jenv->ReleaseStringUTFChars(imagePath, imageChars);

	ExampleApp::PoiCreationDetails::PoiCreationDetailsViewController* pController = reinterpret_cast<ExampleApp::PoiCreationDetails::PoiCreationDetailsViewController*>(nativeObjectPtr);
	pController->HandleConfirmButtonPressed(titleString, descriptionString, imageString, shouldShare);
}

