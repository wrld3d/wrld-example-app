// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchMenuViewJniMethods_HandleClosed(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr
    );

    JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchMenuViewJniMethods_SelectedItem(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr,
            jint itemIndex);
}


