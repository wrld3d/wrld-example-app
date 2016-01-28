// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_modalbackground_ModalBackgroundViewJniMethods_HandleViewTapped(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr);
}
