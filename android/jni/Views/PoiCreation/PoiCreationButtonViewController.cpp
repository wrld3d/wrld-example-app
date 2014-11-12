// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationButtonViewController.h"
#include "IPoiCreationButtonViewModel.h"
#include "IPoiCreationModel.h"
#include "PoiCreationStage.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
    	PoiCreationButtonViewController::PoiCreationButtonViewController(
    			AndroidNativeState& nativeState,
    			PoiCreation::IPoiCreationModel& model,
  				PoiCreation::IPoiCreationButtonViewModel& viewModel
  			)
    	:m_nativeState(nativeState)
       	, m_model(model)
    	, m_viewModel(viewModel)
    	, m_pOnScreenStateChangedCallback(Eegeo_NEW((
    	    			Eegeo::Helpers::TCallback2<PoiCreationButtonViewController, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &PoiCreationButtonViewController::OnScreenStateChangedCallback))
    	{
			m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com.eegeo.poicreation.PoiCreationButtonView");
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

    	PoiCreationButtonViewController::~PoiCreationButtonViewController()
    	{
    		m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);

			Eegeo_DELETE m_pOnScreenStateChangedCallback;

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
			env->CallVoidMethod(m_uiView, removeHudMethod);
			env->DeleteGlobalRef(m_uiView);
			env->DeleteGlobalRef(m_uiViewClass);
    	}

    	void PoiCreationButtonViewController::Selected()
    	{
    		m_model.SetCreationStage(ExampleApp::PoiCreation::Ring);
    	}

    	void PoiCreationButtonViewController::OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState)
    	{
			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			if(m_viewModel.IsFullyOnScreen())
			{
				jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToActive", "()V");
				env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
			}
			else if (m_viewModel.IsFullyOffScreen())
			{
				jmethodID animateOffScreen = env->GetMethodID(m_uiViewClass, "animateToInactive", "()V");
				env->CallVoidMethod(m_uiView, animateOffScreen);
			}
			else
			{
				jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
				env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, onScreenState);
			}
    	}
    }
}
