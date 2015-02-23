// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsJni.h"
#include "InitialExperienceDialogsView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_initialexperience_dialogs_InitialExperienceDialogsJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::InitialExperience::Dialogs::View::InitialExperienceDialogsView* pView = reinterpret_cast<ExampleApp::InitialExperience::Dialogs::View::InitialExperienceDialogsView*>(nativeObjectPtr);
    pView->CloseButtonTapped();
}

