// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ModalBackgroundView.h"
#include "ISearchQueryPerformer.h"
#include "ICallback.h"
#include "UiToNativeMessageBus.h"
#include "ModalityChangedMessage.h"

namespace ExampleApp
{
	namespace ModalBackground
	{
		class ModalBackgroundNativeModalityObserver : private Eegeo::NonCopyable
		{
			ModalBackgroundView& m_modalBackgroundView;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			Eegeo::Helpers::TCallback1<ModalBackgroundNativeModalityObserver, const Modality::ModalityChangedMessage&> m_handlerBinding;

			void HandleModalityChanged(const Modality::ModalityChangedMessage& message)
			{
				m_modalBackgroundView.SetAlpha(message.Modality());
			}

		public:
			ModalBackgroundNativeModalityObserver(
			    ModalBackgroundView& modalBackgroundView,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
				: m_modalBackgroundView(modalBackgroundView)
				, m_uiToNativeMessageBus(uiToNativeMessageBus)
				, m_handlerBinding(this, &ModalBackgroundNativeModalityObserver::HandleModalityChanged)
			{
				m_uiToNativeMessageBus.Subscribe(m_handlerBinding);
			}

			~ModalBackgroundNativeModalityObserver()
			{
				m_uiToNativeMessageBus.Unsubscribe(m_handlerBinding);
			}
		};
	}
}
