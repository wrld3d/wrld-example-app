/*
 * AndroidRouteMatchingProxy.h
 */

#ifndef ANDROIDROUTEMATCHINGPROXY_H_
#define ANDROIDROUTEMATCHINGPROXY_H_

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteMatchingExampleHud_ToggleRouteMatching(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);
}

#endif /* ANDROIDROUTEMATCHINGPROXY_H_ */
