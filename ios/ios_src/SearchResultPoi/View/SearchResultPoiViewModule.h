// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultPoi.h"
#include "ISearchResultPoiViewModule.h"
#include "SearchResultPoiController.h"
#include "SearchResultPoiViewContainer.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiViewModule: public ISearchResultPoiViewModule, private Eegeo::NonCopyable
            {
            private:
                SearchResultPoiViewContainer* m_pView;
                SearchResultPoiController* m_pController;

            public:
                SearchResultPoiViewModule(ISearchResultPoiViewModel& searchResultPoiViewModel,
                                          ExampleAppMessaging::TMessageBus& messageBus,
                                          Metrics::IMetricsService& metricsService);

                ~SearchResultPoiViewModule();

                SearchResultPoiController& GetController() const;

                SearchResultPoiViewContainer& GetView() const;
            };
        }
    }
}
