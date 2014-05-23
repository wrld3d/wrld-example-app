/*
 * JavaHudCrossThreadCommunicationProxy.h
 */

#ifndef JAVAHUDCROSSTHREADCOMMUNICATIONPROXY_H_
#define JAVAHUDCROSSTHREADCOMMUNICATIONPROXY_H_

#include "AndroidExampleProxy.h"
#include "JavaHudCrossThreadCommunicationExample.h"
#include <jni.h>
#include <string>

namespace Examples
{
	class JavaHudCrossThreadCommunicationProxy : public AndroidExampleProxy
	{
	public:
		JavaHudCrossThreadCommunicationProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue);

		void SetCurrentTheme(Examples::JavaHudCrossThreadCommunicationExample* pExample, const std::string& name);

		void ReadCurrentThemeName(Examples::JavaHudCrossThreadCommunicationExample* pExample);
	};
}

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_setCurrentTheme(JNIEnv* jenv, jobject obj,
    		jlong nativeAppWindowPtr,
			jlong nativeCallerProxyPtr,
    		jstring name);

    JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_readCurrentThemeName(JNIEnv* jenv, jobject obj,
    		jlong nativeObjectPtr,
			jlong nativeCallerProxyPtr);
}

#endif /* JAVAHUDCROSSTHREADCOMMUNICATIONPROXY_H_ */
