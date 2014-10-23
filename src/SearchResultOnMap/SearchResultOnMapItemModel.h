// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinSelectionHandler.h"
#include "Search.h"
#include "SearchResultPoi.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class SearchResultOnMapItemModel : public WorldPins::IWorldPinSelectionHandler, private Eegeo::NonCopyable
        {
            Search::SearchResultModel& m_searchResultModel;
            SearchResultPoi::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
            
        public:
            SearchResultOnMapItemModel(Search::SearchResultModel& searchResultModel,
                                       SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel);
            
            ~SearchResultOnMapItemModel();
            
            void SelectPin();
        };
    }
}
