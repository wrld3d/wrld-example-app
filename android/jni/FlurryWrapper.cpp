// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlurryWrapper.h"

#if (FLURRY_ENABLED)

namespace ExampleApp
{
	AndroidNativeState* FlurryWrapper::m_pNativeState = NULL;

	void FlurryWrapper::Begin(const char* apiKey, const char* appVersion)
	{
		Eegeo_TTY("FlurryBegin: App version - : %s\n", appVersion);
		AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
		JNIEnv* env = attached.envForThread;

		jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
		jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

		jstring apiKeyStr = env->NewStringUTF(apiKey);
		jstring appVersionStr = env->NewStringUTF(appVersion);

		jmethodID beginMethod = env->GetStaticMethodID(flurryWrapperClass, "begin", "(Lcom/eegeo/mobileexampleapp/MainActivity;Ljava/lang/String;Ljava/lang/String;)V");
		env->CallStaticVoidMethod(flurryWrapperClass, beginMethod, m_pNativeState->activity, apiKeyStr, appVersionStr);

		env->DeleteLocalRef(apiKeyStr);
		env->DeleteLocalRef(appVersionStr);
		env->DeleteLocalRef(strClassName);
	}

	void FlurryWrapper::SetPosition(double latitude, double longitude, double horizAccuracy, double vertAccuracy)
	{
		Eegeo_TTY("Flurry SetPosition: %f, %f\n", latitude, longitude);

        AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
        JNIEnv* env = attached.envForThread;

        jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
        jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

        jmethodID setPositionMethod = env->GetStaticMethodID(flurryWrapperClass, "setPosition", "(FF)V");
        env->CallStaticVoidMethod(flurryWrapperClass, setPositionMethod, latitude, longitude);

        env->DeleteLocalRef(strClassName);
	}

	void FlurryWrapper::SetEvent(const char* string)
	{
		Eegeo_TTY("Flurry SetEvent: %s\n", string);

        AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
        JNIEnv* env = attached.envForThread;

        jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
        jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

        jstring eventStr = env->NewStringUTF(string);

        jmethodID setEventMethod = env->GetStaticMethodID(flurryWrapperClass, "setEvent", "(Ljava/lang/String;)V");
        env->CallStaticVoidMethod(flurryWrapperClass, setEventMethod, eventStr);

        env->DeleteLocalRef(eventStr);
        env->DeleteLocalRef(strClassName);

	}

