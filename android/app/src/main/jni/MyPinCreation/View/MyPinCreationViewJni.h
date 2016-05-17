// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_mypincreation_MyPinCreationJniMethods_StartButtonPressed(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_mypincreation_MyPinCreationJniMethods_ConfirmationCancelButtonPressed(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_mypincreation_MyPinCreationJniMethods_ConfirmationOkButtonPressed(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);
}

