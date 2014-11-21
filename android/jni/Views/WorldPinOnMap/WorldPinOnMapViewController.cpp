// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinOnMapViewController.h"
#include "Types.h"
#include "IModalityModel.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "IModalityModel.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		WorldPinOnMapViewController::WorldPinOnMapViewController(
		    AndroidNativeState& nativeState,
		    IWorldPinInFocusViewModel& worldPinInFocusViewModel,
		    ScreenControlViewModel::IScreenControlViewModel& worldPinScreenControlViewModel,
		    const Modality::IModalityModel& modalityModel,
		    float pinDiameter
		)
			: m_nativeState(nativeState)
			, m_worldPinInFocusViewModel(worldPinInFocusViewModel)
			, m_worldPinScreenControlViewModel(worldPinScreenControlViewModel)
			, m_modalityModel(modalityModel)
			, m_worldPinOnMapFocusOpenedCallback(this, &WorldPinOnMapViewController::WorldPinOnMapFocusOpenedCallback)
			, m_worldPinOnMapFocusClosedCallback(this, &WorldPinOnMapViewController::WorldPinOnMapFocusClosedCallback)
			, m_worldPinOnMapFocusUpdatedCallback(this, &WorldPinOnMapViewController::WorldPinOnMapFocusUpdatedCallback)
			, m_screenStateChangedCallback(this, &WorldPinOnMapViewController::ScreenStateChangedCallback)
			, m_pinOffset(pinDiameter / 2.f)
		{
			ASSERT_UI_THREAD

			m_worldPinInFocusViewModel.InsertOpenedCallback(m_worldPinOnMapFocusOpenedCallback);
			m_worldPinInFocusViewModel.InsertClosedCallback(m_worldPinOnMapFocusClosedCallback);
			m_worldPinInFocusViewModel.InsertUpdateCallback(m_worldPinOnMapFocusUpdatedCallback);
			m_worldPinScreenControlViewModel.InsertOnScreenStateChangedCallback(m_screenStateChangedCallback);

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com/eegeo/worldpinonmapview/WorldPinOnMapView");
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

			if(m_worldPinInFocusViewModel.IsOpen())
			{
				WorldPinOnMapFocusOpenedCallback();
			}
			else
			{
				WorldPinOnMapFocusClosedCallback();
			}
		}

			WorldPinOnMapViewController::~WorldPinOnMapViewController()
		{
			ASSERT_UI_THREAD

			m_worldPinScreenControlViewModel.RemoveOnScreenStateChangedCallback(m_screenStateChangedCallback);
			m_worldPinInFocusViewModel.RemoveUpdateCallback(m_worldPinOnMapFocusUpdatedCallback);
			m_worldPinInFocusViewModel.RemoveOpenedCallback(m_worldPinOnMapFocusOpenedCallback);
			m_worldPinInFocusViewModel.RemoveClosedCallback(m_worldPinOnMapFocusClosedCallback);

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
			env->CallVoidMethod(m_uiView, removeHudMethod);
			env->DeleteGlobalRef(m_uiView);
			env->DeleteGlobalRef(m_uiViewClass);
		}

		void WorldPinOnMapViewController::HandleWorldPinOnMapClicked()
		{
			ASSERT_UI_THREAD

			if(m_worldPinInFocusViewModel.IsOpen())
			{
				m_worldPinInFocusViewModel.SelectFocussedResult();
			}
		}

		void WorldPinOnMapViewController::WorldPinOnMapFocusOpenedCallback()
		{
			ASSERT_UI_THREAD

			const Eegeo::v2& location = m_worldPinInFocusViewModel.ScreenLocation();
			float offsetY = location.y - m_pinOffset;

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			const WorldPinsInFocusModel& worldPinsInFocusModel = m_worldPinInFocusViewModel.GetWorldPinsInFocusModel();
			jstring titleStr = env->NewStringUTF(worldPinsInFocusModel.GetTitle().c_str());
			jstring detailsStr = env->NewStringUTF(worldPinsInFocusModel.GetSubtitle().c_str());

			jmethodID showAtScreenLocation = env->GetMethodID(m_uiViewClass, "showAtScreenLocation", "(Ljava/lang/String;Ljava/lang/String;FFF)V");
			env->CallVoidMethod(m_uiView, showAtScreenLocation, titleStr, detailsStr, location.x, offsetY, 1.f - m_modalityModel.GetModality());

			env->DeleteLocalRef(titleStr);
			env->DeleteLocalRef(detailsStr);
		}

		void WorldPinOnMapViewController::WorldPinOnMapFocusClosedCallback()
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID dismiss = env->GetMethodID(m_uiViewClass, "dismiss", "()V");
			env->CallVoidMethod(m_uiView, dismiss);
		}

		void WorldPinOnMapViewController::WorldPinOnMapFocusUpdatedCallback()
		{
			ASSERT_UI_THREAD

			const Eegeo::v2& location = m_worldPinInFocusViewModel.ScreenLocation();
			float offsetY = location.y - m_pinOffset;

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID updateScreenLocation = env->GetMethodID(m_uiViewClass, "updateScreenLocation", "(FF)V");
			env->CallVoidMethod(m_uiView, updateScreenLocation, location.x, offsetY);
		}

		void WorldPinOnMapViewController::ScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& screenControlViewModel, float& screenState)
		{
			ASSERT_UI_THREAD

			if(m_worldPinInFocusViewModel.IsOpen())
			{
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID updateScreenVisibility = env->GetMethodID(m_uiViewClass, "updateScreenVisibility", "(F)V");
				env->CallVoidMethod(m_uiView, updateScreenVisibility, screenState);
			}
		}
	}
}
