// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_senion_SenionLabLocationJniMethods_OnLocationChanged(JNIEnv* jenv, jobject obj, jlong nativeCallerPointer, jdouble latitude, jdouble longitude, jstring floorNo);
}
