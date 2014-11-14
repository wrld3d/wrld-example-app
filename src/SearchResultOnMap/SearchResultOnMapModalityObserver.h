// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "ModalityChangedMessage.h"
#include "SearchResultOnMapScaleController.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapModalityObserver : private Eegeo::NonCopyable
		{
			SearchResultOnMapScaleController& m_searchResultOnMapScaleController;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			Eegeo::Helpers::TCallback1<SearchResultOnMapModalityObserver, const Modality::ModalityChangedMessage&> m_handlerBinding;

			void HandleReceivedModalityChangedMessage(const Modality::ModalityChangedMessage& message);

		public:
			SearchResultOnMapModalityObserver(SearchResultOnMapScaleController& searchResultOnMapScaleController,
			                                  ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~SearchResultOnMapModalityObserver();
		};
	}
}
