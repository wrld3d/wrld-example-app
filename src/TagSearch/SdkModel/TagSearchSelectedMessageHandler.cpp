// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TagSearchSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            void TagSearchSelectedMessageHandler::OnTagSearchSelectedMessage(const TagSearchSelectedMessage& message)
            {
                // note: have left the metric event name the same after category => tag rename so that existing metrics
                // aren't affected. If this is not a concern, we should rename the strings from category => tag
                m_metricsService.SetEvent("Category Search", "Category", message.Tag());
                if (message.HasRadius())
                {
                    m_searchQueryPerformer.PerformSearchQuery(message.Tag(), true, message.InteriorSearchAllowed(), message.Radius());
                }
                else
                {
                    m_searchQueryPerformer.PerformSearchQuery(message.Tag(), true, message.InteriorSearchAllowed());
                }
            }

            TagSearchSelectedMessageHandler::TagSearchSelectedMessageHandler(
                Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_handlerBinding(this, &TagSearchSelectedMessageHandler::OnTagSearchSelectedMessage)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }

            TagSearchSelectedMessageHandler::~TagSearchSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }
            
        }
    }
}
