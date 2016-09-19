// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

//#include "AndroidNativeState.h"
//#include "Types.h"
//#include "SearchResultPoi.h"
//#include "SearchResultPoiViewIncludes.h"
//#include "ISearchResultPoiViewModule.h"
//#include "BidirectionalBus.h"
//#include "IMetricsService.h"
#include "Module.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiViewModule: public Module
            {
            public:
            	void Register(const TContainerBuilder& builder);
//            private:
//                SearchResultPoiView* m_pView;
//                SearchResultPoiController* m_pController;
//
//            public:
//                SearchResultPoiViewModule(
//                    AndroidNativeState& nativeState,
//                    ISearchResultPoiViewModel& searchResultPoiViewModel,
//                    ExampleAppMessaging::TMessageBus& messageBus,
//                    Metrics::IMetricsService& metricsService
//                );
//
//                ~SearchResultPoiViewModule();
//
//                SearchResultPoiView& GetView() const;
//                SearchResultPoiController& GetController() const;
            };
        }
    }
}
