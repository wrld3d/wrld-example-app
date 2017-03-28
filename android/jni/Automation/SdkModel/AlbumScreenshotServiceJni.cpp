// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AndroidAppThreadAssertionMacros.h"
#include "AlbumScreenshotService.h"
#include "AlbumScreenshotServiceJni.h"

JNIEXPORT void JNICALL Java_com_eegeo_automation_AlbumScreenshotServiceJniMethods_AsyncSurfaceScreenshot(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jobject compositor)
{
    ASSERT_NATIVE_THREAD

    ExampleApp::Automation::SdkModel::AlbumScreenshotService* pScreenshotService = reinterpret_cast<ExampleApp::Automation::SdkModel::AlbumScreenshotService*>(nativeObjectPtr);
    pScreenshotService->AsyncSurfaceScreenshot(compositor);
}

