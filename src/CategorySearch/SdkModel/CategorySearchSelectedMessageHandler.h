// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ISearchQueryPerformer.h"
#include "ICallback.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace SdkModel
        {
            class CategorySearchSelectedMessageHandler : private Eegeo::NonCopyable
            {
                const std::shared_ptr<Search::SdkModel::ISearchQueryPerformer> m_searchQueryPerformer;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<CategorySearchSelectedMessageHandler, const CategorySearchSelectedMessage&> m_handlerBinding;
                
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;

                void OnCategorySearchSelectedMessage(const CategorySearchSelectedMessage& message);

            public:
                CategorySearchSelectedMessageHandler(const std::shared_ptr<Search::SdkModel::ISearchQueryPerformer>& searchQueryPerformer,
                                                     const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                     const std::shared_ptr<Metrics::IMetricsService>& metricsService);

                ~CategorySearchSelectedMessageHandler();
            };
        }
    }
}
