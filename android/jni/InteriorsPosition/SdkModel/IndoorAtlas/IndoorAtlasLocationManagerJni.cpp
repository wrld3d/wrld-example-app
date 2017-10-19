// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <jni.h>

#include "AndroidAppThreadAssertionMacros.h"
#include "IndoorAtlasLocationManager.h"
#include "IndoorAtlasLocationManagerJni.h"

extern "C"
{
JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_indooratlas_IndoorAtlasLocationManagerJniMethods_DidUpdateLocation(
        JNIEnv *jenv, jclass jobj,
        jlong nativeObjectPtr,
        jdouble latitude,
        jdouble longitude,
        jstring floorId)
{
    std::string floorIdString = "";
    if(floorId != NULL)
    {
        const char *chars = jenv->GetStringUTFChars(floorId, 0);
        floorIdString = chars;
        jenv->ReleaseStringUTFChars(floorId, chars);
    }

    using ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationManager;
    reinterpret_cast<IndoorAtlasLocationManager *>(nativeObjectPtr)->DidUpdateLocation(latitude,
                                                                                       longitude,
                                                                                       floorIdString);
}

JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_indooratlas_IndoorAtlasLocationManagerJniMethods_SetIsAuthorized(
        JNIEnv *jenv, jclass obj,
        jlong nativeObjectPtr,
        jboolean isAuthorized)
{
    using ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationManager;
    reinterpret_cast<IndoorAtlasLocationManager *>(nativeObjectPtr)->SetIsAuthorized(isAuthorized);
}
}
