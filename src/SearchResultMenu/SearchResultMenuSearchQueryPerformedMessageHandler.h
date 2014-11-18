// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "NativeToUiMessageBus.h"
#include "ICallback.h"
#include "SearchQueryPerformedMessage.h"
#include "ISearchResultMenuViewModel.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		class SearchResultMenuSearchQueryPerformedMessageHandler : private Eegeo::NonCopyable
		{
			SearchResultMenu::ISearchResultMenuViewModel& m_searchResultMenuViewModel;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
			Eegeo::Helpers::TCallback1<SearchResultMenuSearchQueryPerformedMessageHandler, const Search::SearchQueryPerformedMessage&> m_handlerBinding;

			void HandleReceivedSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message);

		public:
			SearchResultMenuSearchQueryPerformedMessageHandler(
			    SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel,
			    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~SearchResultMenuSearchQueryPerformedMessageHandler();
		};
	}
}
