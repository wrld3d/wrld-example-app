// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_interiorsexplorer_InteriorsExplorerViewJniMethods_OnDismissedClicked(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_interiorsexplorer_InteriorsExplorerViewJniMethods_OnFloorSelected(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr,
			jint floor);

	JNIEXPORT void JNICALL Java_com_eegeo_interiorsexplorer_InteriorsExplorerViewJniMethods_OnFloorSelectionDragged(
				JNIEnv* jenv, jobject obj,
				jlong nativeObjectPtr,
				jfloat dragParameter);
}
