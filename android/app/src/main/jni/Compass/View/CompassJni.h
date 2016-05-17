// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_compass_CompassViewJniMethods_HandleClick(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);
}

