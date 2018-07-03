// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuPerformedSearchMessageHandler.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            SearchMenuPerformedSearchMessageHandler::SearchMenuPerformedSearchMessageHandler(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                                             Search::SdkModel::IAutocompleteSuggestionQueryPerformer& autocompleteSuggestionQueryPerformer,
                                                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                                                             Metrics::IMetricsService& metricsService)
            : m_searchQueryPerformer(searchQueryPerformer)
            , m_autocompleteSuggestionsQueryPerformer(autocompleteSuggestionQueryPerformer)
            , m_messageBus(messageBus)
            , m_metricsService(metricsService)
            , m_handlePerformedSearchMessageBinding(this, &SearchMenuPerformedSearchMessageHandler::OnPerformedSearchMessage)
            , m_handleSearchWithContextMessageBinding(this, &SearchMenuPerformedSearchMessageHandler::OnSearchWithContextMessage)
            , m_handleAutocompleteSuggestionsMessageBinding(this, &SearchMenuPerformedSearchMessageHandler::OnAutocompleteSuggestionsMessage)
            , m_handleAutocompleteSuggestionsCancelledMessageBinding(this, &SearchMenuPerformedSearchMessageHandler::OnAutocompleteSuggestionsCancelledMessage)
            {
                m_messageBus.SubscribeNative(m_handlePerformedSearchMessageBinding);
                m_messageBus.SubscribeNative(m_handleSearchWithContextMessageBinding);
                m_messageBus.SubscribeNative(m_handleAutocompleteSuggestionsMessageBinding);
                m_messageBus.SubscribeNative(m_handleAutocompleteSuggestionsCancelledMessageBinding);
            }

            SearchMenuPerformedSearchMessageHandler::~SearchMenuPerformedSearchMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handleAutocompleteSuggestionsCancelledMessageBinding);
                m_messageBus.UnsubscribeNative(m_handleAutocompleteSuggestionsMessageBinding);
                m_messageBus.UnsubscribeNative(m_handleSearchWithContextMessageBinding);
                m_messageBus.UnsubscribeNative(m_handlePerformedSearchMessageBinding);
            }

            void SearchMenuPerformedSearchMessageHandler::OnPerformedSearchMessage(const SearchMenuPerformedSearchMessage& message)
            {
                m_searchQueryPerformer.RemoveSearchQueryResults();
                m_metricsService.SetEvent("Search", "Search string", message.SearchQuery().c_str());
                m_searchQueryPerformer.RemoveSearchQueryResults();
                m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), message.IsTag(), message.IsInterior());
            }

            void SearchMenuPerformedSearchMessageHandler::OnSearchWithContextMessage(const SearchMenuSearchWithContextMessage& message)
            {
                m_metricsService.SetEvent("Search-with-context", "Search string", message.SearchQuery().c_str());

				const View::QueryContext& context = message.QueryContext();

				if (context.ClearPreviousResults())
				{
					m_searchQueryPerformer.RemoveSearchQueryResults();
				}

				if (context.UsesRadius())
				{
					if (context.UsesLocation())
					{
						m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), context.IsTag(), context.ShouldTryInterior(),
																  context.Location(), context.Radius());
					}
					else
					{
						m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), context.IsTag(), context.ShouldTryInterior(),
																  context.Radius());
					}
				}
				else
				{
					if (context.UsesLocation())
					{
						m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), context.IsTag(), context.ShouldTryInterior(),
																  context.Location());
					}
					else
					{
						m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), context.IsTag(), context.ShouldTryInterior());
					}
				}
            }

            void SearchMenuPerformedSearchMessageHandler::OnAutocompleteSuggestionsMessage(const AutocompleteSuggestionsMessage& message){
                m_autocompleteSuggestionsQueryPerformer.PerformSuggestionsQuery(message.SearchQuery());
            }

			void SearchMenuPerformedSearchMessageHandler::OnAutocompleteSuggestionsCancelledMessage(const AutocompleteSuggestionsCancelledMessage &message){
				m_autocompleteSuggestionsQueryPerformer.Cancel();
			}
        }
    }
}
