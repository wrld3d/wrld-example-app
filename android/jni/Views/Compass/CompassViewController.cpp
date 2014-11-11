// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "CompassViewController.h"
#include "ICompassModel.h"
#include "ICompassViewModel.h"
#include "IScreenControlViewModel.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "CompassViewCycledMessage.h"

namespace ExampleApp
{
    namespace Compass
    {
    	CompassViewController::CompassViewController(
    			AndroidNativeState& nativeState,
				ExampleApp::Compass::ICompassViewModel& viewModel,
                ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
				ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
    	: m_nativeState(nativeState)
        , m_viewModel(viewModel)
    	, m_uiToNativeMessageBus(uiToNativeMessageBus)
    	, m_nativeToUiMessageBus(nativeToUiMessageBus)
    	, m_onScreenStateChangedCallback(this, &CompassViewController::OnScreenStateChangedCallback)
    	, m_modeChangedCallback(this, &CompassViewController::OnCompassModeChanged)
    	, m_headingChangedCallback(this, &CompassViewController::OnCompassHeadingChanged)
        {
    		ASSERT_UI_THREAD

            m_viewModel.InsertOnScreenStateChangedCallback(m_onScreenStateChangedCallback);

    		m_nativeToUiMessageBus.Subscribe(m_modeChangedCallback);
    		m_nativeToUiMessageBus.Subscribe(m_headingChangedCallback);

    		AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com.eegeo.compass.CompassView");
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

    	CompassViewController::~CompassViewController()
    	{
    		ASSERT_UI_THREAD

            m_viewModel.RemoveOnScreenStateChangedCallback(m_onScreenStateChangedCallback);

    		m_nativeToUiMessageBus.Unsubscribe(m_modeChangedCallback);
    		m_nativeToUiMessageBus.Unsubscribe(m_headingChangedCallback);

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
			env->CallVoidMethod(m_uiView, removeHudMethod);
			env->DeleteGlobalRef(m_uiView);
			env->DeleteGlobalRef(m_uiViewClass);
    	}

    	void CompassViewController::HandleClick()
    	{
    		ASSERT_UI_THREAD

    		m_uiToNativeMessageBus.Publish(CompassViewCycledMessage());
    	}

    	void CompassViewController::OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState)
    	{
    		ASSERT_UI_THREAD

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

        void CompassViewController::OnCompassHeadingChanged(const CompassHeadingUpdateMessage& message)
		{
			ASSERT_UI_THREAD

			float headingAngleRadians = message.GetHeadingRadians();
			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID updateHeading = env->GetMethodID(m_uiViewClass, "updateHeading", "(F)V");
			env->CallVoidMethod(m_uiView, updateHeading, headingAngleRadians);
		}

        void CompassViewController::OnCompassModeChanged(const CompassModeChangedMessage& message)
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			std::string jniMethodName;

		    switch(message.GetMode())
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

