// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsJni.h"
#include "OptionsView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_options_OptionsViewJniMethods_CloseButtonSelected(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Options::View::OptionsView* pView = reinterpret_cast<ExampleApp::Options::View::OptionsView*>(nativeObjectPtr);
    pView->HandleCloseSelected();
}

JNIEXPORT void JNICALL Java_com_eegeo_options_OptionsViewJniMethods_OkButtonSelected(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Options::View::OptionsView* pView = reinterpret_cast<ExampleApp::Options::View::OptionsView*>(nativeObjectPtr);
    pView->HandleOkSelected();
}

JNIEXPORT void JNICALL Java_com_eegeo_options_OptionsViewJniMethods_StreamOverWifiToggled(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    
    ASSERT_UI_THREAD

    ExampleApp::Options::View::OptionsView* pView = reinterpret_cast<ExampleApp::Options::View::OptionsView*>(nativeObjectPtr);
    pView->HandleStreamOverWifiOnlySelectionStateChanged();
}

JNIEXPORT void JNICALL Java_com_eegeo_options_OptionsViewJniMethods_CachingEnabledToggled(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Options::View::OptionsView* pView = reinterpret_cast<ExampleApp::Options::View::OptionsView*>(nativeObjectPtr);
    pView->HandleCacheEnabledSelectionStateChanged();
}

JNIEXPORT void JNICALL Java_com_eegeo_options_OptionsViewJniMethods_ClearCacheToggled(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Options::View::OptionsView* pView = reinterpret_cast<ExampleApp::Options::View::OptionsView*>(nativeObjectPtr);
    pView->HandleClearCacheSelectionStateChanged();
}

JNIEXPORT void JNICALL Java_com_eegeo_options_OptionsViewJniMethods_ClearCacheTriggered(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Options::View::OptionsView* pView = reinterpret_cast<ExampleApp::Options::View::OptionsView*>(nativeObjectPtr);
    pView->HandleClearCacheTriggered();
}

JNIEXPORT void JNICALL Java_com_eegeo_options_OptionsViewJniMethods_PlayTutorialAgainToggled(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jboolean enableTutorials)
{
    ASSERT_UI_THREAD

    ExampleApp::Options::View::OptionsView* pView = reinterpret_cast<ExampleApp::Options::View::OptionsView*>(nativeObjectPtr);
    pView->HandleReplayTutorialsToggled(enableTutorials);
}

