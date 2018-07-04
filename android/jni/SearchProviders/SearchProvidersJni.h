// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_search(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr,
            jstring searchQuery);

    JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_searchWithContext(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr,
            jstring searchQuery,
            jboolean clearPreviousResults,
            jboolean isTag,
            jstring tagText,
            jboolean tryInterior,
            jboolean usesLocation,
            jdouble latitude,
            jdouble longitude,
            jdouble altitude,
            jboolean usesRadius,
            jfloat radius);

    JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_cancel(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_cancelSuggestions(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_autocompleteSuggestions(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jstring searchQuery);

}
