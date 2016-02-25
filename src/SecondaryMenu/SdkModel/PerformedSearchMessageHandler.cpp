// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PerformedSearchMessageHandler.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace SdkModel
        {
            PerformedSearchMessageHandler::PerformedSearchMessageHandler(
                Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_handlePerformedSearchMessageBinding(this, &PerformedSearchMessageHandler::OnPerformedSearchMessage)
            {
                m_messageBus.SubscribeNative(m_handlePerformedSearchMessageBinding);
            }

            PerformedSearchMessageHandler::~PerformedSearchMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlePerformedSearchMessageBinding);
            }

            void PerformedSearchMessageHandler::OnPerformedSearchMessage(const PerformedSearchMessage& message)
            {
                m_metricsService.SetEvent("Search", "Search string", message.SearchQuery().c_str());
                m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), message.IsCategory(), message.IsInterior());
            }
        }
    }
}
