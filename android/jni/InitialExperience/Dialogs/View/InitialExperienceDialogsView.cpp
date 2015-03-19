// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace View
			{
				InitialExperienceDialogsView::InitialExperienceDialogsView(AndroidNativeState& androidNativeState)
				: m_nativeState(androidNativeState)
				{
					ASSERT_UI_THREAD

					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jstring strClassName = env->NewStringUTF("com/eegeo/initialexperience/dialogs/InitialExperienceDialogsView");
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

				InitialExperienceDialogsView::~InitialExperienceDialogsView()
				{
					ASSERT_UI_THREAD

					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;
					jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
					env->CallVoidMethod(m_uiView, removeHudMethod);
					env->DeleteGlobalRef(m_uiView);
					env->DeleteGlobalRef(m_uiViewClass);
				}

				void InitialExperienceDialogsView::Open(const InitialExperienceDialogType::Values& dialogType, const std::string& title, const std::string &description)
				{
					ASSERT_UI_THREAD

					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jstring titleStr = env->NewStringUTF(title.c_str());
					jstring descStr = env->NewStringUTF(description.c_str());

					jmethodID showDialogMethod = env->GetMethodID(m_uiViewClass, "showDialog", "(ILjava/lang/String;Ljava/lang/String;)V");
					env->CallVoidMethod(m_uiView, showDialogMethod, static_cast<int>(dialogType), titleStr, descStr);

					env->DeleteLocalRef(titleStr);
					env->DeleteLocalRef(descStr);
				}

				void InitialExperienceDialogsView::Close()
				{
					ASSERT_UI_THREAD

					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jmethodID dismissDialogMethod = env->GetMethodID(m_uiViewClass, "dismissCurrentDialog", "()V");
					env->CallVoidMethod(m_uiView, dismissDialogMethod);
				}

				void InitialExperienceDialogsView::CloseButtonTapped()
				{
					m_closedButtonCallbacks.ExecuteCallbacks();
				}

				void InitialExperienceDialogsView::SetModalBackground(bool active)
				{
					ASSERT_UI_THREAD

					AndroidSafeNativeThreadAttachment attached(m_nativeState);
					JNIEnv* env = attached.envForThread;

					jmethodID setModalBackgroundMethod = env->GetMethodID(m_uiViewClass, "setModalBackgroundActive", "(Z)V");
					env->CallVoidMethod(m_uiView, setModalBackgroundMethod, active);
				}

				void InitialExperienceDialogsView::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
				{
					ASSERT_UI_THREAD
					m_closedButtonCallbacks.AddCallback(callback);
				}

				void InitialExperienceDialogsView::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
				{
					ASSERT_UI_THREAD
					m_closedButtonCallbacks.RemoveCallback(callback);
				}
			}
		}
	}
}
