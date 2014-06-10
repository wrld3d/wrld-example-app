/*
 * JavaHudCrossThreadCommunicationProxy.cpp
 *
 *  Created on: May 23, 2014
 *      Author: kimbleoperations
 */

#include "JavaHudCrossThreadCommunicationProxy.h"
#include "JavaHudCrossThreadCommunicationExample.h"

using namespace Examples;

JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_setCurrentTheme(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr,
		jstring name)
{
	//extract the string from java via the JNI
	const char* chars = jenv->GetStringUTFChars(name, 0);
	std::string nameString = chars;
	jenv->ReleaseStringUTFChars(name, chars);

	//create a an item to set the theme and post it to our thread safe queue for deferred execution on native main thread
	Examples::JavaHudCrossThreadCommunicationExample* pExample = (Examples::JavaHudCrossThreadCommunicationExample*)(nativeObjectPtr);

	pExample->SetCurrentThemeByName(nameString);
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_readCurrentThemeName(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	//create a an item to read the theme and post it to our thread safe queue for deferred execution on native main thread
	Examples::JavaHudCrossThreadCommunicationExample* pExample = (Examples::JavaHudCrossThreadCommunicationExample*)(nativeObjectPtr);

	pExample->PostCurrentThemeNameToHud();
}
