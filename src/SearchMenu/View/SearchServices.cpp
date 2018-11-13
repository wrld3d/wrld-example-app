// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchServices.h"
#include "SearchQuery.h"
#include "AutocompleteSuggestionsMessage.h"
#include "AutocompleteSuggestionsCancelledMessage.h"
#include "ISearchResultsRepository.h"

#include <algorithm>

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			SearchServices::SearchServices(ISearchProvider& searchProvider,
										   ISearchResultsRepository& searchResultsRepository,
										   ISearchResultsRepository& suggestionsRepository,
                                           ExampleApp::SearchMenu::View::ISearchWidgetView& searchWidgetView,
										   ExampleAppMessaging::TMessageBus& messageBus)
			: m_searchProvider(searchProvider)
			, m_searchResultsRepository(searchResultsRepository)
			, m_suggestionsRepository(suggestionsRepository)
			, m_messageBus(messageBus)
			, m_onSearchCallback(this, &SearchServices::OnSearch)
			, m_onSearchWithContextCallback(this, &SearchServices::OnSearchWithContext)
            , m_onAutocompleteSuggestionsCallback(this, &SearchServices::OnAutocompleteSuggestions)
			, m_onCancelCallback(this, &SearchServices::OnCancel)
			, m_responseReceivedHandler(this, &SearchServices::OnSearchQueryResponseReceivedMessage)
			, m_autocompleteSuggestionsResponseReceivedHandler(this, &SearchServices::OnAutocompleteSuggestionsResponseReceivedMessage)
			, m_onCancelSuggestions(this, &SearchServices::OnCancelSuggestions)
            , m_searchWidgetView(searchWidgetView)
            , m_onSearchbarChangedCallback(this, &SearchServices::OnSearchbarTextChanged)
            , m_rerunLastTagSearch(false)
            , m_lastSearchContext(false, false, "", false)

			{
				m_searchProvider.InsertSearchPerformedCallback(m_onSearchCallback);
				m_searchProvider.InsertSearchWithContextCallback(m_onSearchWithContextCallback);
				m_searchProvider.InsertSearchCancelledCallback(m_onCancelCallback);
				m_searchProvider.InsertSuggestionsCancelledCallback(m_onCancelSuggestions);
				m_searchProvider.InsertAutocompleteSuggestionsCallback(m_onAutocompleteSuggestionsCallback);
                m_searchWidgetView.InsertSearchbarTextChangedCallback(m_onSearchbarChangedCallback);

                m_messageBus.SubscribeUi(m_responseReceivedHandler);
				m_messageBus.SubscribeUi(m_autocompleteSuggestionsResponseReceivedHandler);
            }

			SearchServices::~SearchServices()
			{
				m_messageBus.UnsubscribeUi(m_autocompleteSuggestionsResponseReceivedHandler);
				m_messageBus.UnsubscribeUi(m_responseReceivedHandler);

                m_searchWidgetView.RemoveSearchbarTextChangedCallback(m_onSearchbarChangedCallback);
				m_searchProvider.RemoveAutocompleteSuggestionsCallback(m_onAutocompleteSuggestionsCallback);
				m_searchProvider.RemoveSuggestionsCancelledCallback(m_onCancelSuggestions);
				m_searchProvider.RemoveSearchCancelledCallback(m_onCancelCallback);
				m_searchProvider.RemoveSearchWithContextCallback(m_onSearchWithContextCallback);
				m_searchProvider.RemoveSearchPerformedCallback(m_onSearchCallback);
			}
            
            void SearchServices::OnSearchbarTextChanged(const std::string& newText)
            {
                m_rerunLastTagSearch = false;
            }

			void SearchServices::OnAutocompleteSuggestions(const std::string& searchQuery)
            {
				 m_messageBus.Publish(AutocompleteSuggestionsMessage(searchQuery));
			}

            void SearchServices::OnSearch(const std::string& searchQuery)
            {
                if(m_rerunLastTagSearch)
                {
                    OnSearchWithContext(searchQuery, m_lastSearchContext);
                }
                else
                {
                    m_messageBus.Publish(SearchMenuPerformedSearchMessage(searchQuery, false, false));
                }
            }

			void SearchServices::OnSearchWithContext(const std::string& searchQuery, const QueryContext& context)
			{
                bool samePreviousSearchText = context.TagText() == m_lastSearchContext.TagText();
                m_lastSearchContext = context;
                
				std::string effectiveQuery = context.IsTag() ? context.TagText() : searchQuery;
                
                m_rerunLastTagSearch = context.IsTag() && samePreviousSearchText;

				m_messageBus.Publish(SearchMenuSearchWithContextMessage(effectiveQuery, context));
			}

			void SearchServices::OnCancel()
			{
				m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
			}

			void SearchServices::OnCancelSuggestions()
			{
				m_messageBus.Publish(AutocompleteSuggestionsCancelledMessage());
			}

			void SearchServices::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
				m_searchResultsRepository.SetResults(message.GetResults());
				m_searchProvider.OnSearchResponseReceived(message.DidSucceed(), m_searchResultsRepository.GetResults());
			}

			void SearchServices::OnAutocompleteSuggestionsResponseReceivedMessage(const Search::AutocompleteSuggestionsReceivedMessage& message)
			{
				m_suggestionsRepository.SetResults(message.GetResults());
				m_searchProvider.OnAutocompleteSuggestionsResponseReceived(message.DidSucceed(), m_suggestionsRepository.GetResults());
			}
		}
	}
}
