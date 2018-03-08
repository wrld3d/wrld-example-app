// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "ISearchProvider.h"
#include "SearchServicesResult.h"
#include "SearchResultModel.h"
#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "SearchQueryResponseReceivedMessage.h"

#include <vector>

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			class SearchServices: private Eegeo::NonCopyable
			{
			private:
				ISearchProvider& m_searchProvider;
				ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<SearchServices, const std::string&> m_onSearchCallback;
				Eegeo::Helpers::TCallback2<SearchServices, const std::string&, const QueryContext&> m_onSearchRefreshCallback;
				Eegeo::Helpers::TCallback0<SearchServices> m_onCancelCallback;
				Eegeo::Helpers::TCallback1<SearchServices, const Search::SearchQueryResponseReceivedMessage&> m_responseReceivedHandler;

				typedef Search::SdkModel::SearchResultModel TSdkSearchResult;

				ISearchProvider::TSearchResults m_searchResults;

			public:
				SearchServices(ISearchProvider& searchProvider,
							   ExampleAppMessaging::TMessageBus& messageBus);
				~SearchServices();

				int GetResultOriginalIndexFromCurrentIndex(int index) const;
				const SearchMenu::View::SearchServicesResult::TSdkSearchResult& GetSdkSearchResultByIndex(int index) const;

			private:
				void OnSearch(const std::string& searchQuery);
				void OnSearchRefresh(const std::string& searchQuery, const QueryContext& context);
				void OnCancel();

				void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);

				int CountResultsShown(const std::vector<TSdkSearchResult>& sdkResults);
				void HandleSpecialCases(const TSdkSearchResult& sdkResult,
										std::string& description, std::string& iconName);

				static std::string GetMeetingRoomAvailablityIcon(std::string availability);
			};
		}
	}
}
