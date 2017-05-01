// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "MenuJni.h"
#include "MenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Menu::View::MenuView* pView = reinterpret_cast<ExampleApp::Menu::View::MenuView*>(nativeObjectPtr);
    pView->HandleViewClicked();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewOpenStarted(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Menu::View::MenuView* pView = reinterpret_cast<ExampleApp::Menu::View::MenuView*>(nativeObjectPtr);
    pView->HandleViewOpenStarted();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewOpenCompleted(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Menu::View::MenuView* pView = reinterpret_cast<ExampleApp::Menu::View::MenuView*>(nativeObjectPtr);
    pView->HandleViewOpenCompleted();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewCloseCompleted(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Menu::View::MenuView* pView = reinterpret_cast<ExampleApp::Menu::View::MenuView*>(nativeObjectPtr);
    pView->HandleViewCloseCompleted();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewDragStarted(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Menu::View::MenuView* pView = reinterpret_cast<ExampleApp::Menu::View::MenuView*>(nativeObjectPtr);
    pView->HandleDraggingViewStarted();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewDragInProgress(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jfloat normalisedDragState)
{
    ASSERT_UI_THREAD

    ExampleApp::Menu::View::MenuView* pView = reinterpret_cast<ExampleApp::Menu::View::MenuView*>(nativeObjectPtr);
    pView->HandleDraggingViewInProgress(normalisedDragState);
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewDragCompleted(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Menu::View::MenuView* pView = reinterpret_cast<ExampleApp::Menu::View::MenuView*>(nativeObjectPtr);
    pView->HandleDraggingViewCompleted();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_SelectedItem(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jint sectionIndex,
    jint itemIndex)
{
    ASSERT_UI_THREAD

    ExampleApp::Menu::View::MenuView* pView = reinterpret_cast<ExampleApp::Menu::View::MenuView*>(nativeObjectPtr);
    pView->HandleItemSelected(sectionIndex, itemIndex);
}

JNIEXPORT bool JNICALL Java_com_eegeo_menu_MenuViewJniMethods_TryBeginDrag(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::Menu::View::MenuView* pView = reinterpret_cast<ExampleApp::Menu::View::MenuView*>(nativeObjectPtr);
    return pView->CallBeginDrag();
}



