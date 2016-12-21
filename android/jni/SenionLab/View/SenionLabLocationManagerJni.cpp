// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SenionLabLocationManager.h"
#include "SenionLabLocationManagerJni.h"

// Senion JNI CAll
    JNIEXPORT void JNICALL Java_com_eegeo_senion_SenionLabLocationJniMethods_OnLocationChanged(JNIEnv* jenv, jobject obj, jlong nativeCallerPointer, jdouble latitude, jdouble longitude, jstring floorNo)
    {
    	ExampleApp::SenionLab::View::SenionLabLocationManager* pManager = reinterpret_cast<ExampleApp::SenionLab::View::SenionLabLocationManager*>(nativeCallerPointer);
    	const char* floorIndex = jenv->GetStringUTFChars(floorNo, JNI_FALSE);
    	pManager->OnUpdateLocation(latitude,longitude,floorIndex);
    	jenv->ReleaseStringUTFChars(floorNo, floorIndex);
    }
