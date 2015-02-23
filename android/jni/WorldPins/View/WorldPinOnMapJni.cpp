// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapJni.h"
#include "WorldPinOnMapView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_worldpinonmapview_WorldPinOnMapViewJniMethods_HandleClick(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::WorldPins::View::WorldPinOnMapView* pView = reinterpret_cast<ExampleApp::WorldPins::View::WorldPinOnMapView*>(nativeObjectPtr);
    pView->OnSelected();
}

