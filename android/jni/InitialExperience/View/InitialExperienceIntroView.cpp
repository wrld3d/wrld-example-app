// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace View
		{
			InitialExperienceIntroView::InitialExperienceIntroView(AndroidNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus)
			: m_nativeState(nativeState)
			, m_messageBus(messageBus)
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jstring strClassName = env->NewStringUTF("com/eegeo/initialexperience/intro/InitialExperienceIntroView");
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

			InitialExperienceIntroView::~InitialExperienceIntroView()
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;
				jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
				env->CallVoidMethod(m_uiView, removeHudMethod);
				env->DeleteGlobalRef(m_uiView);
				env->DeleteGlobalRef(m_uiViewClass);
			}

			void InitialExperienceIntroView::Show()
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID showDialogMethod = env->GetMethodID(m_uiViewClass, "show", "()V");
				env->CallVoidMethod(m_uiView, showDialogMethod);

				m_messageBus.Publish(Modality::UpdateNativeModalBackgroundMessage(1.0f, true));
			}

			void InitialExperienceIntroView::Dismiss()
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID dismissDialogMethod = env->GetMethodID(m_uiViewClass, "dismiss", "()V");
				env->CallVoidMethod(m_uiView, dismissDialogMethod);

				m_messageBus.Publish(Modality::UpdateNativeModalBackgroundMessage(0.0f, false));
			}

			void InitialExperienceIntroView::OnDismiss()
			{
				Dismiss();
				m_dismissedCallbacks.ExecuteCallbacks();
			}

			void InitialExperienceIntroView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
			{
				ASSERT_UI_THREAD
				m_dismissedCallbacks.AddCallback(callback);
			}

			void InitialExperienceIntroView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
			{
				ASSERT_UI_THREAD
				m_dismissedCallbacks.RemoveCallback(callback);
			}

			void InitialExperienceIntroView::ShowExitIUX()
			{
			}

			void InitialExperienceIntroView::DismissExitIUX()
			{
			}
		}
	}
}
