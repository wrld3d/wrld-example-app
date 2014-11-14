// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsViewController.h"
#include "MyPinCreationModel.h"
#include "MyPinCreationDetailsViewModel.h"
#include "MyPinCreationStage.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "MyPinCreationViewStateChangedMessage.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
    	MyPinCreationDetailsViewController::MyPinCreationDetailsViewController(
            	AndroidNativeState& nativeState,
            	MyPinCreation::IMyPinCreationModel& model,
            	MyPinCreationDetails::IMyPinCreationDetailsViewModel& viewModel,
				ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
            )
    	: m_nativeState(nativeState)
    	, m_model(model)
    	, m_viewModel(viewModel)
    	, m_uiToNativeMessageBus(uiToNativeMessageBus)
    	, m_pOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<MyPinCreationDetailsViewController>)(this, &MyPinCreationDetailsViewController::Open))
    	, m_pClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<MyPinCreationDetailsViewController>)(this, &MyPinCreationDetailsViewController::Close))
    	{
    		ASSERT_UI_THREAD

    		m_viewModel.InsertOpenedCallback(*m_pOpenedCallback);
    		m_viewModel.InsertClosedCallback(*m_pClosedCallback);

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com.eegeo.mypincreationdetails.MyPinCreationDetailsView");
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

    	MyPinCreationDetailsViewController::~MyPinCreationDetailsViewController()
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

    	void MyPinCreationDetailsViewController::Open()
    	{
    		ASSERT_UI_THREAD

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

			jmethodID showDetailsMethod = env->GetMethodID(m_uiViewClass, "show", "()V");
			env->CallVoidMethod(m_uiView, showDetailsMethod);
    	}

    	void MyPinCreationDetailsViewController::Close()
    	{
    		ASSERT_UI_THREAD

    		AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID dismissDetailsMethod = env->GetMethodID(m_uiViewClass, "dismiss", "()V");
			env->CallVoidMethod(m_uiView, dismissDetailsMethod);
    	}

    	void MyPinCreationDetailsViewController::HandleCloseButtonPressed()
    	{
    		ASSERT_UI_THREAD

    		m_uiToNativeMessageBus.Publish(MyPinCreation::MyPinCreationViewStateChangedMessage(ExampleApp::MyPinCreation::Inactive));
    		m_viewModel.Close();
    	}

    	void MyPinCreationDetailsViewController::HandleConfirmButtonPressed(
    			std::string title,
    			std::string description,
    			std::string image,
    			bool shouldShare)
    	{
    		ASSERT_UI_THREAD



    		Eegeo_TTY("Got some info for ya: %s - %s - %s - %d", title.c_str(), description.c_str(), image.c_str(), shouldShare);

			m_viewModel.Close();
    	}
    }
}
