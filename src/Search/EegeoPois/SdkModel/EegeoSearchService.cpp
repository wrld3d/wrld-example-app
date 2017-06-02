// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoSearchService.h"

#include "EegeoSearchQuery.h"
#include "EegeoSearchQueryFactory.h"
#include "IEegeoParser.h"
#include "INetworkCapabilities.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoSearchService::EegeoSearchService(IEegeoSearchQueryFactory& EegeoSearchQueryFactory,
                                                               IEegeoParser& EegeoParser,
                                                               Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                               const std::vector<std::string>& handledTags)
                : Search::SdkModel::SearchServiceBase(handledTags, true)
                , m_eeGeoSearchQueryFactory(EegeoSearchQueryFactory)
                , m_eeGeoParser(EegeoParser)
                , m_networkCapabilities(networkCapabilities)
                , m_currentQueryModel("", false, false, Eegeo::Space::LatLongAltitude(0, 0, 0), 0.f)
                , m_searchCallback(this,&EegeoSearchService::HandleSearchResponse)
                , m_pCurrentRequest(NULL)
                , m_hasActiveQuery(false)
                , m_networkCapabilitiesChangedHandler(this, &EegeoSearchService::HandleNetworkCapabilitiesChanged)
                {
                    m_networkCapabilities.RegisterChangedCallback(m_networkCapabilitiesChangedHandler);
                }
                
                EegeoSearchService::~EegeoSearchService()
                {
                    CancelInFlightQueries();
                    m_networkCapabilities.UnregisterChangedCallback(m_networkCapabilitiesChangedHandler);
                }
                
                void EegeoSearchService::CancelInFlightQueries()
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
                
                void EegeoSearchService::PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query)
                {
                    CancelInFlightQueries();
                    
                    ExecuteQueryPerformedCallbacks(query);
                    if(m_networkCapabilities.StreamOverWifiOnly() && !m_networkCapabilities.ConnectedToWifi())
                    {
                        ExecutQueryResponseReceivedCallbacks(query, std::vector<Search::SdkModel::SearchResultModel>());
                        return;
                    }
                    
                    m_currentQueryModel = query;
                    m_hasActiveQuery = true;
                    
                    m_pCurrentRequest = m_eeGeoSearchQueryFactory.CreateEegeoSearchForQuery(m_currentQueryModel,
                                                                                                  m_searchCallback);
                }
                
                void EegeoSearchService::PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                  Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
                {
                    // Not implemented.
                    Search::SdkModel::IdentitySearchCallbackData result = Search::SdkModel::IdentitySearchCallbackData::CreateFailed(outdatedSearchResult);
                    callback(result);
                }
                
                void EegeoSearchService::HandleSearchResponse()
                {
                    std::vector<Search::SdkModel::SearchResultModel> queryResults;
                    if(m_pCurrentRequest != NULL && m_pCurrentRequest->IsSucceeded())  // Needs NULL check because callback can happen before factory returns query
                    {
                        const std::string& response(m_pCurrentRequest->ResponseString());
                        m_eeGeoParser.ParseEegeoQueryResults(response, queryResults);
                    }
                    
                    m_hasActiveQuery = false;
                    ExecutQueryResponseReceivedCallbacks(m_currentQueryModel, queryResults);
                }
                
                void EegeoSearchService::HandleNetworkCapabilitiesChanged()
                {
                    if (!m_networkCapabilities.NetworkAvailable())
                    {
                        CancelInFlightQueries();
                    }
                }
            }
        }
    }
}
