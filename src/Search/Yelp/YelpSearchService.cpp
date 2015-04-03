// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <vector>
#include <sstream>
#include "YelpSearchService.h"
#include "ISearchResultParser.h"
#include "SearchResultModel.h"
#include "SearchQuery.h"
#include "Logger.h"
#include "IYelpSearchQueryFactory.h"
#include "IYelpSearchQuery.h"
#include "IGeoNamesSearchQueryFactory.h"
#include "IGeoNamesParser.h"
#include "INetworkCapabilities.h"
#include "Timer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            YelpSearchService::YelpSearchService(IYelpSearchQueryFactory& searchQueryFactory,
                                                 SdkModel::ISearchResultParser& searchResultParser,
                                                 GeoNames::IGeoNamesSearchQueryFactory& geoNamesSearchQueryFactory,
                                                 GeoNames::IGeoNamesParser& geoNamesParser,
                                                 Net::SdkModel::INetworkCapabilities& networkCapabilities)
                : m_searchQueryFactory(searchQueryFactory)
                , m_searchResultParser(searchResultParser)
                , m_geoNamesSearchQueryFactory(geoNamesSearchQueryFactory)
                , m_geoNamesParser(geoNamesParser)
                , m_networkCapabilities(networkCapabilities)
                , m_currentQueryModel("", false, Eegeo::Space::LatLongAltitude(0, 0, 0), 0.f)
                , m_poiSearchCallback(this, &YelpSearchService::HandleSearchResponse)
                , m_pCurrentRequest(NULL)
                , m_geoNameSearchCallback(this, &YelpSearchService::HandleGeoNameQueryResponse)
                , m_pCurrentGeoNameRequest(NULL)
                , m_currentQueryResponseCount(0)
                , m_numExpectedResponses(0)
                , m_hasActiveQuery(false)
            {
            }

            YelpSearchService::~YelpSearchService()
            {
                CancelInFlightQueries();
            }

            void YelpSearchService::CancelInFlightQueries()
            {
                if(m_pCurrentGeoNameRequest != NULL)
                {
                    m_pCurrentGeoNameRequest->Cancel();
                    Eegeo_DELETE m_pCurrentGeoNameRequest;
                    m_pCurrentGeoNameRequest = NULL;
                }
                
                if(m_pCurrentRequest != NULL)
                {
                    m_pCurrentRequest->Cancel();
                    m_pCurrentRequest = NULL;
                }
                
                if(m_hasActiveQuery)
                {
                    std::vector<SdkModel::SearchResultModel> results;
                    ExecutQueryResponseReceivedCallbacks(m_currentQueryModel, results);
                }
                
                m_hasActiveQuery = false;
            }

            void YelpSearchService::PerformLocationQuerySearch(const SdkModel::SearchQuery& searchQuery)
            {
                CancelInFlightQueries();
                
                m_currentQueryResponseCount = 0;
                m_numExpectedResponses = 0;
                m_currentQueryResults.clear();
                
                if(m_networkCapabilities.StreamOverWifiOnly() && !m_networkCapabilities.ConnectedToWifi())
                {
                    return;
                }
                
                m_currentQueryModel = searchQuery;
                m_hasActiveQuery = true;
                
                ExecuteQueryPerformedCallbacks(m_currentQueryModel);
                
                Eegeo::Helpers::Timer issueYelpRequestTimer;
                issueYelpRequestTimer.Start();
                
                IssueYelpRequest();
                issueYelpRequestTimer.Stop();
                if(issueYelpRequestTimer.Total() > 1)
                {
                    Eegeo::TtyHandler::TtyEnabled = true;
                    //Eegeo_TTY("issueYelpRequestTimer = %lld\n", issueYelpRequestTimer.Total());
                    Eegeo::TtyHandler::TtyEnabled = false;
                }
                
                IssueGeoNameRequest();
            }
            
            void YelpSearchService::IssueYelpRequest()
            {
                Eegeo_ASSERT(m_pCurrentRequest == NULL,
                             "Cannot issue Yelp query while exising query in-flight. Cancel existing query first.\n");
                
                ++ m_numExpectedResponses;
                
                // We instantiate a request with the factory, but although we 'own' it, we do not delete it.
                // The request is async and cleans itself up after it has posted a result back. This is due to
                // the details of how cancellation works with the request lifecycle for our platform specific
                // implementations. We keep a pointer to the current request so we can change the active request,
                // have a NULL request, etc.
                m_pCurrentRequest = m_searchQueryFactory.CreateYelpSearchForQuery(m_currentQueryModel, m_poiSearchCallback, m_searchResultParser);
                m_pCurrentRequest->Dispatch();
            }

            void YelpSearchService::HandleSearchResponse()
            {
                if(m_pCurrentRequest != NULL)
                {
                    if(m_pCurrentRequest->IsSucceeded())
                    {
                        Eegeo::Helpers::Timer parseSearchResultsTimer;
                        parseSearchResultsTimer.Start();
                        
                        //const std::string& response(m_pCurrentRequest->ResponseString());
                        //m_searchResultParser.ParseSearchResults(response, m_currentQueryResults);
                        m_currentQueryResults = m_pCurrentRequest->ResponseSearchQueryResults();
                        parseSearchResultsTimer.Stop();
                        if(parseSearchResultsTimer.Total() > 1)
                        {
                            Eegeo::TtyHandler::TtyEnabled = true;
                            //Eegeo_TTY("parseSearchResultsTimer = %lld\n", parseSearchResultsTimer.Total());
                            Eegeo::TtyHandler::TtyEnabled = false;
                        }
                    }

                    m_pCurrentRequest = NULL;
                    TryCompleteCurrentRequest();
                }
            }
            
            void YelpSearchService::IssueGeoNameRequest()
            {
                Eegeo_ASSERT(m_pCurrentGeoNameRequest == NULL,
                             "Cannot issue GeoName query while exising query in-flight. Cancel existing query first.\n");
                
                if(!m_currentQueryModel.IsCategory())
                {
                    ++ m_numExpectedResponses;
                    
                    m_pCurrentGeoNameRequest = m_geoNamesSearchQueryFactory.CreateGeoNamesSearchForQuery(m_currentQueryModel,
                                                                                                         m_geoNameSearchCallback);
                }
            }
            
            void YelpSearchService::HandleGeoNameQueryResponse()
            {
                if(m_pCurrentGeoNameRequest != NULL)
                {
                    if(m_pCurrentGeoNameRequest->IsSucceeded())
                    {
                        const std::string& response(m_pCurrentGeoNameRequest->ResponseString());
                        std::vector<GeoNames::GeoNamesSearchResultDto> geoNameResultDtos;
                        m_geoNamesParser.ParseGeoNamesQueryResults(response, geoNameResultDtos);
                        
                        if(!geoNameResultDtos.empty())
                        {
                            SdkModel::SearchResultModel model(geoNameResultDtos.begin()->ToSearchResultModel());
                            
                            // Note: Pushing to front of vector is lame, would be better with a deque...
                            m_currentQueryResults.insert(m_currentQueryResults.begin(), model);
                        }
                    }
                    
                    Eegeo_DELETE m_pCurrentGeoNameRequest;
                    m_pCurrentGeoNameRequest = NULL;
                    TryCompleteCurrentRequest();
                }
            }
            
            void YelpSearchService::TryCompleteCurrentRequest()
            {
                Eegeo_ASSERT(m_currentQueryResponseCount < m_numExpectedResponses,
                             "Unexpected number of responses received to Yelp query: got %d, expected %d.\n",
                             m_currentQueryResponseCount,
                             m_numExpectedResponses);
                
                if((++m_currentQueryResponseCount) == m_numExpectedResponses)
                {
                    ExecutQueryResponseReceivedCallbacks(m_currentQueryModel, m_currentQueryResults);
                    m_hasActiveQuery = false;
                    m_currentQueryResponseCount = 0;
                    m_numExpectedResponses = 0;
                    m_currentQueryResults.clear();
                }
            }
            
            void YelpSearchService::PerformIdentitySearch(const std::string& searchResultIdentifier,
                                                          Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback)
            {
                m_searchQueryFactory.CreateYelpSearchForSpecificLocation(searchResultIdentifier, callback, m_searchResultParser)->Dispatch();
            }
        }
    }
}

