// Copyright eeGeo Ltd (2012-2017), All Rights Reserved
#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabLocationInteropJniMethods_UpdateIsAuthorized(
        JNIEnv *jenv,
        jclass clazz,
        jlong nativeObjectPtr,
        jboolean isAuthorized);

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabLocationInteropJniMethods_UpdateLocation(
            JNIEnv *jenv,
            jclass clazz,
            jlong nativeObjectPtr,
            jdouble latitudeDegrees,
            jdouble longitudeDegrees,
            jdouble horizontalAltitude,
            jint senionFloorNumber);

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabLocationInteropJniMethods_UpdateHeading(
            JNIEnv *jenv,
            jclass clazz,
            jlong nativeObjectPtr,
            jdouble headingInDegrees);
}
