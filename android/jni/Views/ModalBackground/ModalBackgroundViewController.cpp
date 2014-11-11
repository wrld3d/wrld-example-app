// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModalBackgroundViewController.h"
#include "Types.h"
#include "ModalityModel.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
		ModalBackgroundViewController::ModalBackgroundViewController(
			AndroidNativeState& nativeState,
			Modality::IModalityModel& modalityModel
		)
		: m_nativeState(nativeState)
		, m_modalityModel(modalityModel)
		, m_pOpenStateChangedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<ModalBackgroundViewController>)(this, &ModalBackgroundViewController::OpenStateChangedCallback))
		{
			ASSERT_UI_THREAD

			m_modalityModel.InsertModalityChangedCallback(*m_pOpenStateChangedCallback);

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com/eegeo/modalbackground/ModalBackgroundView");
			jclass uiClass = m_nativeState.LoadClass(env, strClassName);
			env->DeleteLocalRef(strClassName);

			m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
			jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/mobileexampleapp/MainActivity;)V");

			jobject instance = env->NewObject(
				m_uiViewClass,
				uiViewCtor,
				m_nativeState.activity
			);

			m_uiView = env->NewGlobalRef(instance);
		}

		ModalBackgroundViewController::~ModalBackgroundViewController()
		{
			ASSERT_UI_THREAD

			m_modalityModel.RemoveModalityChangedCallback(*m_pOpenStateChangedCallback);

			Eegeo_DELETE m_pOpenStateChangedCallback;

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
			env->CallVoidMethod(m_uiView, removeHudMethod);
			env->DeleteGlobalRef(m_uiView);
			env->DeleteGlobalRef(m_uiViewClass);
		}

		void ModalBackgroundViewController::OpenStateChangedCallback()
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID animateToIntermediateActivityState = env->GetMethodID(m_uiViewClass, "animateToIntermediateActivityState", "(F)V");
			env->CallVoidMethod(m_uiView, animateToIntermediateActivityState, m_modalityModel.GetModality());
		}
    }
}



