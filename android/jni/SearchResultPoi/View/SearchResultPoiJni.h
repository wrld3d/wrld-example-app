// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_searchresultpoiview_SearchResultPoiViewJniMethods_CloseButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_searchresultpoiview_SearchResultPoiViewJniMethods_TogglePinnedButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);
}
