// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CombinedSearchService.h"
#include "SearchQuery.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            namespace SdkModel
            {
                CombinedSearchService::CombinedSearchService(const std::map<std::string,Search::SdkModel::ISearchService*>& searchServices,
                                                             Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
                : SearchServiceBase(std::vector<std::string>())
                , m_searchServices(searchServices)
                , m_searchQueryResponseCallback(this, &CombinedSearchService::OnSearchResponseRecieved)
                , m_pendingResultsLeft(0)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_currentQueryModel("", false, false, Eegeo::Space::LatLongAltitude(0, 0, 0), 0.f)
                , m_hasActiveQuery(false)
                {
                    std::map<std::string,Search::SdkModel::ISearchService*>::const_iterator iter;
                    
                    for (iter = m_searchServices.begin(); iter != m_searchServices.end(); ++iter)
                    {
                        (*iter).second->InsertOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                    }
                }
                
                CombinedSearchService::~CombinedSearchService()
                {
                    std::map<std::string,Search::SdkModel::ISearchService*>::const_iterator iter;
                    
                    for (iter = m_searchServices.begin(); iter != m_searchServices.end(); ++iter)
                    {
                        (*iter).second->RemoveOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                    }
                }
                
                bool CombinedSearchService::CanHandleCategory(const std::string& category) const
                {
                    std::map<std::string,Search::SdkModel::ISearchService*>::const_iterator iter;
                    
                    for (iter = m_searchServices.begin(); iter != m_searchServices.end(); ++iter)
                    {
                        if((*iter).second->CanHandleCategory(category))
                        {
                            return true;
                        }
                    }
                    
                    return false;
                }
                
                void CombinedSearchService::PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query)
                {
                    
                    if(m_hasActiveQuery)
                    {
                        Eegeo_TTY("Warning: Canceling Queries in Flight");
                        CancelInFlightQueries();
                    }
                    
                    std::vector<Search::SdkModel::ISearchService*> queryServices;
                    
                    for (std::map<std::string,Search::SdkModel::ISearchService*>::const_iterator iter = m_searchServices.begin(); iter != m_searchServices.end(); ++iter)
                    {
                        bool isIndoor = m_interiorInteractionModel.HasInteriorModel();
                        bool isCategory = query.IsCategory();
                        bool canPerformCategory = isCategory && (*iter).second->CanHandleCategory(query.Query());
                        bool canPerformIndoor = (*iter).second->CanHandleIndoor();
                        
                        if (isIndoor || query.ShouldTryInteriorSearch())
                        {
                            if (canPerformIndoor)
                            {
                                queryServices.push_back((*iter).second);
                            }
                        }
                        else
                        {
                            if(canPerformCategory)
                            {
                                queryServices.push_back((*iter).second);
                            }
                            else if (!isCategory)
                            {
                                queryServices.push_back((*iter).second);
                            }
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
                    
                    for (std::vector<Search::SdkModel::ISearchService*>::const_iterator iter = queryServices.begin(); iter != queryServices.end(); ++iter)
                    {
                        (*iter)->PerformLocationQuerySearch(query);
                    }
                }
                
                void CombinedSearchService::PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                     Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
                {
                    std::map<std::string,Search::SdkModel::ISearchService*>::iterator iter = m_searchServices.find(outdatedSearchResult.GetVendor());
                    if (iter != m_searchServices.end())
                    {
                        Search::SdkModel::ISearchService* pSearchService = iter->second;
                        pSearchService->PerformIdentitySearch(outdatedSearchResult,callback);
                    }
                    else
                    {
                        Eegeo_TTY("Warning: Trying to update old result not handled by this combined search service");
                        Search::SdkModel::IdentitySearchCallbackData result = Search::SdkModel::IdentitySearchCallbackData::CreateFailed(outdatedSearchResult);
                        callback(result);
                    }
                }
                
                void CombinedSearchService::CancelInFlightQueries()
                {
                    std::map<std::string,Search::SdkModel::ISearchService*>::const_iterator iter;
                    
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
                
                void CombinedSearchService::OnSearchResponseRecieved(const Search::SdkModel::SearchQuery& query,
                                                                        const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    std::vector<Search::SdkModel::SearchResultModel> filtered;
                    filtered.reserve(results.size());
                    
                    for (std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = results.begin();
                         it != results.end();
                         it++)
                    {
                        const Search::SdkModel::SearchResultModel& searchResult = *it;
                        filtered.push_back(searchResult);
                    }
                    
                    m_combinedResults.insert(m_combinedResults.end(), filtered.begin(), filtered.end());
                    
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
}