// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuPerformedSearchMessageHandler.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            SearchMenuPerformedSearchMessageHandler::SearchMenuPerformedSearchMessageHandler(const std::shared_ptr<Search::SdkModel::ISearchQueryPerformer>& searchQueryPerformer,
                                                                                             const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                                                             const std::shared_ptr<Metrics::IMetricsService>& metricsService)
            : m_searchQueryPerformer(searchQueryPerformer)
            , m_messageBus(messageBus)
            , m_metricsService(metricsService)
            , m_handlePerformedSearchMessageBinding(this, &SearchMenuPerformedSearchMessageHandler::OnPerformedSearchMessage)
            {
                m_messageBus->SubscribeNative(m_handlePerformedSearchMessageBinding);
            }
            
            SearchMenuPerformedSearchMessageHandler::~SearchMenuPerformedSearchMessageHandler()
            {
                m_messageBus->UnsubscribeNative(m_handlePerformedSearchMessageBinding);
            }
            
            void SearchMenuPerformedSearchMessageHandler::OnPerformedSearchMessage(const SearchMenuPerformedSearchMessage& message)
            {
                m_metricsService->SetEvent("Search", "Search string", message.SearchQuery().c_str());
                m_searchQueryPerformer->PerformSearchQuery(message.SearchQuery(), message.IsTag(), message.IsInterior());
            }
        }
    }
}
