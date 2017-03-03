// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <jni.h>
#include <string>

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

JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_SetInteriorIdFromMapKey(
		JNIEnv *jenv, jclass obj,
		jlong nativeObjectPtr,
		jstring mapKey)
{
	const char* chars = jenv->GetStringUTFChars(mapKey, 0);
	std::string mapKeyString = chars;
	jenv->ReleaseStringUTFChars(mapKey, chars);

	using ExampleApp::InteriorsPosition::View::SenionLab::SenionLabBroadcastReceiver;
	reinterpret_cast<SenionLabBroadcastReceiver *>(nativeObjectPtr)->SetInteriorIdFromMapKey(mapKeyString);
}

JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabBroadcastReceiverJniMethods_SetIsConnected(
        JNIEnv *jenv, jclass obj,
        jlong nativeObjectPtr,
        jboolean isConnected)
{
    using ExampleApp::InteriorsPosition::View::SenionLab::SenionLabBroadcastReceiver;
    reinterpret_cast<SenionLabBroadcastReceiver *>(nativeObjectPtr)->SetIsConnected(isConnected);
}
}
