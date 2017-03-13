// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_indooratlas_IndoorAtlasLocationManagerJniMethods_DidUpdateLocation(
            JNIEnv *jenv, jclass clazz,
            jlong nativeObjectPtr,
            jdouble latitude,
            jdouble longitude,
            jstring floorId);

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_indooratlas_IndoorAtlasLocationManagerJniMethods_SetIsAuthorized(
            JNIEnv *jenv, jclass clazz,
            jlong nativeObjectPtr,
            jboolean isAuthorized);
}
