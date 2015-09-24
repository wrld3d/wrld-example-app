// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CombinedSearchService.h"
#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            CombinedSearchService::CombinedSearchService(const std::map<std::string,SdkModel::ISearchService*>& searchServices)
            : SearchServiceBase(std::vector<std::string>())
            , m_searchServices(searchServices)
            , m_searchQueryResponseCallback(this, &CombinedSearchService::OnSearchResponseRecieved)
            , m_pendingResultsLeft(0)
            , m_currentQueryModel("", false, Eegeo::Space::LatLongAltitude(0, 0, 0), 0.f)
            , m_hasActiveQuery(false)
            {
                std::map<std::string,SdkModel::ISearchService*>::const_iterator iter;
                
                for (iter = m_searchServices.begin(); iter != m_searchServices.end(); ++iter)
                {
                    (*iter).second->InsertOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                }
            }
            
            CombinedSearchService::~CombinedSearchService()
            {
                std::map<std::string,SdkModel::ISearchService*>::const_iterator iter;
                
                for (iter = m_searchServices.begin(); iter != m_searchServices.end(); ++iter)
                {
                    (*iter).second->RemoveOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                }
            }
            
            bool CombinedSearchService::CanHandleCategory(const std::string& category) const
            {
                std::map<std::string,SdkModel::ISearchService*>::const_iterator iter;
                
                for (iter = m_searchServices.begin(); iter != m_searchServices.end(); ++iter)
                {
                    if((*iter).second->CanHandleCategory(category))
                    {
                        return true;
                    }
                }
                
                return false;
            }
            
            void CombinedSearchService::PerformLocationQuerySearch(const SdkModel::SearchQuery& query)
            {
                
                if(m_hasActiveQuery)
                {
                    Eegeo_TTY("Warning: Canceling Queries in Flight");
                    CancelInFlightQueries();
                }
                
                std::vector<SdkModel::ISearchService*> queryServices;
                
                for (std::map<std::string,SdkModel::ISearchService*>::const_iterator iter = m_searchServices.begin(); iter != m_searchServices.end(); ++iter)
                {
                    bool canPerformQuery = !query.IsCategory() || (*iter).second->CanHandleCategory(query.Query());
                    
                    if(canPerformQuery)
                    {
                        queryServices.push_back((*iter).second);
                    }
                }
                
                ExecuteQueryPerformedCallbacks(query);
                
                m_pendingResultsLeft += static_cast<int>(queryServices.size());
                
                if(queryServices.empty())
                {
                    Eegeo_TTY("Warning: No valid query dispatched");
                    ExecutQueryResponseReceivedCallbacks(query, m_combinedResults);
                    return;
                }
                
                m_currentQueryModel = query;
                m_hasActiveQuery = true;
                
                for (std::vector<SdkModel::ISearchService*>::const_iterator iter = queryServices.begin(); iter != queryServices.end(); ++iter)
                {
                    (*iter)->PerformLocationQuerySearch(query);
                }
            }
            
            void CombinedSearchService::PerformIdentitySearch(const SdkModel::SearchResultModel& outdatedSearchResult,
                                                                 Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback)
            {
                if(m_searchServices.find(outdatedSearchResult.GetVendor()) != m_searchServices.end())
                {
                    m_searchServices[outdatedSearchResult.GetVendor()]->PerformIdentitySearch(outdatedSearchResult,callback);
                }
                else
                {
                    Eegeo_TTY("Warning: Trying to update old result not handled by this combined search service");
                    SdkModel::IdentitySearchCallbackData result = SdkModel::IdentitySearchCallbackData::CreateFailed(outdatedSearchResult);
                    callback(result);
                }
            }
            
            void CombinedSearchService::CancelInFlightQueries()
            {
                std::map<std::string,SdkModel::ISearchService*>::const_iterator iter;
                
                for (iter = m_searchServices.begin(); iter != m_searchServices.end(); ++iter)
                {
                    (*iter).second->CancelInFlightQueries();
                }
                
                if(m_hasActiveQuery)
                {
                    m_hasActiveQuery = false;
                    m_combinedResults.clear();
                    ExecutQueryResponseReceivedCallbacks(m_currentQueryModel, m_combinedResults);
                }
            }
            
            void CombinedSearchService::OnSearchResponseRecieved(const SdkModel::SearchQuery& query,
                                                                    const std::vector<SdkModel::SearchResultModel>& results)
            {
                m_combinedResults.insert(m_combinedResults.end(), results.begin(), results.end());
                
                if( --m_pendingResultsLeft <= 0)
                {
                    m_hasActiveQuery = false;
                    m_pendingResultsLeft = 0;
                    ExecutQueryResponseReceivedCallbacks(query, m_combinedResults);
                    m_combinedResults.clear();
                }
            }
        }
    }
}