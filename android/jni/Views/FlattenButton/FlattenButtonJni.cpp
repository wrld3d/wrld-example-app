// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FlattenButtonJni.h"
#include "FlattenButtonViewController.h"

JNIEXPORT void JNICALL Java_com_eegeo_flattenbutton_FlattenButtonViewJniMethods_SetFlatten(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jboolean flattened)
{
	ExampleApp::FlattenButton::FlattenButtonViewController* pController = reinterpret_cast<ExampleApp::FlattenButton::FlattenButtonViewController*>(nativeObjectPtr);
	pController->SetFlattened(flattened);
}

