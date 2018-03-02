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
			, m_onCancelCallback(this, &SearchServices::OnCancel)
			, m_responseReceivedHandler(this, &SearchServices::OnSearchQueryResponseReceivedMessage)
			{
				m_searchProvider.InsertSearchPerformedCallback(m_onSearchCallback);
				m_searchProvider.InsertSearchCancelledCallback(m_onCancelCallback);

                m_messageBus.SubscribeUi(m_responseReceivedHandler);
            }

			SearchServices::~SearchServices()
			{
                m_messageBus.UnsubscribeUi(m_responseReceivedHandler);

				m_searchProvider.RemoveSearchCancelledCallback(m_onCancelCallback);
				m_searchProvider.RemoveSearchPerformedCallback(m_onSearchCallback);
			}

            void SearchServices::OnSearch(const std::string& searchQuery)
            {
				m_messageBus.Publish(SearchMenuPerformedSearchMessage(searchQuery, false, false));
            }

			void SearchServices::OnCancel()
			{
				// TO DO - cancel ongoing search
			}

            void SearchServices::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
				m_searchProvider.OnSearchResponseReceived(message.GetResults());
			}
		}
	}
}
