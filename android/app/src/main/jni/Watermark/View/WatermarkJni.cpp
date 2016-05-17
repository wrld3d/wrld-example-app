// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkJni.h"
#include "WatermarkView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_watermark_WatermarkViewJniMethods_OnSelected(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Watermark::View::WatermarkView* pView = reinterpret_cast<ExampleApp::Watermark::View::WatermarkView*>(nativeObjectPtr);
    pView->OnSelected();
}

