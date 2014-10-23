// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "MenuJni.h"
#include "MenuViewController.h"

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewClicked(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	ExampleApp::Menu::MenuViewController* pController = reinterpret_cast<ExampleApp::Menu::MenuViewController*>(nativeObjectPtr);
	pController->HandleViewClicked();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewOpenCompleted(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ExampleApp::Menu::MenuViewController* pController = reinterpret_cast<ExampleApp::Menu::MenuViewController*>(nativeObjectPtr);
	pController->HandleViewOpenCompleted();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewCloseCompleted(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ExampleApp::Menu::MenuViewController* pController = reinterpret_cast<ExampleApp::Menu::MenuViewController*>(nativeObjectPtr);
	pController->HandleViewCloseCompleted();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewDragStarted(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ExampleApp::Menu::MenuViewController* pController = reinterpret_cast<ExampleApp::Menu::MenuViewController*>(nativeObjectPtr);
	pController->HandleDraggingViewStarted();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewDragInProgress(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jfloat normalisedDragState)
{
	ExampleApp::Menu::MenuViewController* pController = reinterpret_cast<ExampleApp::Menu::MenuViewController*>(nativeObjectPtr);
	pController->HandleDraggingViewInProgress(normalisedDragState);
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_ViewDragCompleted(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ExampleApp::Menu::MenuViewController* pController = reinterpret_cast<ExampleApp::Menu::MenuViewController*>(nativeObjectPtr);
	pController->HandleDraggingViewCompleted();
}

JNIEXPORT void JNICALL Java_com_eegeo_menu_MenuViewJniMethods_SelectedItem(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jstring selectedItem,
    jint index)
{
	const char* chars = jenv->GetStringUTFChars(selectedItem, 0);
	std::string selection = chars;
	jenv->ReleaseStringUTFChars(selectedItem, chars);

	ExampleApp::Menu::MenuViewController* pController = reinterpret_cast<ExampleApp::Menu::MenuViewController*>(nativeObjectPtr);
	pController->HandleItemSelected(selection, index);
}

JNIEXPORT bool JNICALL Java_com_eegeo_menu_MenuViewJniMethods_TryBeginDrag(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	ExampleApp::Menu::MenuViewController* pController = reinterpret_cast<ExampleApp::Menu::MenuViewController*>(nativeObjectPtr);
	return pController->TryBeginDrag();
}
