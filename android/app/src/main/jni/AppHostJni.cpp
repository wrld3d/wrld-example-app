// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppHostJni.h"
#include "AppHost.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_revealApplicationUi(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    AppHost* pAppHost = reinterpret_cast<AppHost*>(nativeObjectPtr);
    pAppHost->RevealUiFromUiThread();
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_handleApplicationUiCreatedOnNativeThread(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_NATIVE_THREAD

    AppHost* pAppHost = reinterpret_cast<AppHost*>(nativeObjectPtr);
    pAppHost->HandleApplicationUiCreatedOnNativeThread();
}
