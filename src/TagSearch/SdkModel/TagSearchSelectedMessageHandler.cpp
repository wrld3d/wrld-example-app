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
                m_metricsService->SetEvent("Category Search", "Category", message.Tag());
                if (message.HasRadius())
                {
                    m_searchQueryPerformer->PerformSearchQuery(message.Tag(), true, message.InteriorSearchAllowed(), message.Radius());
                }
                else
                {
                    m_searchQueryPerformer->PerformSearchQuery(message.Tag(), true, message.InteriorSearchAllowed());
                }
            }
            
            TagSearchSelectedMessageHandler::TagSearchSelectedMessageHandler(const std::shared_ptr<Search::SdkModel::ISearchQueryPerformer>& searchQueryPerformer,
                                                                         const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                                         const std::shared_ptr<Metrics::IMetricsService>& metricsService)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_handlerBinding(this, &TagSearchSelectedMessageHandler::OnTagSearchSelectedMessage)
            {
                m_messageBus->SubscribeNative(m_handlerBinding);
            }

            TagSearchSelectedMessageHandler::~TagSearchSelectedMessageHandler()
            {
                m_messageBus->UnsubscribeNative(m_handlerBinding);
            }
        }
    }
}
