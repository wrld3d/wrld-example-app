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
                    
                    for(int i = 0; i < results.size(); ++i)
                    {
                        std::stringstream idString;
                        idString << results.at(i).poi_id;
                        
                        std::map<std::string, std::string> metaData;
                        
                        metaData.insert(std::pair<std::string, std::string>(SearchConstants::JOB_TITLE_FIELD_NAME, results.at(i).job_title));
                        metaData.insert(std::pair<std::string, std::string>(SearchConstants::WORKING_GROUP_FIELD_NAME, results.at(i).working_group));
                        metaData.insert(std::pair<std::string, std::string>(SearchConstants::OFFICE_LOCATION_FIELD_NAME, results.at(i).office_location));
                        metaData.insert(std::pair<std::string, std::string>(SearchConstants::DESK_CODE_FIELD_NAME, results.at(i).desk_code));
                        
                        searchResults.push_back(Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                                    idString.str(),
                                                                                    results.at(i).name,
                                                                                    Eegeo::Space::LatLong::FromDegrees(results.at(i).latitude_degrees, results.at(i).longitude_degrees),
                                                                                    0.0f,
                                                                                    true,
                                                                                    Eegeo::Resources::Interiors::InteriorId(results.at(i).interior_id),
                                                                                    results.at(i).interior_floor,
                                                                                    "",
                                                                                    "",
                                                                                    "",
                                                                                    "person",
                                                                                    std::vector<std::string>(),
                                                                                    "",
                                                                                    "Swallow",
                                                                                    results.at(i).image_filename,
                                                                                    "",
                                                                                    std::vector<std::string>(),
                                                                                    0,
                                                                                    0,
                                                                                    metaData));
                    }
                    
                    ExecutQueryResponseReceivedCallbacks(query, searchResults);
                }
            }
        }
    }
}
