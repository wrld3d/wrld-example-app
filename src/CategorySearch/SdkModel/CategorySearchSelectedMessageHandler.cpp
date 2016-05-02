// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CategorySearchSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace SdkModel
        {
            void CategorySearchSelectedMessageHandler::OnCategorySearchSelectedMessage(const CategorySearchSelectedMessage& message)
            {
                m_metricsService.SetEvent("Category Search", "Category", message.Category());
                if (message.HasRadius())
                {
                    m_searchQueryPerformer.PerformSearchQuery(message.Category(), true, message.InteriorSearchAllowed(), message.Radius());
                }
                else
                {
                    m_searchQueryPerformer.PerformSearchQuery(message.Category(), true, message.InteriorSearchAllowed());
                }
            }

            CategorySearchSelectedMessageHandler::CategorySearchSelectedMessageHandler(
                Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_handlerBinding(this, &CategorySearchSelectedMessageHandler::OnCategorySearchSelectedMessage)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }

            CategorySearchSelectedMessageHandler::~CategorySearchSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }
            
        }
    }
}
