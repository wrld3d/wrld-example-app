// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidFlurryMetricsService.h"

namespace ExampleApp
{
	namespace Metrics
	{
		AndroidFlurryMetricsService::AndroidFlurryMetricsService(AndroidNativeState* pNativeState)
		: m_pNativeState(pNativeState)
		, m_enabled(false)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com/eegeo/flurry/FlurryWrapper");
			jclass flurryClass = m_pNativeState->LoadClass(env, strClassName);

			m_flurryClass = static_cast<jclass>(env->NewGlobalRef(flurryClass));

			env->DeleteLocalRef(strClassName);
		}

		AndroidFlurryMetricsService::~AndroidFlurryMetricsService()
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			env->DeleteGlobalRef(m_flurryClass);
		}

		void AndroidFlurryMetricsService::BeginSession(const std::string& apiKey, const std::string& appVersion)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring apiKeyStr = env->NewStringUTF(apiKey.c_str());
			jstring appVersionStr = env->NewStringUTF(appVersion.c_str());

			jmethodID beginMethod = env->GetStaticMethodID(m_flurryClass, "begin", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;Ljava/lang/String;Ljava/lang/String;)V");
			env->CallStaticVoidMethod(m_flurryClass, beginMethod, m_pNativeState->activity, apiKeyStr, appVersionStr);

			env->DeleteLocalRef(apiKeyStr);
			env->DeleteLocalRef(appVersionStr);

			m_enabled = true;
		}

		void AndroidFlurryMetricsService::SetPosition(double latitude, double longitude, double horizAccuracy, double vertAccuracy)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID setPositionMethod = env->GetStaticMethodID(m_flurryClass, "setPosition", "(FF)V");
			env->CallStaticVoidMethod(m_flurryClass, setPositionMethod, latitude, longitude);
		}

		void AndroidFlurryMetricsService::SetEvent(const std::string& eventString)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring eventStr = env->NewStringUTF(eventString.c_str());

			jmethodID setEventMethod = env->GetStaticMethodID(m_flurryClass, "setEvent", "(Ljava/lang/String;)V");
			env->CallStaticVoidMethod(m_flurryClass, setEventMethod, eventStr);

			env->DeleteLocalRef(eventStr);
		}

		void AndroidFlurryMetricsService::SetEvent(const std::string& eventString, const std::string& key, const std::string& value)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring eventStr = env->NewStringUTF(eventString.c_str());
			jstring keyStr = env->NewStringUTF(key.c_str());
			jstring valStr = env->NewStringUTF(value.c_str());

			jmethodID setEventMethod = env->GetStaticMethodID(m_flurryClass, "setEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
			env->CallStaticVoidMethod(m_flurryClass, setEventMethod, eventStr, keyStr, valStr);

			env->DeleteLocalRef(valStr);
			env->DeleteLocalRef(keyStr);
			env->DeleteLocalRef(eventStr);
		}

		void AndroidFlurryMetricsService::SetEvent(const std::string& eventString, const std::string& key1, const std::string& value1, const std::string& key2, const std::string& value2)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring eventStr = env->NewStringUTF(eventString.c_str());
			jstring key1Str = env->NewStringUTF(key1.c_str());
			jstring val1Str = env->NewStringUTF(value1.c_str());
			jstring key2Str = env->NewStringUTF(key2.c_str());
			jstring val2Str = env->NewStringUTF(value2.c_str());

			jmethodID setEventMethod = env->GetStaticMethodID(m_flurryClass, "setEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
			env->CallStaticVoidMethod(m_flurryClass, setEventMethod, eventStr, key1Str, val1Str, key2Str, val2Str);

			env->DeleteLocalRef(val2Str);
			env->DeleteLocalRef(key2Str);
			env->DeleteLocalRef(val1Str);
			env->DeleteLocalRef(key1Str);
			env->DeleteLocalRef(eventStr);
		}

		void AndroidFlurryMetricsService::SetEvent(const std::string& eventString, const std::string& key1, const std::string& value1, const std::string& key2, const std::string& value2, const std::string& key3, const std::string& value3)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring eventStr = env->NewStringUTF(eventString.c_str());
			jstring key1Str = env->NewStringUTF(key1.c_str());
			jstring val1Str = env->NewStringUTF(value1.c_str());
			jstring key2Str = env->NewStringUTF(key2.c_str());
			jstring val2Str = env->NewStringUTF(value2.c_str());
			jstring key3Str = env->NewStringUTF(key2.c_str());
			jstring val3Str = env->NewStringUTF(value2.c_str());

			jmethodID setEventMethod = env->GetStaticMethodID(m_flurryClass, "setEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
			env->CallStaticVoidMethod(m_flurryClass, setEventMethod, eventStr, key1Str, val1Str, key2Str, val2Str, key3Str, val3Str);

			env->DeleteLocalRef(val3Str);
			env->DeleteLocalRef(key3Str);
			env->DeleteLocalRef(val2Str);
			env->DeleteLocalRef(key2Str);
			env->DeleteLocalRef(val1Str);
			env->DeleteLocalRef(key1Str);
			env->DeleteLocalRef(eventStr);
		}

		void AndroidFlurryMetricsService::BeginTimedEvent(const std::string& eventString)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring eventStr = env->NewStringUTF(eventString.c_str());

			jmethodID beginTimedEventMethod = env->GetStaticMethodID(m_flurryClass, "setEvent", "(Ljava/lang/String;)V");
			env->CallStaticVoidMethod(m_flurryClass, beginTimedEventMethod, eventStr);

			env->DeleteLocalRef(eventStr);
		}

		void AndroidFlurryMetricsService::BeginTimedEvent(const std::string& eventString, const std::string& key1, const std::string& value1)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring eventStr = env->NewStringUTF(eventString.c_str());
			jstring key1Str = env->NewStringUTF(key1.c_str());
			jstring val1Str = env->NewStringUTF(value1.c_str());

			jmethodID beginTimedEventMethod = env->GetStaticMethodID(m_flurryClass, "beginTimedEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
			env->CallStaticVoidMethod(m_flurryClass, beginTimedEventMethod, eventStr, key1Str, val1Str);

			env->DeleteLocalRef(val1Str);
			env->DeleteLocalRef(key1Str);
			env->DeleteLocalRef(eventStr);
		}

		void AndroidFlurryMetricsService::EndTimedEvent(const std::string& eventString)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring eventStr = env->NewStringUTF(eventString.c_str());

			jmethodID endTimedEventMethod = env->GetStaticMethodID(m_flurryClass, "endTimedEvent", "(Ljava/lang/String;)V");
			env->CallStaticVoidMethod(m_flurryClass, endTimedEventMethod, eventStr);

			env->DeleteLocalRef(eventStr);
		}

		void AndroidFlurryMetricsService::EndTimedEvent(const std::string& eventString, const std::string& key1, const std::string& value1)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring eventStr = env->NewStringUTF(eventString.c_str());
			jstring key1Str = env->NewStringUTF(key1.c_str());
			jstring val1Str = env->NewStringUTF(value1.c_str());

			jmethodID endTimedEventMethod = env->GetStaticMethodID(m_flurryClass, "endTimedEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
			env->CallStaticVoidMethod(m_flurryClass, endTimedEventMethod, eventStr, key1Str, val1Str);

			env->DeleteLocalRef(val1Str);
			env->DeleteLocalRef(key1Str);
			env->DeleteLocalRef(eventStr);
		}

		bool AndroidFlurryMetricsService::IsEnabled() const
		{
			return m_enabled;
		}
	}
}
