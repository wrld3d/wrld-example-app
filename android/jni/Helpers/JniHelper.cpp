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
			jclass classLocalRef = LoadClassLocalRef(nativeState, env, javaClassName);
			jclass javaClass = static_cast<jclass>(env->NewGlobalRef(classLocalRef));
			env->DeleteLocalRef(classLocalRef);

			return javaClass;
		}

		jobject JniHelper::LoadInstanceGlobalRef(JNIEnv* env,
												 const std::string& constructorSignature,
												 jclass javaClass,
												 ...)
		{
			va_list constructor_args;
			va_start(constructor_args, javaClass);

			jmethodID classConstructor = env->GetMethodID(javaClass, "<init>",
														  constructorSignature.c_str());

			jobject instance = env->NewObjectV(javaClass,
											   classConstructor,
											   constructor_args);

			jobject javaInstance = env->NewGlobalRef(instance);
			env->DeleteLocalRef(instance);

			va_end(constructor_args);
			return javaInstance;
		}

		jclass JniHelper::LoadClassLocalRef(AndroidNativeState& nativeState,
											JNIEnv* env,
											const std::string& javaClassName)
		{
			jstring strClassName = env->NewStringUTF(javaClassName.c_str());
			jclass javaClass = nativeState.LoadClass(env, strClassName);
			env->DeleteLocalRef(strClassName);

			return javaClass;
		}

		jobjectArray JniHelper::LoadArrayLocalRef(JNIEnv* env,
												  jclass javaClass,
												  const std::string& constructorSignature,
												  int size,
												  ...)
		{
			va_list constructor_args;
			va_start(constructor_args, size);

			jmethodID classConstructor = env->GetMethodID(javaClass, "<init>",
														  constructorSignature.c_str());

			jobjectArray javaArray = env->NewObjectArray(size, javaClass, 0);

			for (int i = 0; i < size; i++)
			{
				jobject arrayElement = env->NewObjectV(javaClass, classConstructor, constructor_args);
				env->SetObjectArrayElement(javaArray, i, arrayElement);
				env->DeleteLocalRef(arrayElement);
			}

			va_end(constructor_args);
			return javaArray;
		}
	}
}
