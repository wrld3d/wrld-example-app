// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchMenuPerformedSearchMessage.h"
#include "ISearchQueryPerformer.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            class SearchMenuPerformedSearchMessageHandler : private Eegeo::NonCopyable
            {
                const std::shared_ptr<Search::SdkModel::ISearchQueryPerformer> m_searchQueryPerformer;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<SearchMenuPerformedSearchMessageHandler, const SearchMenuPerformedSearchMessage&> m_handlePerformedSearchMessageBinding;
                
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;
                
                void OnPerformedSearchMessage(const SearchMenuPerformedSearchMessage& message);
                
            public:
                SearchMenuPerformedSearchMessageHandler(const std::shared_ptr<Search::SdkModel::ISearchQueryPerformer>& searchQueryPerformer,
                                                        const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                        const std::shared_ptr<Metrics::IMetricsService>& metricsService);
                
                ~SearchMenuPerformedSearchMessageHandler();
            };
        }
    }
}
