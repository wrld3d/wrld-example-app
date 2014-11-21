// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultsClearMessage.h"
#include "Search.h"
#include "ICallback.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
	namespace Search
	{
		class SearchResultsClearMessageHandler : private Eegeo::NonCopyable
		{
			ISearchQueryPerformer& m_searchQueryPerformer;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			Eegeo::Helpers::TCallback1<SearchResultsClearMessageHandler, const SearchResultsClearMessage&> m_handlerBinding;

			void HandleReceivedSearchResultsClearMessage(const SearchResultsClearMessage& message);

		public:
			SearchResultsClearMessageHandler(
				ISearchQueryPerformer& searchQueryPerformer,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~SearchResultsClearMessageHandler();
		};
	}
}
