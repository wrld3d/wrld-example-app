// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "ISearchResultOnMapModule.h"
#include "SearchResultOnMap.h"
#include "SearchResultPoi.h"
#include "WorldPins.h"
#include "Location.h"
#include "Modality.h"
#include "IIdentity.h"
#include "Rendering.h"
#include "Camera.h"
#include "SearchResultOnMapItemModelSelectedObserver.h"
#include "BidirectionalBus.h"
#include "TagSearch.h"
#include "MyPins.h"
#include "IMetricsService.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            class SearchResultOnMapModule: public ISearchResultOnMapModule, private Eegeo::NonCopyable
            {
            private:
                ISearchResultOnMapModel* m_pSearchResultOnMapModel;
                View::ISearchResultOnMapFactory* m_pSearchResultOnMapFactory;
                View::SearchResultOnMapItemModelSelectedObserver* m_pSearchResultOnMapItemModelSelectedObserver;

            public:
                SearchResultOnMapModule(Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                        SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                        WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                        MyPins::SdkModel::IMyPinsService& myPinsService,
                                        TagSearch::ISearchResultIconKeyMapper& searchResultOnMapIconKeyMapper,
                                        Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultMyPinsService,
                                        ExampleAppMessaging::TMessageBus& messageBus,
                                        Metrics::IMetricsService& metricsService,
                                        const Menu::View::IMenuReactionModel& menuReaction);

                ~SearchResultOnMapModule();

                ISearchResultOnMapModel& GetSearchResultOnMapModel() const;

            };
        }
    }
}
