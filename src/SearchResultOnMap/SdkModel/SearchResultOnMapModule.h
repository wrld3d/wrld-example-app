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
                View::ISearchResultOnMapIconCategoryMapper* m_pSearchResultOnMapIconCategoryMapper;
                View::SearchResultOnMapItemModelSelectedObserver* m_pSearchResultOnMapItemModelSelectedObserver;

            public:
                SearchResultOnMapModule(Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                        SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                        WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                        ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultOnMapModule();

                ISearchResultOnMapModel& GetSearchResultOnMapModel() const;

            };
        }
    }
}
