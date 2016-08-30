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
                const std::shared_ptr<MyPins::SdkModel::IMyPinsService> m_myPinsService;
                const std::shared_ptr<Search::SdkModel::MyPins::ISearchResultMyPinsService> m_searchResultMyPinsService;
                const std::shared_ptr<CategorySearch::ISearchResultIconCategoryMapper> m_searchResultIconCategoryMapper;
                
            public:
                SearchResultPoiMyPinService(const std::shared_ptr<MyPins::SdkModel::IMyPinsService>& myPinsService,
                                            const std::shared_ptr<Search::SdkModel::MyPins::ISearchResultMyPinsService>& searchResultMyPinsService,
                                            const std::shared_ptr<CategorySearch::ISearchResultIconCategoryMapper>& searchResultIconCategoryMapper);
                
                ~SearchResultPoiMyPinService();
                
                void AddOrRemoveSearchResultFromMyPins(const Search::SdkModel::SearchResultModel& searchResult);
            };
        }
    }
}
