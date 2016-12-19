// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_indooratlas_IndoorAtlasJniMethods_OnLocationChanged(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
		jdouble latitude,
		jdouble longitude);
}
