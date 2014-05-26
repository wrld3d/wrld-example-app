/*
 * AndroidExampleControllerProxy.cpp
 */

#include "AndroidExampleControllerProxy.h"
#include "AndroidExampleControllerView.h"
#include "ActivatePreviousExampleMessage.h"
#include "ActivateNextExampleMessage.h"
#include "SelectExampleMessage.h"

using namespace Examples;

AndroidExampleControllerProxy::AndroidExampleControllerProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue)
: AndroidExampleProxy(messageQueue)
{

}

void AndroidExampleControllerProxy::ActivatePrevious(Examples::AndroidExampleControllerView* pExample)
{
	SendMessage(new Examples::ActivatePreviousExampleMessage(pExample));
}

void AndroidExampleControllerProxy::ActivateNext(Examples::AndroidExampleControllerView* pExample)
{
	SendMessage(new Examples::ActivateNextExampleMessage(pExample));
}

void AndroidExampleControllerProxy::SelectExample(Examples::AndroidExampleControllerView* pExample, const std::string& selectedExample)
{
	SendMessage(new Examples::SelectExampleMessage(pExample, selectedExample));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_ExampleControllerHud_ActivatePrevious(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr,
		jlong nativeCallerProxyPtr)
{
	Examples::AndroidExampleControllerView* pExample = (Examples::AndroidExampleControllerView*)(nativeObjectPtr);
	Examples::AndroidExampleControllerProxy* pProxy = (Examples::AndroidExampleControllerProxy*)(nativeCallerProxyPtr);
	pProxy->ActivatePrevious(pExample);
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_ExampleControllerHud_ActivateNext(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr,
		jlong nativeCallerProxyPtr)
{
	Examples::AndroidExampleControllerView* pExample = (Examples::AndroidExampleControllerView*)(nativeObjectPtr);
	Examples::AndroidExampleControllerProxy* pProxy = (Examples::AndroidExampleControllerProxy*)(nativeCallerProxyPtr);
	pProxy->ActivateNext(pExample);
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_ExampleControllerHud_SelectExample(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr,
		jlong nativeCallerProxyPtr,
		jstring selectedExample)
{

	//extract the string from java via the JNI
	const char* chars = jenv->GetStringUTFChars(selectedExample, 0);
	std::string nameString = chars;
	jenv->ReleaseStringUTFChars(selectedExample, chars);

	Examples::AndroidExampleControllerView* pExample = (Examples::AndroidExampleControllerView*)(nativeObjectPtr);
	Examples::AndroidExampleControllerProxy* pProxy = (Examples::AndroidExampleControllerProxy*)(nativeCallerProxyPtr);

	pProxy->SelectExample(pExample, nameString);
}


