// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchService.h"
#include "SearchQuery.h"
#include "SwallowSearchConstants.h"
#include "IPoiDbModule.h"
#include "IPoiDbService.h"
#include "PoiFtsResults.h"
#include "SQLiteSpellingSuggestionResults.h"
#include <sstream>

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            SwallowSearchService::SwallowSearchService(PoiDb::IPoiDbModule& poiDbModule)
            : m_poiDbModule(poiDbModule)
            {
                
            }
            
            void SwallowSearchService::CancelInFlightQueries()
            {
                
            }
            
            void SwallowSearchService::PerformLocationQuerySearch(const SdkModel::SearchQuery& query)
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
            }
                
            void SwallowSearchService::PerformIdentitySearch(const std::string& searchResultIdentifier,
                                                             Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback)
            {
                 Eegeo_ASSERT(false, "Identity search not implemented");
            }
            
            void SwallowSearchService::PerformFullTextSearch(const SdkModel::SearchQuery& query, PoiDb::IPoiDbService& poiDbService)
            {
                Eegeo::SQLite::SQLiteSpellingSuggestionResults spellingSuggestions;
                poiDbService.SuggestSpelling(query.Query(), spellingSuggestions);
                
                PoiDb::PoiFtsResults ftsResults;
                
                poiDbService.FullTextSearch(spellingSuggestions.spellCheckedSearchQuery, ftsResults);
                
                ParseSearchResults(query, ftsResults.resultRows);
            }
            
            void SwallowSearchService::PerformCategorySearch(const SdkModel::SearchQuery& query, PoiDb::IPoiDbService& poiDbService)
            {
                
            }
            
            void SwallowSearchService::ParseSearchResults(const SdkModel::SearchQuery& query, const std::vector<PoiDb::PoiTableDto>& results)
            {
                std::vector<SdkModel::SearchResultModel> searchResults;
                
                for(int i = 0; i < results.size(); ++i)
                {
                    std::stringstream idString;
                    idString << results.at(i).poi_id;
                    
                    std::map<std::string, std::string> metaData;
                    
                    metaData.insert(std::pair<std::string, std::string>(JOB_TITLE_FIELD_NAME, results.at(i).job_title));
                    metaData.insert(std::pair<std::string, std::string>(WORKING_GROUP_FIELD_NAME, results.at(i).working_group));
                    metaData.insert(std::pair<std::string, std::string>(OFFICE_LOCATION_FIELD_NAME, results.at(i).office_location));
                    metaData.insert(std::pair<std::string, std::string>(DESK_CODE_FIELD_NAME, results.at(i).desk_code));
                    
                    searchResults.push_back(SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
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
