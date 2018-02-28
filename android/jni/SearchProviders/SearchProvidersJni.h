// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_search(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr,
            jstring searchQuery);
}
