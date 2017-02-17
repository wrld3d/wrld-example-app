// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <jni.h>

#include "AndroidAppThreadAssertionMacros.h"
#include "SenionLabBroadcastReceiver.h"
#include "SenionLabBroadcastReceiverJni.h"

extern "C"
{
JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_DidUpdateLocation(
        JNIEnv *jenv, jclass jobj,
        jlong nativeObjectPtr,
        jdouble latitude,
        jdouble longitude,
        jint floorNumber)
{
    using ExampleApp::InteriorsPosition::View::SenionLab::SenionLabBroadcastReceiver;
    reinterpret_cast<SenionLabBroadcastReceiver *>(nativeObjectPtr)->DidUpdateLocation(latitude,
                                                                                     longitude,
                                                                                     floorNumber);
}

JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_SetIsAuthorized(
        JNIEnv *jenv, jclass obj,
        jlong nativeObjectPtr,
        jboolean isAuthorized)
{
    using ExampleApp::InteriorsPosition::View::SenionLab::SenionLabBroadcastReceiver;
    reinterpret_cast<SenionLabBroadcastReceiver *>(nativeObjectPtr)->SetIsAuthorized(isAuthorized);
}
}
