// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidExampleControllerProxy.h"
#include "AndroidExampleControllerView.h"

using namespace Examples;

JNIEXPORT void JNICALL Java_com_eegeo_examples_examplecontroller_ExampleControllerJniMethods_ActivatePrevious(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::AndroidExampleControllerView* pExample = (Examples::AndroidExampleControllerView*)(nativeObjectPtr);
	pExample->SelectPrevious();
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_examplecontroller_ExampleControllerJniMethods_ActivateNext(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
	Examples::AndroidExampleControllerView* pExample = (Examples::AndroidExampleControllerView*)(nativeObjectPtr);
	pExample->SelectNext();
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_examplecontroller_ExampleControllerJniMethods_SelectExample(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jstring selectedExample)
{
	//extract the string from java via the JNI
	const char* chars = jenv->GetStringUTFChars(selectedExample, 0);
	std::string nameString = chars;
	jenv->ReleaseStringUTFChars(selectedExample, chars);

	Examples::AndroidExampleControllerView* pExample = (Examples::AndroidExampleControllerView*)(nativeObjectPtr);

	pExample->SetCurrentExampleName(nameString);
}


