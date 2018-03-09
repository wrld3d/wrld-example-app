// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuPerformedSearchMessageHandler.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            SearchMenuPerformedSearchMessageHandler::SearchMenuPerformedSearchMessageHandler(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                                                             Metrics::IMetricsService& metricsService)
            : m_searchQueryPerformer(searchQueryPerformer)
            , m_messageBus(messageBus)
            , m_metricsService(metricsService)
            , m_handlePerformedSearchMessageBinding(this, &SearchMenuPerformedSearchMessageHandler::OnPerformedSearchMessage)
            , m_handleRefreshedSearchMessageBinding(this, &SearchMenuPerformedSearchMessageHandler::OnRefreshedSearchMessage)
            {
                m_messageBus.SubscribeNative(m_handlePerformedSearchMessageBinding);
                m_messageBus.SubscribeNative(m_handleRefreshedSearchMessageBinding);
            }

            SearchMenuPerformedSearchMessageHandler::~SearchMenuPerformedSearchMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handleRefreshedSearchMessageBinding);
                m_messageBus.UnsubscribeNative(m_handlePerformedSearchMessageBinding);
            }

            void SearchMenuPerformedSearchMessageHandler::OnPerformedSearchMessage(const SearchMenuPerformedSearchMessage& message)
            {
                m_metricsService.SetEvent("Search", "Search string", message.SearchQuery().c_str());
                m_searchQueryPerformer.RemoveSearchQueryResults();
                m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), message.IsTag(), message.IsInterior(), message.ShouldZoomToBuildingsView());
            }

            void SearchMenuPerformedSearchMessageHandler::OnRefreshedSearchMessage(const SearchMenuRefreshedSearchMessage& message)
            {
                m_metricsService.SetEvent("Refresh search", "Search string", message.SearchQuery().c_str());
                m_searchQueryPerformer.RemoveSearchQueryResults();
                m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), message.IsTag(), message.IsInterior(), message.ShouldZoomToBuildingsView(),
                                                          message.Location(), message.Radius());
            }
        }
    }
}
