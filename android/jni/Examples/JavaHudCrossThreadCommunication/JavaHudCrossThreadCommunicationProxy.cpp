// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JavaHudCrossThreadCommunicationProxy.h"
#include "JavaHudCrossThreadCommunicationExample.h"

using namespace Examples;

JNIEXPORT void JNICALL Java_com_eegeo_examples_themereaderwriter_ThemeReaderWriterJniMethods_SetCurrentTheme(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jstring name)
{
	//extract the string from java via the JNI
	const char* chars = jenv->GetStringUTFChars(name, 0);
	std::string nameString = chars;
	jenv->ReleaseStringUTFChars(name, chars);

	Examples::JavaHudCrossThreadCommunicationExample* pExample = (Examples::JavaHudCrossThreadCommunicationExample*)(nativeObjectPtr);

	pExample->SetCurrentThemeByName(nameString);
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_themereaderwriter_ThemeReaderWriterJniMethods_ReadCurrentThemeName(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::JavaHudCrossThreadCommunicationExample* pExample = (Examples::JavaHudCrossThreadCommunicationExample*)(nativeObjectPtr);

	pExample->PostCurrentThemeNameToHud();
}
