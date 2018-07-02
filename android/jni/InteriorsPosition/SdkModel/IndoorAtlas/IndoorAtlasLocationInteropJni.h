// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_indooratlas_IndoorAtlasLocationInteropJniMethods_UpdateLocation(
            JNIEnv *jenv, jclass jobj,
            jlong nativeObjectPtr,
            jdouble latitudeDegrees,
            jdouble longitudeDegrees,
            jdouble horizontalAccuracyInMeters,
            jstring indoorAtlasFloorId);

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_indooratlas_IndoorAtlasLocationInteropJniMethods_UpdateIsAuthorized(
            JNIEnv *jenv, jclass obj,
            jlong nativeObjectPtr,
            jboolean isAuthorized);

}
