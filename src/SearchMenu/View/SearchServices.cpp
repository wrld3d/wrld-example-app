// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchServices.h"
//#include "S_S_SSearchConstants.h"
//#include "S_S_SSearchParser.h"
#include "SearchQuery.h"
#include "AutocompleteSuggestionsMessage.h"

#include <algorithm>

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			SearchServices::SearchServices(ISearchProvider& searchProvider,
										   ExampleAppMessaging::TMessageBus& messageBus)
			: m_searchProvider(searchProvider)
			, m_messageBus(messageBus)
			, m_onSearchCallback(this, &SearchServices::OnSearch)
			, m_onSearchWithContextCallback(this, &SearchServices::OnSearchWithContext)
            , m_onAutocompleteSuggestionsCallback(this, &SearchServices::OnAutocompleteSuggestions)
			, m_onCancelCallback(this, &SearchServices::OnCancel)
			, m_responseReceivedHandler(this, &SearchServices::OnSearchQueryResponseReceivedMessage)
			, m_autocompleteSuggestionsResponseReceivedHandler(this, &SearchServices::OnAutocompleteSuggestionsResponseReceivedMessage)

			{
				m_searchProvider.InsertSearchPerformedCallback(m_onSearchCallback);
				m_searchProvider.InsertSearchWithContextCallback(m_onSearchWithContextCallback);
				m_searchProvider.InsertSearchCancelledCallback(m_onCancelCallback);
				m_searchProvider.InsertAutocompleteSuggestionsCallback(m_onAutocompleteSuggestionsCallback);

                m_messageBus.SubscribeUi(m_responseReceivedHandler);
				m_messageBus.SubscribeUi(m_autocompleteSuggestionsResponseReceivedHandler);
            }

			SearchServices::~SearchServices()
			{
				m_messageBus.UnsubscribeUi(m_autocompleteSuggestionsResponseReceivedHandler);
				m_messageBus.UnsubscribeUi(m_responseReceivedHandler);

				m_searchProvider.RemoveAutocompleteSuggestionsCallback(m_onAutocompleteSuggestionsCallback);
				m_searchProvider.RemoveSearchCancelledCallback(m_onCancelCallback);
				m_searchProvider.RemoveSearchWithContextCallback(m_onSearchWithContextCallback);
				m_searchProvider.RemoveSearchPerformedCallback(m_onSearchCallback);
			}

			int SearchServices::GetResultOriginalIndexFromCurrentIndex(int index) const
			{
				return m_searchResults[index].GetOriginalIndex();
			}

			const SearchMenu::View::SearchServicesResult::TSdkSearchResult& SearchServices::GetSdkSearchResultByIndex(int index) const
			{
				return m_searchResults[index].GetSdkSearchResult();
			}

			void SearchServices::OnAutocompleteSuggestions(const std::string& searchQuery){
				 m_messageBus.Publish(AutocompleteSuggestionsMessage(searchQuery));
			}

            void SearchServices::OnSearch(const std::string& searchQuery)
            {
				m_messageBus.Publish(SearchMenuPerformedSearchMessage(searchQuery, false, false));
            }

			void SearchServices::OnSearchWithContext(const std::string& searchQuery, const QueryContext& context)
			{
				std::string effectiveQuery = context.IsTag() ? context.TagText() : searchQuery;

				m_messageBus.Publish(SearchMenuSearchWithContextMessage(effectiveQuery, context));
			}

			void SearchServices::OnCancel()
			{
				m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
			}

			void SearchServices::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
				const std::vector<TSdkSearchResult>& sdkResults = message.GetResults();

				m_searchResults.clear();
				m_searchResults.reserve(sdkResults.size());

				for (std::vector<TSdkSearchResult>::const_iterator it = sdkResults.begin(); it != sdkResults.end(); it++)
				{
					std::string name = it->GetTitle();
					std::string desc = it->GetSubtitle();
					std::string icon = it->GetIconKey();

					//HandleSpecialCases(*it, desc, icon);

					m_searchResults.push_back(SearchServicesResult(name, desc, icon,
																   static_cast<int>(std::distance(sdkResults.begin(), it)),
																   *it));
				}

				std::stable_sort(m_searchResults.begin(), m_searchResults.end());

				m_searchProvider.OnSearchResponseReceived(m_searchResults);
			}

			void SearchServices::OnAutocompleteSuggestionsResponseReceivedMessage(const Search::AutocompleteSuggestionsReceivedMessage& message){

				const std::vector<TSdkSearchResult>& sdkResults = message.GetResults();

				m_suggestionResults.clear();
				m_suggestionResults.reserve(sdkResults.size());

				for (std::vector<TSdkSearchResult>::const_iterator it = sdkResults.begin(); it != sdkResults.end(); it++)
				{
					std::string name = it->GetTitle();
					std::string desc = it->GetSubtitle();
					std::string icon = it->GetIconKey();

					m_suggestionResults.push_back(SearchServicesResult(name, desc, icon,
					                                                   static_cast<int>(std::distance(sdkResults.begin(), it)),
					                                                   *it));
				}

				m_searchProvider.OnAutocompleteSuggestionsResponseReceived(m_suggestionResults);
			}
		}
	}
}
