// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsViewJni.h"
#include "MyPinCreationDetailsViewController.h"

JNIEXPORT void JNICALL Java_com_eegeo_mypincreationdetails_MyPinCreationDetailsJniMethods_CloseButtonPressed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr)
{
	ExampleApp::MyPinCreationDetails::MyPinCreationDetailsViewController* pController = reinterpret_cast<ExampleApp::MyPinCreationDetails::MyPinCreationDetailsViewController*>(nativeObjectPtr);
	pController->HandleCloseButtonPressed();
}

JNIEXPORT void JNICALL Java_com_eegeo_mypincreationdetails_MyPinCreationDetailsJniMethods_SubmitButtonPressed(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr, jstring title, jstring description, jstring imagePath, jbyteArray imageData, jboolean shouldShare)
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

	jbyte* pBuffer = jenv->GetByteArrayElements(imageData, NULL);

	Byte* imageDataBytes = reinterpret_cast<Byte *>(pBuffer);
	size_t imageSize = std::size_t(jenv->GetArrayLength(imageData));

	ExampleApp::MyPinCreationDetails::MyPinCreationDetailsViewController* pController = reinterpret_cast<ExampleApp::MyPinCreationDetails::MyPinCreationDetailsViewController*>(nativeObjectPtr);
	pController->HandleConfirmButtonPressed(titleString, descriptionString, imageString, imageDataBytes, imageSize, shouldShare);

	jenv->ReleaseByteArrayElements(imageData, pBuffer, 0);

}

