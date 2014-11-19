// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsViewController.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "IMyPinDetailsViewModel.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
		MyPinDetailsViewController::MyPinDetailsViewController(
				AndroidNativeState& nativeState,
				IMyPinDetailsViewModel& myPinDetailsViewModel)
		: m_nativeState(nativeState)
		, m_viewModel(myPinDetailsViewModel)
		, m_pOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<MyPinDetailsViewController>)(this, &MyPinDetailsViewController::Open))
		, m_pClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<MyPinDetailsViewController>)(this, &MyPinDetailsViewController::Close))
		{
			ASSERT_UI_THREAD

			m_viewModel.InsertOpenedCallback(*m_pOpenedCallback);
			m_viewModel.InsertClosedCallback(*m_pClosedCallback);

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com.eegeo.mypindetails.MyPinDetailsView");
			jclass uiClass = m_nativeState.LoadClass(env, strClassName);
			env->DeleteLocalRef(strClassName);

			m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
			jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/mobileexampleapp/MainActivity;J)V");

			jobject instance = env->NewObject(
				m_uiViewClass,
				uiViewCtor,
				m_nativeState.activity,
				(jlong)(this)
			);

			m_uiView = env->NewGlobalRef(instance);
		}

		MyPinDetailsViewController::~MyPinDetailsViewController()
		{
			ASSERT_UI_THREAD

			m_viewModel.RemoveOpenedCallback(*m_pOpenedCallback);
			m_viewModel.RemoveClosedCallback(*m_pClosedCallback);

			Eegeo_DELETE m_pOpenedCallback;
			Eegeo_DELETE m_pClosedCallback;

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
			env->CallVoidMethod(m_uiView, removeHudMethod);
			env->DeleteGlobalRef(m_uiView);
			env->DeleteGlobalRef(m_uiViewClass);
		}

		void MyPinDetailsViewController::Open()
		{
			ASSERT_UI_THREAD

			const MyPins::MyPinModel& myPinModel = m_viewModel.GetMyPinModel();

			if(!m_viewModel.TryAcquireReactorControl())
			{
				if(m_viewModel.IsOpen())
				{
					m_viewModel.Close();
				}
				return;
			}

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring titleStr = env->NewStringUTF(myPinModel.GetTitle().c_str());
			jstring descriptionStr = env->NewStringUTF(myPinModel.GetDescription().c_str());
			jstring imageStr = env->NewStringUTF(myPinModel.GetImagePath().c_str());

			jmethodID showDetailsMethod = env->GetMethodID(m_uiViewClass, "display", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
			env->CallVoidMethod(m_uiView, showDetailsMethod, titleStr, descriptionStr, imageStr);

			env->DeleteLocalRef(titleStr);
			env->DeleteLocalRef(descriptionStr);
			env->DeleteLocalRef(imageStr);
		}

		void MyPinDetailsViewController::Close()
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID dismissPoiInfo = env->GetMethodID(m_uiViewClass, "dismiss", "()V");
			env->CallVoidMethod(m_uiView, dismissPoiInfo);
		}

		void MyPinDetailsViewController::HandleCloseButtonPressed()
		{
			ASSERT_UI_THREAD

			m_viewModel.Close();
		}

    }
}
