// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_search_yelp_AndroidYelpSearchQueryJni_SearchQueryComplete(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jboolean success,
        jstring result);

    JNIEXPORT void JNICALL Java_com_eegeo_search_yelp_AndroidYelpSearchQueryJni_BusinessQueryComplete(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jboolean success,
        jstring result);
}
