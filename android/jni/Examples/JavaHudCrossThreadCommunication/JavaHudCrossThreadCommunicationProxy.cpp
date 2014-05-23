/*
 * JavaHudCrossThreadCommunicationProxy.cpp
 *
 *  Created on: May 23, 2014
 *      Author: kimbleoperations
 */

#include "JavaHudCrossThreadCommunicationProxy.h"
#include "JavaHudCrossThreadCommunicationExample.h"
#include "ToggleRouteMatchingMessage.h"
#include "UpdateCurrentThemeMessage.h"
#include "RequestCurrentThemeNameMessage.h"

using namespace Examples;

JavaHudCrossThreadCommunicationProxy::JavaHudCrossThreadCommunicationProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue)
: AndroidExampleProxy(messageQueue)
{

}

void JavaHudCrossThreadCommunicationProxy::SetCurrentTheme(
		Examples::JavaHudCrossThreadCommunicationExample* pExample,
		const std::string& name)
{
	SendMessage(new Examples::UpdateCurrentThemeMessage(pExample, name));
}

void JavaHudCrossThreadCommunicationProxy::ReadCurrentThemeName(
		Examples::JavaHudCrossThreadCommunicationExample* pExample)
{
	SendMessage(new Examples::RequestCurrentThemeNameMessage(pExample));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_setCurrentTheme(JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr,
		jlong nativeCallerProxyPtr,
		jstring name)
{
	//extract the string from java via the JNI
	const char* chars = jenv->GetStringUTFChars(name, 0);
	std::string nameString = chars;
	jenv->ReleaseStringUTFChars(name, chars);

	//create a an item to set the theme and post it to our thread safe queue for deferred execution on native main thread
	Examples::JavaHudCrossThreadCommunicationExample* pExample = (Examples::JavaHudCrossThreadCommunicationExample*)(nativeObjectPtr);
	Examples::JavaHudCrossThreadCommunicationProxy* pProxy = (Examples::JavaHudCrossThreadCommunicationProxy*)(nativeCallerProxyPtr);

	pProxy->SetCurrentTheme(pExample, nameString);
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_readCurrentThemeName(JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr,
		jlong nativeCallerProxyPtr)
{
	//create a an item to read the theme and post it to our thread safe queue for deferred execution on native main thread
	Examples::JavaHudCrossThreadCommunicationExample* pExample = (Examples::JavaHudCrossThreadCommunicationExample*)(nativeObjectPtr);
	Examples::JavaHudCrossThreadCommunicationProxy* pProxy = (Examples::JavaHudCrossThreadCommunicationProxy*)(nativeCallerProxyPtr);

	pProxy->ReadCurrentThemeName(pExample);
}
