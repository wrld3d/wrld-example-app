// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef JAVAHUDCROSSTHREADCOMMUNICATIONPROXY_H_
#define JAVAHUDCROSSTHREADCOMMUNICATIONPROXY_H_

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_themereaderwriter_ThemeReaderWriterJniMethods_SetCurrentTheme(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeAppWindowPtr,
	    jstring name);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_themereaderwriter_ThemeReaderWriterJniMethods_ReadCurrentThemeName(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);
}

#endif /* JAVAHUDCROSSTHREADCOMMUNICATIONPROXY_H_ */
