// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundViewJni.h"
#include "ModalBackgroundAggregateView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_modalbackground_ModalBackgroundViewJniMethods_HandleViewTapped(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::ModalBackground::View::ModalBackgroundAggregateView* pView = reinterpret_cast<ExampleApp::ModalBackground::View::ModalBackgroundAggregateView*>(nativeObjectPtr);
    pView->HandleViewTapped();
}
