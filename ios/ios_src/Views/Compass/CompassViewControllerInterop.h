// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "CompassViewController.h"
#include "CompassViewModel.h"
#include "Types.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "CompassModeChangedMessage.h"
#include "CompassHeadingUpdateMessage.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
	namespace Compass
	{
		class CompassViewControllerInterop : private Eegeo::NonCopyable
		{
			CompassViewController* m_pController;
			ICompassViewModel& m_viewModel;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

			Eegeo::Helpers::TCallback2<CompassViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float> m_onScreenStateChangedCallback;
			Eegeo::Helpers::TCallback1<CompassViewControllerInterop, const CompassModeChangedMessage&> m_modeChangedCallback;
			Eegeo::Helpers::TCallback1<CompassViewControllerInterop, const CompassHeadingUpdateMessage&> m_headingChangedCallback;

			void OnCompassModeChanged(const CompassModeChangedMessage& message)
			{
				[m_pController handleGpsModeChanged:message.GetMode()];
			}

			void OnCompassHeadingChanged(const CompassHeadingUpdateMessage& message)
			{
				[m_pController updateHeading:message.GetHeadingRadians()];
			}

			void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
			{
				[m_pController handleScreenStateChanged:m_viewModel.OnScreenState()];
			}

		public:

			CompassViewControllerInterop(CompassViewController* pController,
			                             ICompassViewModel& viewModel,
			                             ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
				: m_pController(pController)
				, m_viewModel(viewModel)
				, m_nativeToUiMessageBus(nativeToUiMessageBus)
				, m_onScreenStateChangedCallback(this, &CompassViewControllerInterop::OnScreenStateChangedCallback)
				, m_modeChangedCallback(this, &CompassViewControllerInterop::OnCompassModeChanged)
				, m_headingChangedCallback(this, &CompassViewControllerInterop::OnCompassHeadingChanged)
			{
				m_nativeToUiMessageBus.Subscribe(m_modeChangedCallback);
				m_nativeToUiMessageBus.Subscribe(m_headingChangedCallback);
				m_viewModel.InsertOnScreenStateChangedCallback(m_onScreenStateChangedCallback);
			}

			~CompassViewControllerInterop()
			{
				m_viewModel.RemoveOnScreenStateChangedCallback(m_onScreenStateChangedCallback);
				m_nativeToUiMessageBus.Unsubscribe(m_modeChangedCallback);
				m_nativeToUiMessageBus.Unsubscribe(m_headingChangedCallback);
			}
		};

	}
}
