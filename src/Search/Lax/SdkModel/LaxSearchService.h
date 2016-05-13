// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Search.h"
#include "SearchServiceBase.h"
#include "LatLongAltitude.h"
#include "InteriorId.h"
//#include "LaxPoiDb.h"
#include "CategorySearchModel.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                class LaxSearchService : public Search::SdkModel::SearchServiceBase, private Eegeo::NonCopyable
                {
                public:
//                    LaxSearchService(const std::vector<std::string>& availableCategories,
//                                         LaxPoiDb::LaxPoiDbServiceProvider& LaxPoiDbServiceProvider);
                    
                    LaxSearchService(const std::vector<std::string>& availableCategories);
                    
                    void CancelInFlightQueries();
                    
                    void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                               Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                    
                private:
//                    void PerformFullTextSearch(const Search::SdkModel::SearchQuery& query, LaxPoiDb::LaxPoiDbCombinedService& LaxPoiDbService);
//                    
//                    void PerformCategorySearch(const Search::SdkModel::SearchQuery& query, LaxPoiDb::LaxPoiDbCombinedService& LaxPoiDbService);
                    
                    void PerformFullTextSearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformCategorySearch(const Search::SdkModel::SearchQuery& query);
                    
//                    LaxPoiDb::LaxPoiDbServiceProvider& m_LaxPoiDbServiceProvider;
                };
            }
        }
    }
}
