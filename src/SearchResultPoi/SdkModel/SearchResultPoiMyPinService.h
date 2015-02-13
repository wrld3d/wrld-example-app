// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultPoiMyPinService.h"
#include "SearchResultModel.h"
#include "MyPins.h"
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
                MyPins::SdkModel::IMyPinsRepository& m_myPinsRepository;
                CategorySearch::ISearchResultIconCategoryMapper& m_searchResultIconCategoryMapper;
                
            public:
                SearchResultPoiMyPinService(MyPins::SdkModel::IMyPinsService& myPinsService,
                                            MyPins::SdkModel::IMyPinsRepository& myPinsRepository,
                                            CategorySearch::ISearchResultIconCategoryMapper& searchResultIconCategoryMapper);
                
                ~SearchResultPoiMyPinService();
                
                void AddOrRemoveSearchResultFromMyPins(const Search::SdkModel::SearchResultModel& searchResult);
            };
        }
    }
}
