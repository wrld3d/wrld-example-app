// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IndoorAtlasLocationManagerJni.h"
#include "IndoorAtlasLocationManager.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_indooratlas_IndoorAtlasJniMethods_OnLocationChanged(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
		jdouble latitude,
		jdouble longitude)
{
    ASSERT_UI_THREAD

    ExampleApp::IndoorAtlas::View::IndoorAtlasLocationManager* pView = reinterpret_cast<ExampleApp::IndoorAtlas::View::IndoorAtlasLocationManager*>(nativeObjectPtr);
    pView->OnUpdateLocation(latitude, longitude);
}

