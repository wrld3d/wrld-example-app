// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "SenionLabBroadcastReceiverJni.h"
#include "SenionLabBroadcastReceiver.h"

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_DidUpdateLocation(
            JNIEnv *jenv,
            jclass jobj,
            jlong nativeObjectPtr,
            jdouble latitudeInDegrees,
            jdouble longitudeInDegrees,
            jdouble horizontalAccuracyInMeters,
            jint senionFloorNumber)
    {
        using ExampleApp::InteriorsPosition::View::SenionLab::SenionLabBroadcastReceiver;

        auto* pBroadcastReceiver = reinterpret_cast<SenionLabBroadcastReceiver*>(nativeObjectPtr);

        pBroadcastReceiver->DidUpdateLocation(
                latitudeInDegrees, longitudeInDegrees, horizontalAccuracyInMeters, senionFloorNumber);
    }

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_SetIsAuthorized(
            JNIEnv *jenv,
            jclass obj,
            jlong nativeObjectPtr,
            jboolean isAuthorized)
    {
        using ExampleApp::InteriorsPosition::View::SenionLab::SenionLabBroadcastReceiver;
        reinterpret_cast<SenionLabBroadcastReceiver *>(nativeObjectPtr)->SetIsAuthorized(isAuthorized);
    }
}
