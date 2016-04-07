// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewJni.h"
#include "InteriorsExplorerView.h"
#include "AndroidAppThreadAssertionMacros.h"

	JNIEXPORT void JNICALL Java_com_eegeo_interiorsexplorer_InteriorsExplorerViewJniMethods_OnDismissedClicked(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr)
{
	ASSERT_UI_THREAD

	ExampleApp::InteriorsExplorer::View::InteriorsExplorerView* pView = reinterpret_cast<ExampleApp::InteriorsExplorer::View::InteriorsExplorerView*>(nativeObjectPtr);
	pView->Dismiss();
}

	JNIEXPORT void JNICALL Java_com_eegeo_interiorsexplorer_InteriorsExplorerViewJniMethods_OnFloorSelected(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr,
			jint floor)
{
	ASSERT_UI_THREAD

	ExampleApp::InteriorsExplorer::View::InteriorsExplorerView* pView = reinterpret_cast<ExampleApp::InteriorsExplorer::View::InteriorsExplorerView*>(nativeObjectPtr);
	pView->SelectFloor(floor);
}

JNIEXPORT void JNICALL Java_com_eegeo_interiorsexplorer_InteriorsExplorerViewJniMethods_OnFloorSelectionDragged(
				JNIEnv* jenv, jobject obj,
				jlong nativeObjectPtr,
				jfloat dragParameter)
{
	ASSERT_UI_THREAD

	ExampleApp::InteriorsExplorer::View::InteriorsExplorerView* pView = reinterpret_cast<ExampleApp::InteriorsExplorer::View::InteriorsExplorerView*>(nativeObjectPtr);
	pView->SetFloorSelectionDrag(dragParameter);
}
