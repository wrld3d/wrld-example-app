// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_OnSearchResultsCleared(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr
        );

    JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_OnSearchResultSelected(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr,
            jint index
        );

    JNIEXPORT void JNICALL Java_com_eegeo_searchmenu_SearchWidgetViewJniMethods_SelectedItem(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr,
            jint sectionIndex,
            jint itemIndex
        );
}
