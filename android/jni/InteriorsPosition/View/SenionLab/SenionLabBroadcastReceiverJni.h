// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_DidUpdateLocation(
            JNIEnv *jenv, jclass clazz,
            jlong nativeObjectPtr,
            jdouble latitude,
            jdouble longitude,
            jint floorNumber);

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_SetIsAuthorized(
            JNIEnv *jenv, jclass clazz,
            jlong nativeObjectPtr,
            jboolean isAuthorized);

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_SetInteriorIdFromMapKey(
            JNIEnv *jenv, jclass clazz,
            jlong nativeObjectPtr,
            jstring mapKey);

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_SetIsConnected(
            JNIEnv *jenv, jclass clazz,
            jlong nativeObjectPtr,
            jboolean isConnected);
}
