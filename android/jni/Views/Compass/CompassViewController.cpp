// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "CompassViewController.h"
#include "ICompassModel.h"
#include "ICompassViewModel.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace Compass
    {
    	CompassViewController::CompassViewController(
    			AndroidNativeState& nativeState,
        		Compass::ICompassModel& model,
				ExampleApp::Compass::ICompassViewModel& viewModel)
    	: m_nativeState(nativeState)
        , m_model(model)
        , m_viewModel(viewModel)
        , m_pGpsModelChangedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<CompassViewController>)(this, &CompassViewController::OnGpsModeChanged))
    	, m_pUpdateCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<CompassViewController, float>))(this, &CompassViewController::OnHeadingUpdated))
    	, m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<CompassViewController, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &CompassViewController::OnScreenStateChangedCallback))
        {
            m_model.InsertGpsModeChangedCallback(*m_pGpsModelChangedCallback);
            m_viewModel.InsertUpdateCallback(*m_pUpdateCallback);
            m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);

    		AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com.eegeo.compass.CompassView");
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

    	CompassViewController::~CompassViewController()
    	{
            m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
            m_viewModel.RemoveUpdateCallback(*m_pUpdateCallback);
            m_model.RemoveGpsModeChangedCallback(*m_pGpsModelChangedCallback);

            Eegeo_DELETE m_pOnScreenStateChangedCallback;
            Eegeo_DELETE m_pUpdateCallback;
            Eegeo_DELETE m_pGpsModelChangedCallback;

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
			env->CallVoidMethod(m_uiView, removeHudMethod);
			env->DeleteGlobalRef(m_uiView);
			env->DeleteGlobalRef(m_uiViewClass);
    	}

    	void CompassViewController::HandleClick()
    	{
    		m_model.CycleToNextGpsMode();
    	}

    	void CompassViewController::OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState)
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

		void CompassViewController::OnHeadingUpdated(float& headingAngleRadians)
		{
			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID updateHeading = env->GetMethodID(m_uiViewClass, "updateHeading", "(F)V");
			env->CallVoidMethod(m_uiView, updateHeading, headingAngleRadians);
		}

		void CompassViewController::OnGpsModeChanged()
		{
			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			std::string jniMethodName;

		    switch(m_model.GetGpsMode())
		    {
		        case ExampleApp::Compass::GpsMode::GpsDisabled:
		        {
		        	jniMethodName = "showGpsDisabledView";
		        }break;

		        case ExampleApp::Compass::GpsMode::GpsFollow:
		        {
		        	jniMethodName = "showGpsFollowView";
		        }break;

		        case ExampleApp::Compass::GpsMode::GpsCompassMode:
		        {
		        	jniMethodName = "showGpsCompassModeView";
		        }break;

		        default:
		        {
		            Eegeo_ASSERT(false, "Invalid GPS mode\n");
		        }break;
		    }

			jmethodID jniMethod = env->GetMethodID(m_uiViewClass, jniMethodName.c_str(), "()V");
			env->CallVoidMethod(m_uiView, jniMethod);
		}
    }
}

