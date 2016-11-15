// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Search.h"
#include "SearchServiceBase.h"
#include "LatLongAltitude.h"
#include "InteriorId.h"
#include "SwallowPoiDb.h"
#include "TagSearchModel.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowSearchService : public Search::SdkModel::SearchServiceBase, private Eegeo::NonCopyable
                {
                public:
                    SwallowSearchService(const std::vector<std::string>& availableCategories,
                                         SwallowPoiDb::SwallowPoiDbServiceProvider& swallowPoiDbServiceProvider);
                    
                    void CancelInFlightQueries();
                    
                    void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                               Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                    
                private:
                    void PerformFullTextSearch(const Search::SdkModel::SearchQuery& query, SwallowPoiDb::SwallowPoiDbCombinedService& swallowPoiDbService);
                    
                    void PerformCategorySearch(const Search::SdkModel::SearchQuery& query, SwallowPoiDb::SwallowPoiDbCombinedService& swallowPoiDbService);
                    
                    SwallowPoiDb::SwallowPoiDbServiceProvider& m_swallowPoiDbServiceProvider;
                };
            }
        }
    }
}
