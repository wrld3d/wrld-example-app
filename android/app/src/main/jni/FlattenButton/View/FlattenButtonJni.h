// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_flattenbutton_FlattenButtonViewJniMethods_OnToggle(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jboolean flattened);
}

