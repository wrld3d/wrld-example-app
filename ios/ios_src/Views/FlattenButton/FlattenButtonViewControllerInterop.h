// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "FlattenButtonViewController.h"
#include "IFlattenButtonViewModel.h"
#include "NativeToUiMessageBus.h"
#include "Types.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "FlattenButtonModelStateChangedMessage.h"

namespace ExampleApp
{
	namespace FlattenButton
	{
		class FlattenButtonViewControllerInterop : private Eegeo::NonCopyable
		{
			FlattenButtonViewController* m_pController;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
			IFlattenButtonViewModel& m_viewModel;

			Eegeo::Helpers::TCallback1<FlattenButtonViewControllerInterop, const FlattenButtonModelStateChangedMessage&> m_flattenModelStateChangedCallback;
			Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

			void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
			{
				[m_pController handleScreenStateChanged:m_viewModel.OnScreenState()];
			}

			void OnFlattenModelStateChangedCallback(const FlattenButtonModelStateChangedMessage& message)
			{
				[m_pController handleModelStateChanged:message.IsFlattened()];
			}

		public:

			FlattenButtonViewControllerInterop(FlattenButtonViewController* pController,
			                                   ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
			                                   IFlattenButtonViewModel& viewModel)
				: m_pController(pController)
				, m_nativeToUiMessageBus(nativeToUiMessageBus)
				, m_viewModel(viewModel)
				, m_flattenModelStateChangedCallback(this, &FlattenButtonViewControllerInterop::OnFlattenModelStateChangedCallback)
				, m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<FlattenButtonViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &FlattenButtonViewControllerInterop::OnScreenStateChangedCallback))
			{
				m_nativeToUiMessageBus.Subscribe(m_flattenModelStateChangedCallback);
				m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
			}

			~FlattenButtonViewControllerInterop()
			{
				m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
				m_nativeToUiMessageBus.Unsubscribe(m_flattenModelStateChangedCallback);

				Eegeo_DELETE m_pOnScreenStateChangedCallback;
			}
		};
	}
}