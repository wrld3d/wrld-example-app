// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_automation_AlbumScreenshotServiceJniMethods_AsyncSurfaceScreenshot(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jobject compositor);
}

