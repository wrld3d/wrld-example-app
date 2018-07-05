// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_CloseButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SelectStartLocationClicked(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SelectEndLocationClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_StartLocationClearButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_EndLocationClearButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_StartEndLocationsSwapped(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_StartEndButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SelectedDirectionIndexChanged(
        JNIEnv *jenv, jobject obj,
        jlong nativeObjectPtr,
        jint directionIndex);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetBottomViewHeight(
        JNIEnv *jenv, jobject obj,
        jlong nativeObjectPtr,
        jint bottomViewHeight);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetTopViewHeight(
            JNIEnv *jenv, jobject obj,
            jlong nativeObjectPtr,
            jint topViewHeight);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_RerouteDialogClosed(
            JNIEnv *jenv, jobject obj,
            jlong nativeObjectPtr,
            jboolean shouldReroute);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetNavigationStartPointFromSuggestion(
            JNIEnv *jenv, jobject obj,
            jlong nativeObjectPtr,
            jint searchResultIndex);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetNavigationEndPointFromSuggestion(
            JNIEnv *jenv, jobject obj,
            jlong nativeObjectPtr,
            jint searchResultIndex);

    JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetSearchingForLocation(
            JNIEnv *jenv, jobject obj,
            jlong nativeObjectPtr,
            jboolean isSearching,
            jboolean isStartLocation
    );
}
