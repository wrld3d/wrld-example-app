// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchService.h"
#include "SearchQuery.h"
#include "SwallowSearchConstants.h"
#include "IPoiDbModule.h"
#include "IPoiDbService.h"
#include "PoiFtsResults.h"
#include "SQLiteSpellingSuggestionResults.h"
#include <sstream>
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowSearchService::SwallowSearchService(const std::vector<std::string>& availableCategories,
                                                           PoiDb::IPoiDbModule& poiDbModule)
                : Search::SdkModel::SearchServiceBase(availableCategories)
                , m_poiDbModule(poiDbModule)
                {
                    
                }
                
                void SwallowSearchService::CancelInFlightQueries()
                {
                    
                }
                
                void SwallowSearchService::PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query)
                {
                    PoiDb::IPoiDbService* poiDbService;
                    
                    ExecuteQueryPerformedCallbacks(query);
                    
                    if(m_poiDbModule.TryGetPoiDbService(poiDbService))
                    {
                        if(query.IsCategory())
                        {
                            PerformCategorySearch(query, *poiDbService);
                        }
                        else
                        {
                            PerformFullTextSearch(query, *poiDbService);
                        }
                    }
                    else
                    {
                        ExecutQueryResponseReceivedCallbacks(query, std::vector<Search::SdkModel::SearchResultModel>());
                    }
                }
                    
                void SwallowSearchService::PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                 Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
                {
                    // Not implemented.
                    Search::SdkModel::IdentitySearchCallbackData result = Search::SdkModel::IdentitySearchCallbackData::CreateFailed(outdatedSearchResult);
                    callback(result);
                }
                
                void SwallowSearchService::PerformFullTextSearch(const Search::SdkModel::SearchQuery& query, PoiDb::IPoiDbService& poiDbService)
                {
                    Eegeo::SQLite::SQLiteSpellingSuggestionResults spellingSuggestions;
                    poiDbService.SuggestSpelling(query.Query(), spellingSuggestions);
                    
                    PoiDb::PoiFtsResults ftsResults;
                    
                    poiDbService.FullTextSearch(spellingSuggestions.spellCheckedSearchQuery, ftsResults);
                    
                    ParseSearchResults(query, ftsResults.resultRows);
                }
                
                void SwallowSearchService::PerformCategorySearch(const Search::SdkModel::SearchQuery& query, PoiDb::IPoiDbService& poiDbService)
                {
                    ExecutQueryResponseReceivedCallbacks(query, std::vector<Search::SdkModel::SearchResultModel>());
                }
                
                void SwallowSearchService::ParseSearchResults(const Search::SdkModel::SearchQuery& query, const std::vector<PoiDb::PoiTableDto>& results)
                {
                    std::vector<Search::SdkModel::SearchResultModel> searchResults;
                    
                    SearchParser::ParsePersonSearchResults(results, searchResults);
                    
                    ExecutQueryResponseReceivedCallbacks(query, searchResults);
                }
            }
        }
    }
}
