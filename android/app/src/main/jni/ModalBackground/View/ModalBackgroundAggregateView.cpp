// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundAggregateView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "Types.h"
#include "UpdateNativeModalBackgroundMessage.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            ModalBackgroundAggregateView::ModalBackgroundAggregateView(AndroidNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus)
                : m_nativeState(nativeState)
                , m_messageBus(messageBus)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com/eegeo/modalbackground/ModalBackgroundView");
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

            ModalBackgroundAggregateView::~ModalBackgroundAggregateView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void ModalBackgroundAggregateView::SetFullyActive()
            {
                ASSERT_UI_THREAD
                SetActiveStateToIntermediateValue(1.0f);
            }

            void ModalBackgroundAggregateView::SetFullyInactive()
            {
                ASSERT_UI_THREAD
                SetActiveStateToIntermediateValue(0.0f);
            }

            void ModalBackgroundAggregateView::SetActiveStateToIntermediateValue(float modality)
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToIntermediateActivityState = env->GetMethodID(m_uiViewClass, "animateToIntermediateActivityState", "(F)V");
                env->CallVoidMethod(m_uiView, animateToIntermediateActivityState, modality);

                // Publish message to native view.
                m_messageBus.Publish(Modality::UpdateNativeModalBackgroundMessage(modality, false));
            }

            void ModalBackgroundAggregateView::InsertTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
            	m_tappedCallbacks.AddCallback(callback);
            }

            void ModalBackgroundAggregateView::RemoveTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
            	m_tappedCallbacks.RemoveCallback(callback);
            }

            void ModalBackgroundAggregateView::HandleViewTapped()
            {
            	m_tappedCallbacks.ExecuteCallbacks();
            }
        }
    }
}
