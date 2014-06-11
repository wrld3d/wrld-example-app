/*
 * AndroidRouteMatchingProxy.h
 */

#ifndef ANDROIDROUTEMATCHINGPROXY_H_
#define ANDROIDROUTEMATCHINGPROXY_H_

#include "AndroidExampleProxy.h"
#include "AndroidRouteMatchingExampleView.h"
#include <jni.h>

namespace Examples
{
class AndroidRouteMatchingProxy : public AndroidExampleProxy
{
public:
	AndroidRouteMatchingProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue);

	void ToggleRouteMatching(Examples::AndroidRouteMatchingExampleView* pExample);
};
}

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteMatchingExampleHud_ToggleRouteMatching(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeCallerProxyPtr);
}

#endif /* ANDROIDROUTEMATCHINGPROXY_H_ */
