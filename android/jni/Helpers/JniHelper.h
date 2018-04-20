// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include <cstdarg>
#include <string>

namespace ExampleApp
{
    namespace Helpers
    {
		class JniHelper
		{
		public:
			static jclass LoadClassGlobalRef(AndroidNativeState& nativeState,
											 JNIEnv* env,
											 const std::string& javaClassName);
			static jobject LoadInstanceGlobalRef(JNIEnv* env,
												 const std::string& constructorSignature,
												 jclass javaClass,
												 ...);	// constructor parameters

			static jclass LoadClassLocalRef(AndroidNativeState& nativeState,
											JNIEnv* env,
											const std::string& javaClassName);
			static jobjectArray LoadArrayLocalRef(JNIEnv* env,
												  jclass javaClass,
												  const std::string& constructorSignature,
												  int size,
												  ...);
		};
    }
}
