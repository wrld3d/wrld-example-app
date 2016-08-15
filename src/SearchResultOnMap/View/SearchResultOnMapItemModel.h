// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinSelectionHandler.h"
#include "Search.h"
#include "SearchResultPoi.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            class SearchResultOnMapItemModel : public WorldPins::SdkModel::IWorldPinSelectionHandler, private Eegeo::NonCopyable
            {
                Search::SdkModel::SearchResultModel m_searchResultModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Metrics::IMetricsService& m_metricsService;
                
                Eegeo::Helpers::TCallback1<SearchResultOnMapItemModel, const SearchResultOnMap::SearchResultMeetingAvailabilityChanged&> m_availabilityChangedHandlerBinding;
                
                void OnAvailabilityChanged(const ExampleApp::SearchResultOnMap::SearchResultMeetingAvailabilityChanged& message);

            public:
                SearchResultOnMapItemModel(const Search::SdkModel::SearchResultModel& searchResultModel,
                                           ExampleAppMessaging::TMessageBus& messageBus,
                                           Metrics::IMetricsService& metricsService);

                ~SearchResultOnMapItemModel();

                void SelectPin();
            };
        }
    }
}
