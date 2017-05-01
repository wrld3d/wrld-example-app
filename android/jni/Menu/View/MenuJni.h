// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewOpenCompleted(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewOpenStarted(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewCloseCompleted(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewDragStarted(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewDragInProgress(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jfloat normalisedDragState);

    JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewDragCompleted(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_SelectedItem(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jint sectionIndex,
        jint itemIndex);

    JNIEXPORT bool JNICALL Java_com_eegeo_menu_MenuViewJniMethods_TryBeginDrag(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);
}


