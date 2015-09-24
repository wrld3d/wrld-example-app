// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <vector>
#include "DecartaSearchService.h"
#include "ISearchResultParser.h"
#include "Types.h"
#include "IWebLoadRequest.h"
#include "LatLongAltitude.h"
#include "SearchResultModel.h"
#include "IWebLoadRequestFactory.h"
#include "WebLoadRequestCompletionCallback.h"
#include "SearchQuery.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Decarta
        {
            namespace SdkModel
            {
                DecartaSearchService::DecartaSearchService(const std::string& decartaApiKey,
                                                           Search::SdkModel::ISearchResultParser& parser,
                                                           Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                           Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                           const std::vector<std::string>& availableCategories)
                : Search::SdkModel::SearchServiceBase(availableCategories)
                , m_decartaApiKey(decartaApiKey)
                , m_parser(parser)
                , m_webRequestFactory(webRequestFactory)
                , m_urlEncoder(urlEncoder)
                , m_pPoiSearchCallback(Eegeo_NEW(Eegeo::Web::TWebLoadRequestCompletionCallback<DecartaSearchService>)(this, &DecartaSearchService::HandleSearchResponse))
                , m_pCurrentRequest(NULL)
                {
                }
                
                DecartaSearchService::~DecartaSearchService()
                {
                    CancelInFlightQueries();
                    Eegeo_DELETE m_pPoiSearchCallback;
                }
                
                void DecartaSearchService::CancelInFlightQueries()
                {
                    if(m_pCurrentRequest != NULL)
                    {
                        std::vector<Search::SdkModel::SearchResultModel> results;
                        Search::SdkModel::SearchQuery* pRequestBoundQuery = static_cast<Search::SdkModel::SearchQuery*>(m_pCurrentRequest->GetUserData());
                        ExecutQueryResponseReceivedCallbacks(*pRequestBoundQuery, results);
                        Eegeo_DELETE pRequestBoundQuery;
                        m_pCurrentRequest->Cancel();
                        m_pCurrentRequest = NULL;
                    }
                }
                
                void DecartaSearchService::PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& searchQuery)
                {
                    CancelInFlightQueries();
                    
                    ExecuteQueryPerformedCallbacks(searchQuery);
                    
                    const std::string baseUrl =  "http://api.decarta.com/v1/";
                    
                    std::stringstream ss;
                    ss << baseUrl;
                    ss << m_decartaApiKey;
                    
                    if(searchQuery.IsCategory())
                    {
                        // Some decarta categories from http://developer.decarta.com/Docs/REST/Search#category
                        EncodeApiQueryIntoStringStream(searchQuery.Query(), "/search/category/", ss);
                    }
                    else
                    {
                        if(searchQuery.Query().empty())
                        {
                            // Ideally we could use the search API to perform a 'wildcard' search here to get all
                            // the POI results nearby, but deCarta does not support this feature. We could fake it
                            // by performing multiple searches for various categories from the deCarta category
                            // list, aggregating the results, but seems overly complex for this example.
                            ExecutQueryResponseReceivedCallbacks(searchQuery, std::vector<Search::SdkModel::SearchResultModel>());
                            return;
                        }
                        else
                        {
                            EncodeApiQueryIntoStringStream(searchQuery.Query(), "/search/", ss);
                        }
                    }
                    
                    ss << "?lat=" << searchQuery.Location().GetLatitudeInDegrees();
                    ss << "&lon=" << searchQuery.Location().GetLongitudeInDegrees();
                    ss << "&radius=" << searchQuery.Radius();
                    ss << "&limit=100";
                    
                    std::string url = ss.str();
                    EXAMPLE_LOG("Search Request: %s\n", url.c_str());
                    
                    IssueRequest(url, searchQuery);
                }
                
                void DecartaSearchService::IssueRequest(const std::string queryUrl, const Search::SdkModel::SearchQuery& query)
                {
                    // Dynamically allocate a copy of the search query for association with the web request, as we do not know
                    // the lifetime of the parameter, and we do not really want to store state when the lifetime is bound to the
                    // request anyway.
                    
                    Search::SdkModel::SearchQuery* pRequestBoundQuery = Eegeo_NEW(Search::SdkModel::SearchQuery)(query.Query(),
                                                                                                                 query.IsCategory(),
                                                                                                                 query.Location(),
                                                                                                                 query.Radius());
                    
                    m_pCurrentRequest = m_webRequestFactory.CreateGet(queryUrl, *m_pPoiSearchCallback, pRequestBoundQuery);
                    m_pCurrentRequest->SetTimeoutSeconds(10);
                    m_pCurrentRequest->Load();
                }
                
                void DecartaSearchService::HandleSearchResponse(Eegeo::Web::IWebLoadRequest& webLoadRequest)
                {
                    if(m_pCurrentRequest != NULL)
                    {
                        std::vector<Search::SdkModel::SearchResultModel> results;
                        Search::SdkModel::SearchQuery* pRequestBoundQuery = static_cast<Search::SdkModel::SearchQuery*>(webLoadRequest.GetUserData());
                        
                        EXAMPLE_LOG("Search Response Code: %d\n", webLoadRequest.HttpStatusCode());
                        
                        if(webLoadRequest.IsSucceeded())
                        {
                            size_t resultSize = webLoadRequest.GetResourceData().size();
                            std::string serialized(reinterpret_cast<char const*>(&(webLoadRequest.GetResourceData().front())), resultSize);
                            
                            EXAMPLE_LOG("Search Response Body: %s\n", serialized.c_str());
                            
                            m_parser.ParseSearchResults(serialized, results);
                        }
                        
                        ExecutQueryResponseReceivedCallbacks(*pRequestBoundQuery, results);
                        
                        // Must delete this query as we dynamically allocated it in DecartaSearchService::IssueRequest.
                        Eegeo_DELETE pRequestBoundQuery;
                        m_pCurrentRequest = NULL;
                    }
                }
                
                void DecartaSearchService::EncodeApiQueryIntoStringStream(const std::string& query,
                                                                          const std::string& apiPoint,
                                                                          std::stringstream& out_stream)
                {
                    out_stream << apiPoint;
                    std::string encodedQuery;
                    m_urlEncoder.UrlEncode(query, encodedQuery);
                    out_stream << encodedQuery << ".json";
                }
                
                void DecartaSearchService::PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                 Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
                {
                    // Not implemented.
                    Search::SdkModel::IdentitySearchCallbackData result = Search::SdkModel::IdentitySearchCallbackData::CreateFailed(outdatedSearchResult);
                    callback(result);
                }
            }
        }
    }
}

