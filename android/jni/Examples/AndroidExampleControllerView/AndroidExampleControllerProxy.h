// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ANDROIDEXAMPLECONTROLLERPROXY_H_
#define ANDROIDEXAMPLECONTROLLERPROXY_H_

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_examplecontroller_ExampleControllerJniMethods_ActivatePrevious(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_examplecontroller_ExampleControllerJniMethods_ActivateNext(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_examplecontroller_ExampleControllerJniMethods_SelectExample(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jstring selectedExample);
}


#endif /* ANDROIDEXAMPLECONTROLLERPROXY_H_ */
