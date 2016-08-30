// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultOnMapFactory.h"
#include "SearchResultPoi.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            class SearchResultOnMapFactory : public ISearchResultOnMapFactory, private Eegeo::NonCopyable
            {
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;

            public:
                SearchResultOnMapFactory(const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus, const std::shared_ptr<Metrics::IMetricsService>& metricsService);

                ~SearchResultOnMapFactory();

                SearchResultOnMapItemModel* CreateSearchResultOnMapItemModel(Search::SdkModel::SearchResultModel& searchResultModel) const;
            };
        }
    }
}
