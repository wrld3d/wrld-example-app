// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
        	OptionsView::OptionsView(AndroidNativeState& nativeState)
            : m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com/eegeo/options/OptionsView");
                jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
                jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                jobject instance = env->NewObject(
                                       m_uiViewClass,
                                       uiViewCtor,
                                       m_nativeState.activity,
                                       (jlong)(this)
                                   );

                m_uiView = env->NewGlobalRef(instance);
            }

        	OptionsView::~OptionsView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            bool OptionsView::IsStreamOverWifiOnlySelected() const
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID isStreamOverWifiOnlySelected = env->GetMethodID(m_uiViewClass, "isStreamOverWifiOnlySelected", "()Z");
                const bool result = env->CallBooleanMethod(m_uiView, isStreamOverWifiOnlySelected);
                return result;
            }

            bool OptionsView::IsCacheEnabledSelected() const
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID isCacheEnabledSelected = env->GetMethodID(m_uiViewClass, "isCacheEnabledSelected", "()Z");
                const bool result = env->CallBooleanMethod(m_uiView, isCacheEnabledSelected);
                return result;
            }

            void OptionsView::SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID setStreamOverWifiOnlySelected = env->GetMethodID(m_uiViewClass, "setStreamOverWifiOnlySelected", "(Z)V");
                env->CallVoidMethod(m_uiView, setStreamOverWifiOnlySelected, isStreamOverWifiOnlySelected);
            }

            void OptionsView::SetCacheEnabledSelected(bool isCacheEnabledSelected)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID setCacheEnabledSelected = env->GetMethodID(m_uiViewClass, "setCacheEnabledSelected", "(Z)V");
                env->CallVoidMethod(m_uiView, setCacheEnabledSelected, isCacheEnabledSelected);
            }

            void OptionsView::SetReplayTutorialsSelected(bool isReplayTutorialsSelected)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID setReplayTutorialsSelected = env->GetMethodID(m_uiViewClass, "setReplayTutorialsSelected", "(Z)V");
                env->CallVoidMethod(m_uiView, setReplayTutorialsSelected, isReplayTutorialsSelected);
            }

            void OptionsView::Open()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID openOptions = env->GetMethodID(m_uiViewClass, "openOptions", "()V");
                env->CallVoidMethod(m_uiView, openOptions);
            }

            void OptionsView::Close()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID closeOptions = env->GetMethodID(m_uiViewClass, "closeOptions", "()V");
                env->CallVoidMethod(m_uiView, closeOptions);
            }

            void OptionsView::ConcludeCacheClearCeremony()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID concludeCacheClearCeremony = env->GetMethodID(m_uiViewClass, "concludeCacheClearCeremony", "()V");
                env->CallVoidMethod(m_uiView, concludeCacheClearCeremony);
            }

            void OptionsView::HandleCloseSelected()
            {
                ASSERT_UI_THREAD

                m_closeCallbacks.ExecuteCallbacks();
            }

            void OptionsView::HandleStreamOverWifiOnlySelectionStateChanged()
            {
                ASSERT_UI_THREAD

                m_wifiOnlyCallbacks.ExecuteCallbacks();
            }

            void OptionsView::HandleCacheEnabledSelectionStateChanged()
            {
                ASSERT_UI_THREAD

                m_cacheEnabledCallbacks.ExecuteCallbacks();
            }

            void OptionsView::HandleClearCacheSelected()
            {
                ASSERT_UI_THREAD

                m_clearCacheCallbacks.ExecuteCallbacks();
            }

            void OptionsView::InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closeCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closeCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_wifiOnlyCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_wifiOnlyCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_cacheEnabledCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_cacheEnabledCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_clearCacheCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_clearCacheCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                ASSERT_UI_THREAD

                m_replayTutorialsToggledCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback) 
            {
                ASSERT_UI_THREAD

                m_replayTutorialsToggledCallbacks.RemoveCallback(callback);
            }
        }
    }
}
