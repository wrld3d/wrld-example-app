// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationConfirmationView::MyPinCreationConfirmationView(AndroidNativeState& androidNativeState)
                : m_nativeState(androidNativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com.eegeo.mypincreation.MyPinCreationConfirmationView");
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

            MyPinCreationConfirmationView::~MyPinCreationConfirmationView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void MyPinCreationConfirmationView::OnConfirmed()
            {
                ASSERT_UI_THREAD
                m_confirmedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationConfirmationView::OnDismissed()
            {
                ASSERT_UI_THREAD
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationConfirmationView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinCreationConfirmationView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationConfirmationView::InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_confirmedCallbacks.AddCallback(callback);
            }

            void MyPinCreationConfirmationView::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_confirmedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationConfirmationView::SetOnScreenStateToIntermediateValue(float value)
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID method = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
                env->CallVoidMethod(m_uiView, method, value);
            }

            void MyPinCreationConfirmationView::SetFullyOnScreen()
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID method = env->GetMethodID(m_uiViewClass, "animateToActive", "()V");
                env->CallVoidMethod(m_uiView, method);
            }

            void MyPinCreationConfirmationView::SetFullyOffScreen()
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID method = env->GetMethodID(m_uiViewClass, "animateToInactive", "()V");
                env->CallVoidMethod(m_uiView, method);
            }
        }
    }
}
