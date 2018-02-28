// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchServices.h"

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
			, m_responseReceivedHandler(this, &SearchServices::OnSearchQueryResponseReceivedMessage)
			{
				m_searchProvider.InsertSearchPerformedCallback(m_onSearchCallback);

                m_messageBus.SubscribeUi(m_responseReceivedHandler);
            }

			SearchServices::~SearchServices()
			{
                m_messageBus.UnsubscribeUi(m_responseReceivedHandler);

				m_searchProvider.RemoveSearchPerformedCallback(m_onSearchCallback);
			}

            void SearchServices::OnSearch(const std::string& searchQuery)
            {
				m_messageBus.Publish(SearchMenuPerformedSearchMessage(searchQuery, false, false));
            }

            void SearchServices::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
				const TSdkSearchResults& data = message.GetResults();

				m_searchResults.clear();

				for (TSdkSearchResults::const_iterator it = data.begin(); it != data.end(); it++)
					m_searchResults.push_back(it->GetJsonData());

				m_searchProvider.OnSearchResponseReceived(m_searchResults);
			}
		}
	}
}
