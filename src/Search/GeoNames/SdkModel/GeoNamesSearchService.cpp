// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GeoNamesSearchService.h"

#include "GeoNamesSearchQuery.h"
#include "GeoNamesSearchQueryFactory.h"
#include "GeoNamesSearchResultDto.h"
#include "IGeoNamesParser.h"
#include "INetworkCapabilities.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                GeoNamesSearchService::GeoNamesSearchService(IGeoNamesSearchQueryFactory& geoNamesSearchQueryFactory,
                                                             IGeoNamesParser& geoNamesParser,
                                                             Net::SdkModel::INetworkCapabilities& networkCapabilities)
                : Search::SdkModel::SearchServiceBase(std::vector<std::string>())
                , m_geoNamesSearchQueryFactory(geoNamesSearchQueryFactory)
                , m_geoNamesParser(geoNamesParser)
                , m_networkCapabilities(networkCapabilities)
                , m_currentQueryModel("", false, false, Eegeo::Space::LatLongAltitude(0, 0, 0), 0.f)
                , m_searchCallback(this,&GeoNamesSearchService::HandleSearchResponse)
                , m_pCurrentRequest(NULL)
                , m_hasActiveQuery(false)
                {
                }
                
                GeoNamesSearchService::~GeoNamesSearchService()
                {
                    CancelInFlightQueries();
                }
                
                void GeoNamesSearchService::CancelInFlightQueries()
                {
                    if(m_pCurrentRequest != NULL)
                    {
                        if(m_hasActiveQuery)
                        {
                            m_pCurrentRequest->Cancel();
                        }
                        Eegeo_DELETE m_pCurrentRequest;
                        m_pCurrentRequest = NULL;
                    }
                    
                    if(m_hasActiveQuery)
                    {
                        m_hasActiveQuery = false;
                        std::vector<Search::SdkModel::SearchResultModel> results;
                        ExecutQueryResponseReceivedCallbacks(m_currentQueryModel, results);
                    }
                }
                
                void GeoNamesSearchService::PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query)
                {
                    CancelInFlightQueries();
                    
                    ExecuteQueryPerformedCallbacks(query);
                    if(m_currentQueryModel.IsTag() || (m_networkCapabilities.StreamOverWifiOnly() && !m_networkCapabilities.ConnectedToWifi()))
                    {
                        ExecutQueryResponseReceivedCallbacks(query, std::vector<Search::SdkModel::SearchResultModel>());
                        return;
                    }
                    
                    m_currentQueryModel = query;
                    m_hasActiveQuery = true;
                    
                    m_pCurrentRequest = m_geoNamesSearchQueryFactory.CreateGeoNamesSearchForQuery(m_currentQueryModel,
                                                                                                  m_searchCallback);
                }
                
                void GeoNamesSearchService::PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                  Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
                {
                    // Not implemented.
                    Search::SdkModel::IdentitySearchCallbackData result = Search::SdkModel::IdentitySearchCallbackData::CreateFailed(outdatedSearchResult);
                    callback(result);
                }
                
                void GeoNamesSearchService::HandleSearchResponse()
                {
                    std::vector<Search::SdkModel::SearchResultModel> queryResults;
                    if(m_pCurrentRequest != NULL && m_pCurrentRequest->IsSucceeded())  // Needs NULL check because callback can happen before factory returns query
                    {
                        const std::string& response(m_pCurrentRequest->ResponseString());
                        std::vector<GeoNamesSearchResultDto> geoNameResultDtos;
                        m_geoNamesParser.ParseGeoNamesQueryResults(response, geoNameResultDtos);
                        
                        queryResults.reserve(geoNameResultDtos.size());
                        if(!geoNameResultDtos.empty())
                        {
                            for(unsigned i = 0; i < geoNameResultDtos.size(); ++i)
                            {
                                Search::SdkModel::SearchResultModel model(geoNameResultDtos[i].ToSearchResultModel());
                                queryResults.push_back(model);
                            }
                        }
                    }
                    
                    m_hasActiveQuery = false;
                    ExecutQueryResponseReceivedCallbacks(m_currentQueryModel, queryResults);
                }
            }
        }
    }
}
