// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxSearchService.h"
#include "SearchQuery.h"
#include "LaxSearchConstants.h"
//#include "LaxPoiDbServiceProvider.h"
//#include "LaxPoiDbCombinedService.h"
#include <sstream>
#include "LaxSearchConstants.h"
#include "LaxSearchParser.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
//                LaxSearchService::LaxSearchService(const std::vector<std::string>& availableCategories,
//                                                           LaxPoiDb::LaxPoiDbServiceProvider& LaxPoiDbServiceProvider)
//                : Search::SdkModel::SearchServiceBase(availableCategories)
//                , m_LaxPoiDbServiceProvider(LaxPoiDbServiceProvider)
                
                LaxSearchService::LaxSearchService(const std::vector<std::string>& availableCategories)
                : Search::SdkModel::SearchServiceBase(availableCategories)
                {
                    
                }
                
                void LaxSearchService::CancelInFlightQueries()
                {
                    
                }
                
                void LaxSearchService::PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query)
                {
//                    LaxPoiDb::LaxPoiDbCombinedService* LaxPoiDbService;
//                    
//                    ExecuteQueryPerformedCallbacks(query);
//                    
//                    if(m_LaxPoiDbServiceProvider.TryGetLaxPoiDbService(LaxPoiDbService))
//                    {
//                        if(query.IsCategory())
//                        {
//                            PerformCategorySearch(query, *LaxPoiDbService);
//                        }
//                        else
//                        {
//                            PerformFullTextSearch(query, *LaxPoiDbService);
//                        }
//                    }
//                    else
//                    {
//                        ExecutQueryResponseReceivedCallbacks(query, std::vector<Search::SdkModel::SearchResultModel>());
//                    }
                }
                    
                void LaxSearchService::PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                 Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
                {
                    // Not implemented.
                    Search::SdkModel::IdentitySearchCallbackData result = Search::SdkModel::IdentitySearchCallbackData::CreateFailed(outdatedSearchResult);
                    callback(result);
                }
                
//                void LaxSearchService::PerformFullTextSearch(const Search::SdkModel::SearchQuery& query, LaxPoiDb::LaxPoiDbCombinedService& LaxPoiDbService)
                
                void LaxSearchService::PerformFullTextSearch(const Search::SdkModel::SearchQuery& query)
                {
                    std::vector<Search::SdkModel::SearchResultModel> results;
                    
//                    LaxPoiDbService.FullTextSearch(query.Query(), results);
//                    
//                    ExecuteQueryPerformedCallbacks(query);
//                    ExecutQueryResponseReceivedCallbacks(query, results);
                }
                
//               void LaxSearchService::PerformCategorySearch(const Search::SdkModel::SearchQuery& query, LaxPoiDb::LaxPoiDbCombinedService& LaxPoiDbService)
                
                void LaxSearchService::PerformCategorySearch(const Search::SdkModel::SearchQuery& query)
                {
                    std::vector<Search::SdkModel::SearchResultModel> results;
                    
//                    LaxPoiDbService.CategorySearch(query.Query(), results);
//                    
//                    ExecuteQueryPerformedCallbacks(query);
//                    ExecutQueryResponseReceivedCallbacks(query, results);
                }
            }
        }
    }
}
