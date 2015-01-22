// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonJni.h"
#include "FlattenButtonView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_flattenbutton_FlattenButtonViewJniMethods_OnToggle(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jboolean flattened)
{
    ASSERT_UI_THREAD

    ExampleApp::FlattenButton::View::FlattenButtonView* pView = reinterpret_cast<ExampleApp::FlattenButton::View::FlattenButtonView*>(nativeObjectPtr);
    pView->OnToggle(flattened);
}

