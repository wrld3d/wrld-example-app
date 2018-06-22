// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "IndoorAtlasLocationInteropJni.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "IndoorAtlasLocationInterop.h"

#include <jni.h>

extern "C"
{
JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_indooratlas_IndoorAtlasLocationManagerJniMethods_UpdateLocation(
        JNIEnv *jenv, jclass jobj,
        jlong nativeObjectPtr,
        jdouble latitudeDegrees,
        jdouble longitudeDegrees,
        jdouble horizontalAccuracyInMeters,
        jstring indoorAtlasFloorId)
{
    std::string floorIdString = "";
    if(indoorAtlasFloorId != NULL)
    {
        const char *chars = jenv->GetStringUTFChars(indoorAtlasFloorId, 0);
        floorIdString = chars;
        jenv->ReleaseStringUTFChars(indoorAtlasFloorId, chars);
    }

    using ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationInterop;
    reinterpret_cast<IndoorAtlasLocationInterop *>(nativeObjectPtr)->DidUpdateLocation(
            latitudeDegrees,
            longitudeDegrees,
            horizontalAccuracyInMeters,
            floorIdString);
}

JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_indooratlas_IndoorAtlasLocationManagerJniMethods_UpdateIsAuthorized(
        JNIEnv *jenv, jclass obj,
        jlong nativeObjectPtr,
        jboolean isAuthorized)
{
    using ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationInterop;
    reinterpret_cast<IndoorAtlasLocationInterop *>(nativeObjectPtr)->SetIsAuthorized(isAuthorized);
}
}
