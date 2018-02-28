// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include <cstdarg>
#include <vector>
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
												 const std::string& javaConstructorSignature,
												 jclass javaClass,
												 ...);	// constructor parameters

			static jobjectArray LoadStringArrayLocalRef(AndroidNativeState& nativeState,
														JNIEnv* env,
														const std::vector<std::string>& searchResults);
		};
    }
}
