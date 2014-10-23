// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageViewController.h"
#include "Types.h"
#include "IAboutPageViewModel.h"
#include "IAboutPageModel.h"

namespace ExampleApp
{
    namespace AboutPage
    {
		AboutPageViewController::AboutPageViewController(
			AndroidNativeState& nativeState,
            AboutPage::IAboutPageModel& aboutPageModel,
			IAboutPageViewModel& aboutPageViewModel
		)
		: m_nativeState(nativeState)
		, m_aboutPageModel(aboutPageModel)
		, m_aboutPageViewModel(aboutPageViewModel)
        , m_pAboutPageOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<AboutPageViewController>)(this, &AboutPageViewController::AboutPageOpenedCallback))
        , m_pAboutPageClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<AboutPageViewController>)(this, &AboutPageViewController::AboutPageClosedCallback))
		{
			m_aboutPageViewModel.InsertOpenedCallback(*m_pAboutPageOpenedCallback);
			m_aboutPageViewModel.InsertClosedCallback(*m_pAboutPageClosedCallback);

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com/eegeo/aboutpageview/AboutPageView");
			jclass uiClass = m_nativeState.LoadClass(env, strClassName);
			env->DeleteLocalRef(strClassName);

			m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
			jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/MainActivity;J)V");

			jobject instance = env->NewObject(
				m_uiViewClass,
				uiViewCtor,
				m_nativeState.activity,
				(jlong)(this)
			);

			m_uiView = env->NewGlobalRef(instance);
		}

		AboutPageViewController::~AboutPageViewController()
		{
			m_aboutPageViewModel.RemoveOpenedCallback(*m_pAboutPageOpenedCallback);
			m_aboutPageViewModel.RemoveClosedCallback(*m_pAboutPageClosedCallback);

            Eegeo_DELETE m_pAboutPageOpenedCallback;
            Eegeo_DELETE m_pAboutPageClosedCallback;

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
			env->CallVoidMethod(m_uiView, removeHudMethod);
			env->DeleteGlobalRef(m_uiView);
			env->DeleteGlobalRef(m_uiViewClass);
		}

		void AboutPageViewController::HandleCloseButtonPressed()
		{
			if(m_aboutPageViewModel.IsOpen())
			{
				m_aboutPageViewModel.Close();
			}
		}

		void AboutPageViewController::AboutPageOpenedCallback()
		{
			if(!m_aboutPageViewModel.TryAcquireReactorControl())
			{
				if(m_aboutPageViewModel.IsOpen())
				{
					m_aboutPageViewModel.Close();
				}
				return;
			}

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring aboutStr = env->NewStringUTF(m_aboutPageModel.GetAboutText().c_str());
			jstring platformHashStr = env->NewStringUTF(m_aboutPageModel.GetPlatformHash().c_str());
			jstring platformVersionStr = env->NewStringUTF(m_aboutPageModel.GetPlatformVersion().c_str());

			jmethodID displayPoiInfo = env->GetMethodID(m_uiViewClass, "displayPoiInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
			env->CallVoidMethod(m_uiView, displayPoiInfo, aboutStr, platformHashStr, platformVersionStr);

			env->DeleteLocalRef(platformVersionStr);
			env->DeleteLocalRef(platformHashStr);
			env->DeleteLocalRef(aboutStr);
		}

		void AboutPageViewController::AboutPageClosedCallback()
		{
			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID dismissPoiInfo = env->GetMethodID(m_uiViewClass, "dismissAboutPage", "()V");
			env->CallVoidMethod(m_uiView, dismissPoiInfo);
		}
    }
}
