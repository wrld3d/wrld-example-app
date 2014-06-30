// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ANDROIDROUTEMATCHINGPROXY_H_
#define ANDROIDROUTEMATCHINGPROXY_H_

#include "AndroidRouteMatchingExampleView.h"
#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_routematching_RouteMatchingJniMethods_ToggleRouteMatching(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);
}

#endif /* ANDROIDROUTEMATCHINGPROXY_H_ */
