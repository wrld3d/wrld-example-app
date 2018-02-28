// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "JniHelper.h"

namespace ExampleApp
{
    namespace Helpers
    {
		jclass JniHelper::LoadClassGlobalRef(AndroidNativeState& nativeState,
											 JNIEnv* env,
											 const std::string& javaClassName)
		{
			jstring strClassName = env->NewStringUTF(javaClassName.c_str());
			jclass classLocalRef = nativeState.LoadClass(env, strClassName);
			env->DeleteLocalRef(strClassName);

			jclass javaClass = static_cast<jclass>(env->NewGlobalRef(classLocalRef));
			env->DeleteLocalRef(classLocalRef);

			return javaClass;
		}

		jobject JniHelper::LoadInstanceGlobalRef(JNIEnv* env,
												 const std::string& javaConstructorSignature,
												 jclass javaClass,
												 ...)
		{
			va_list constructor_args;
			va_start(constructor_args, javaClass);

			jmethodID classConstructor = env->GetMethodID(javaClass, "<init>",
														  javaConstructorSignature.c_str());

			jobject instance = env->NewObjectV(javaClass,
											   classConstructor,
											   constructor_args);

			jobject javaInstance = env->NewGlobalRef(instance);
			env->DeleteLocalRef(instance);

			va_end(constructor_args);
			return javaInstance;
		}

		jobjectArray JniHelper::LoadStringArrayLocalRef(AndroidNativeState& nativeState,
														JNIEnv* env,
														const std::vector<std::string>& searchResults)
		{
			jstring strClassName = env->NewStringUTF("java/lang/String");
			jclass strClass = nativeState.LoadClass(env, strClassName);
			env->DeleteLocalRef(strClassName);

			jobjectArray searchResultArray = env->NewObjectArray(searchResults.size(), strClass, 0);
			env->DeleteLocalRef(strClass);

			for (int i = 0; i < searchResults.size(); i++)
			{
				jstring javaString = env->NewStringUTF(searchResults[i].c_str());
				env->SetObjectArrayElement(searchResultArray, i, javaString);
				env->DeleteLocalRef(javaString);
			}

			return searchResultArray;
		}
	}
}
