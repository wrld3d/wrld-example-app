// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_mypincreationdetails_MyPinCreationDetailsJniMethods_CloseButtonPressed(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_mypincreationdetails_MyPinCreationDetailsJniMethods_SubmitButtonPressed(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);
}

