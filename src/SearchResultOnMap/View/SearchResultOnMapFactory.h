// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultOnMapFactory.h"
#include "SearchResultPoi.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            class SearchResultOnMapFactory : public ISearchResultOnMapFactory, private Eegeo::NonCopyable
            {
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Metrics::IMetricsService& m_metricsService;
                
                InteriorsExplorer::SdkModel::Highlights::InteriorEntityHighlightController& m_entityHighlightController;

            public:
                SearchResultOnMapFactory(ExampleAppMessaging::TMessageBus& messageBus,
                                         Metrics::IMetricsService& metricsService,
                                         InteriorsExplorer::SdkModel::Highlights::InteriorEntityHighlightController& entityHighlightController);

                ~SearchResultOnMapFactory();

                SearchResultOnMapItemModel* CreateSearchResultOnMapItemModel(Search::SdkModel::SearchResultModel& searchResultModel) const;
            };
        }
    }
}
