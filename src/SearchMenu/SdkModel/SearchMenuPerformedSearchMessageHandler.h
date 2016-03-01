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
                Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchMenuPerformedSearchMessageHandler, const SearchMenuPerformedSearchMessage&> m_handlePerformedSearchMessageBinding;
                
                Metrics::IMetricsService& m_metricsService;
                
                void OnPerformedSearchMessage(const SearchMenuPerformedSearchMessage& message);
                
            public:
                SearchMenuPerformedSearchMessageHandler(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                        ExampleAppMessaging::TMessageBus& messageBus,
                                                        Metrics::IMetricsService& metricsService);
                
                ~SearchMenuPerformedSearchMessageHandler();
            };
        }
    }
}
