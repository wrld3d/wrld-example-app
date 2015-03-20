// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkView::WatermarkView(AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com.eegeo.watermark.WatermarkView");
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

            WatermarkView::~WatermarkView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void WatermarkView::OnSelected()
            {
                ASSERT_UI_THREAD

                m_callbacks.ExecuteCallbacks();
            }

            void WatermarkView::SetOnScreenStateToIntermediateValue(float value)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
                env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, value);
            }

            void WatermarkView::SetFullyOnScreen()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToActive", "()V");
                env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
            }

            void WatermarkView::SetFullyOffScreen()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToInactive", "()V");
                env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
            }

            void WatermarkView::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.AddCallback(callback);
            }

            void WatermarkView::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.RemoveCallback(callback);
            }
        }
    }
}
