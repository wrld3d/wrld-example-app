// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidPersistentSettingsModel.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace PersistentSettings
    {
        AndroidPersistentSettingsModel::AndroidPersistentSettingsModel(AndroidNativeState& nativeState)
            : m_nativeState(nativeState)
        {
            ASSERT_NATIVE_THREAD

            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;

            jstring strClassName = env->NewStringUTF("com.eegeo.persistentstate.PersistentState");
            jclass uiClass = m_nativeState.LoadClass(env, strClassName);
            env->DeleteLocalRef(strClassName);

            m_jniApiClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
            jmethodID ctor = env->GetMethodID(m_jniApiClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

            jobject instance = env->NewObject(
                                   m_jniApiClass,
                                   ctor,
                                   m_nativeState.activity,
                                   (jlong)(this)
                               );

            m_jniApiInstance = env->NewGlobalRef(instance);
        }

        AndroidPersistentSettingsModel::~AndroidPersistentSettingsModel()
        {
            ASSERT_NATIVE_THREAD

            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;

            env->DeleteGlobalRef(m_jniApiInstance);
            env->DeleteGlobalRef(m_jniApiClass);
        }

        bool AndroidPersistentSettingsModel::TryGetValue(const std::string& name, bool& out_value) const
        {
            ASSERT_NATIVE_THREAD

            if(HasValue(name))
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jstring keyJstr = env->NewStringUTF(name.c_str());
                jmethodID methodId = env->GetMethodID(m_jniApiClass, "getBoolean", "(Ljava/lang/String;)Z");
                out_value = env->CallBooleanMethod(m_jniApiInstance, methodId, keyJstr);
                env->DeleteLocalRef(keyJstr);
                return true;
            }

            return false;
        }

        bool AndroidPersistentSettingsModel::TryGetValue(const std::string& name, int& out_value) const
        {
            ASSERT_NATIVE_THREAD

            if(HasValue(name))
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jstring keyJstr = env->NewStringUTF(name.c_str());
                jmethodID methodId = env->GetMethodID(m_jniApiClass, "getInt", "(Ljava/lang/String;)I");
                out_value = env->CallIntMethod(m_jniApiInstance, methodId, keyJstr);
                env->DeleteLocalRef(keyJstr);
                return true;
            }

            return false;
        }

        bool AndroidPersistentSettingsModel::TryGetValue(const std::string& name, double& out_value) const
        {
            ASSERT_NATIVE_THREAD

            if(HasValue(name))
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jstring keyJstr = env->NewStringUTF(name.c_str());
                jmethodID methodId = env->GetMethodID(m_jniApiClass, "getDouble", "(Ljava/lang/String;)D");
                out_value = env->CallDoubleMethod(m_jniApiInstance, methodId, keyJstr);
                env->DeleteLocalRef(keyJstr);
                return true;
            }

            return false;
        }

        bool AndroidPersistentSettingsModel::TryGetValue(const std::string& name, std::string& out_value) const
        {
            ASSERT_NATIVE_THREAD

            if(HasValue(name))
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jstring keyJstr = env->NewStringUTF(name.c_str());
                jmethodID methodId = env->GetMethodID(m_jniApiClass, "getString", "(Ljava/lang/String;)Ljava/lang/String;");
                jstring resultJString = static_cast<jstring>(env->CallObjectMethod(m_jniApiInstance, methodId, keyJstr));
                const char* chars = env->GetStringUTFChars(resultJString, 0);
                out_value = chars;
                env->ReleaseStringUTFChars(resultJString, chars);
                env->DeleteLocalRef(keyJstr);
                return true;
            }

            return false;
        }

        void AndroidPersistentSettingsModel::SetValue(const std::string& name, bool value)
        {
            ASSERT_NATIVE_THREAD

            SetValue(name, value, "setBoolean", "(Ljava/lang/String;Z)V");
        }

        void AndroidPersistentSettingsModel::SetValue(const std::string& name, int value)
        {
            ASSERT_NATIVE_THREAD

            SetValue(name, value, "setInt", "(Ljava/lang/String;I)V");
        }

        void AndroidPersistentSettingsModel::SetValue(const std::string& name, double value)
        {
            ASSERT_NATIVE_THREAD

            SetValue(name, value, "setDouble", "(Ljava/lang/String;D)V");
        }

        void AndroidPersistentSettingsModel::SetValue(const std::string& name, const std::string& value)
        {
            ASSERT_NATIVE_THREAD

            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            jstring keyJstr = env->NewStringUTF(name.c_str());
            jstring valueJstr = env->NewStringUTF(value.c_str());
            jmethodID methodId = env->GetMethodID(m_jniApiClass, "setString", "(Ljava/lang/String;Ljava/lang/String;)V");
            env->CallVoidMethod(m_jniApiInstance, methodId, keyJstr, valueJstr);
            env->DeleteLocalRef(keyJstr);
            env->DeleteLocalRef(valueJstr);
        }

        void AndroidPersistentSettingsModel::ClearAll()
        {
            ASSERT_NATIVE_THREAD

            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            jmethodID methodId = env->GetMethodID(m_jniApiClass, "clearAll", "()V");
            env->CallVoidMethod(m_jniApiInstance, methodId);
        }

        bool AndroidPersistentSettingsModel::HasValue(const std::string& name) const
        {
            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            jstring jstr = env->NewStringUTF(name.c_str());
            jmethodID method = env->GetMethodID(m_jniApiClass, "containsKey", "(Ljava/lang/String;)Z");
            bool result = env->CallBooleanMethod(m_jniApiInstance, method, jstr);
            env->DeleteLocalRef(jstr);
            return result;
        }

        template <typename TValue>
        void AndroidPersistentSettingsModel::SetValue(const std::string& name, TValue value, const std::string& method, const std::string& signature)
        {
            ASSERT_NATIVE_THREAD

            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            jstring keyJstr = env->NewStringUTF(name.c_str());
            jmethodID methodId = env->GetMethodID(m_jniApiClass, method.c_str(), signature.c_str());
            env->CallVoidMethod(m_jniApiInstance, methodId, keyJstr, value);
            env->DeleteLocalRef(keyJstr);
        }
    }
}
