// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ANDROIDEXAMPLECONTROLLERPROXY_H_
#define ANDROIDEXAMPLECONTROLLERPROXY_H_

#include "AndroidExampleProxy.h"
#include "AndroidExampleControllerView.h"
#include <jni.h>
#include <string>

namespace Examples
{
class AndroidExampleControllerProxy : public AndroidExampleProxy
{
public:
	AndroidExampleControllerProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue);

	void ActivatePrevious(Examples::AndroidExampleControllerView* pExample);

	void ActivateNext(Examples::AndroidExampleControllerView* pExample);

	void SelectExample(Examples::AndroidExampleControllerView* pExample, const std::string& selectedExample);
};
}

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_ExampleControllerHud_ActivatePrevious(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeCallerProxyPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_ExampleControllerHud_ActivateNext(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeCallerProxyPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_ExampleControllerHud_SelectExample(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr,
	    jlong nativeCallerProxyPtr,
	    jstring selectedExample);
}


#endif /* ANDROIDEXAMPLECONTROLLERPROXY_H_ */
