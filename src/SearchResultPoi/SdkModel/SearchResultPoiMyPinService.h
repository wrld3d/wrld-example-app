// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultPoiMyPinService.h"
#include "SearchResultModel.h"
#include "MyPins.h"
#include "Search.h"
#include "CategorySearch.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            class SearchResultPoiMyPinService : public ISearchResultPoiMyPinService, private Eegeo::NonCopyable
            {
                MyPins::SdkModel::IMyPinsService& m_myPinsService;
                Search::SdkModel::MyPins::ISearchResultMyPinsService& m_searchResultMyPinsService;
                CategorySearch::ISearchResultIconCategoryMapper& m_searchResultIconCategoryMapper;
                
            public:
                SearchResultPoiMyPinService(MyPins::SdkModel::IMyPinsService& myPinsService,
                                            Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultMyPinsService,
                                            CategorySearch::ISearchResultIconCategoryMapper& searchResultIconCategoryMapper);
                
                ~SearchResultPoiMyPinService();
                
                void AddOrRemoveSearchResultFromMyPins(const Search::SdkModel::SearchResultModel& searchResult);
            };
        }
    }
}
