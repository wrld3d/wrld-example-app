// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            FlattenButtonView::FlattenButtonView(AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com.eegeo.flattenbutton.FlattenButtonView");
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

            FlattenButtonView::~FlattenButtonView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void FlattenButtonView::SetToggled(bool toggled)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID updateViewStateBasedOnFlattening = env->GetMethodID(m_uiViewClass, "updateViewStateBasedOnFlattening", "(Z)V");
                env->CallVoidMethod(m_uiView, updateViewStateBasedOnFlattening, toggled);
            }

            void FlattenButtonView::OnToggle(bool toggled)
            {
                ASSERT_UI_THREAD

                m_callbacks.ExecuteCallbacks(toggled);
            }

            void FlattenButtonView::SetOnScreenStateToIntermediateValue(float value)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
                env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, value);
            }

            void FlattenButtonView::SetFullyOnScreen()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToActive", "()V");
                env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
            }

            void FlattenButtonView::SetFullyOffScreen()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToInactive", "()V");
                env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
            }

            void FlattenButtonView::InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.AddCallback(callback);
            }

            void FlattenButtonView::RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.RemoveCallback(callback);
            }

            void FlattenButtonView::SetViewEnabled(bool enabled)
            {
            	ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID setViewEnabledMethod = env->GetMethodID(m_uiViewClass, "setViewEnabled", "(Z)V");
				env->CallVoidMethod(m_uiView, setViewEnabledMethod, enabled);
            }
        }
    }
}
