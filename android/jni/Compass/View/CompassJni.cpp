// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassJni.h"
#include "CompassView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_compass_CompassViewJniMethods_HandleClick(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Compass::View::CompassView* pView = reinterpret_cast<ExampleApp::Compass::View::CompassView*>(nativeObjectPtr);
    pView->OnCycle();
}