	void FlurryWrapper::SetEvent(const char* string, const char* key1, const char* value1)
	{
		Eegeo_TTY("Flurry SetEvent: %s\nkey: %s\tvalue: %s\n", string, key1, value1);

        AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
        JNIEnv* env = attached.envForThread;

        jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
        jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

        jstring eventStr = env->NewStringUTF(string);
        jstring key1Str = env->NewStringUTF(key1);
        jstring val1Str = env->NewStringUTF(value1);

        jmethodID setEventMethod = env->GetStaticMethodID(flurryWrapperClass, "setEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        env->CallStaticVoidMethod(flurryWrapperClass, setEventMethod, eventStr, key1Str, val1Str);

        env->DeleteLocalRef(val1Str);
        env->DeleteLocalRef(key1Str);
        env->DeleteLocalRef(eventStr);
        env->DeleteLocalRef(strClassName);
	}

	void FlurryWrapper::SetEvent(const char* string, const char* key1, const char* value1, const char* key2, const char* value2)
	{
		Eegeo_TTY("Flurry SetEvent: %s\nkey1: %s\tvalue1: %s\nkey2: %s\tvalue2: %s\n", string, key1, value1, key2, value2);

        AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
        JNIEnv* env = attached.envForThread;

        jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
        jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

        jstring eventStr = env->NewStringUTF(string);
        jstring key1Str = env->NewStringUTF(key1);
        jstring val1Str = env->NewStringUTF(value1);
        jstring key2Str = env->NewStringUTF(key2);
        jstring val2Str = env->NewStringUTF(value2);

        jmethodID setEventMethod = env->GetStaticMethodID(flurryWrapperClass, "setEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        env->CallStaticVoidMethod(flurryWrapperClass, setEventMethod, eventStr, key1Str, val1Str, key2Str, val2Str);

        env->DeleteLocalRef(val2Str);
        env->DeleteLocalRef(key2Str);
        env->DeleteLocalRef(val1Str);
        env->DeleteLocalRef(key1Str);
        env->DeleteLocalRef(eventStr);
        env->DeleteLocalRef(strClassName);
	}

	void FlurryWrapper::SetEvent(const char* string, const char* key1, const char* value1, const char* key2, const char* value2, const char* key3, const char* value3)
	{
		Eegeo_TTY("Flurry SetEvent: %s\nkey1: %s\tvalue1: %s\nkey2: %s\tvalue2: %s\nkey3: %s\tvalue3: %s\n", string, key1, value1, key2, value2, key3, value3);

        AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
        JNIEnv* env = attached.envForThread;

        jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
        jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

        jstring eventStr = env->NewStringUTF(string);
        jstring key1Str = env->NewStringUTF(key1);
        jstring val1Str = env->NewStringUTF(value1);
        jstring key2Str = env->NewStringUTF(key2);
        jstring val2Str = env->NewStringUTF(value2);
        jstring key3Str = env->NewStringUTF(key2);
        jstring val3Str = env->NewStringUTF(value2);

        jmethodID setEventMethod = env->GetStaticMethodID(flurryWrapperClass, "setEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        env->CallStaticVoidMethod(flurryWrapperClass, setEventMethod, eventStr, key1Str, val1Str, key2Str, val2Str, key3Str, val3Str);

        env->DeleteLocalRef(val3Str);
        env->DeleteLocalRef(key3Str);
        env->DeleteLocalRef(val2Str);
        env->DeleteLocalRef(key2Str);
        env->DeleteLocalRef(val1Str);
        env->DeleteLocalRef(key1Str);
        env->DeleteLocalRef(eventStr);
        env->DeleteLocalRef(strClassName);
	}

	void FlurryWrapper::BeginTimedEvent(const char* string)
	{
		Eegeo_TTY("Flurry: BeginTimedEvent: %s\n", string);

        AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
        JNIEnv* env = attached.envForThread;

        jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
        jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

        jstring eventStr = env->NewStringUTF(string);

        jmethodID beginTimedEventMethod = env->GetStaticMethodID(flurryWrapperClass, "setEvent", "(Ljava/lang/String;)V");
        env->CallStaticVoidMethod(flurryWrapperClass, beginTimedEventMethod, eventStr);

        env->DeleteLocalRef(eventStr);
        env->DeleteLocalRef(strClassName);
	}

	void FlurryWrapper::BeginTimedEvent(const char* string, const char* key1, const char* value1)
	{
		Eegeo_TTY("Flurry: BeginTimedEvent: %s\nkey: %s\tvalue: %s\n", string, key1, value1);

        AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
        JNIEnv* env = attached.envForThread;

        jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
        jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

        jstring eventStr = env->NewStringUTF(string);
        jstring key1Str = env->NewStringUTF(key1);
        jstring val1Str = env->NewStringUTF(value1);

        jmethodID beginTimedEventMethod = env->GetStaticMethodID(flurryWrapperClass, "beginTimedEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        env->CallStaticVoidMethod(flurryWrapperClass, beginTimedEventMethod, eventStr, key1Str, val1Str);

        env->DeleteLocalRef(val1Str);
        env->DeleteLocalRef(key1Str);
        env->DeleteLocalRef(eventStr);
        env->DeleteLocalRef(strClassName);
	}

	void FlurryWrapper::EndTimedEvent(const char* string)
	{
		Eegeo_TTY("Flurry: EndTimedEvent: %s\n", string);

        AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
        JNIEnv* env = attached.envForThread;

        jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
        jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

        jstring eventStr = env->NewStringUTF(string);

        jmethodID endTimedEventMethod = env->GetStaticMethodID(flurryWrapperClass, "endTimedEvent", "(Ljava/lang/String;)V");
        env->CallStaticVoidMethod(flurryWrapperClass, endTimedEventMethod, eventStr);

        env->DeleteLocalRef(eventStr);
        env->DeleteLocalRef(strClassName);
	}

	void FlurryWrapper::EndTimedEvent(const char* string, const char* key1, const char* value1)
	{
		Eegeo_TTY("Flurry: EndTimedEvent: %s\nkey: %s\tvalue: %s\n", string, key1, value1);

        AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
        JNIEnv* env = attached.envForThread;

        jstring strClassName = env->NewStringUTF("com.eegeo.flurry.FlurryWrapper");
        jclass flurryWrapperClass = m_pNativeState->LoadClass(env, strClassName);

        jstring eventStr = env->NewStringUTF(string);
        jstring key1Str = env->NewStringUTF(key1);
        jstring val1Str = env->NewStringUTF(value1);

        jmethodID endTimedEventMethod = env->GetStaticMethodID(flurryWrapperClass, "endTimedEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        env->CallStaticVoidMethod(flurryWrapperClass, endTimedEventMethod, eventStr, key1Str, val1Str);

        env->DeleteLocalRef(val1Str);
        env->DeleteLocalRef(key1Str);
        env->DeleteLocalRef(eventStr);
        env->DeleteLocalRef(strClassName);
	}

	void FlurryWrapper::InitialiseJavaInterface(AndroidNativeState* pNativeState)
	{
		m_pNativeState = pNativeState;
	}
}

#endif
