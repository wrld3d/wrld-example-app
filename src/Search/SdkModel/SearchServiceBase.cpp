// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchServiceBase.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchServiceBase::SearchServiceBase(const std::vector<std::string>& availableCategories)
            : m_availableCategories(availableCategories)
            {

            }

            SearchServiceBase::~SearchServiceBase()
            {

            }
            
            bool SearchServiceBase::CanHandleCategory(const std::string& category) const
            {
                return(std::find(m_availableCategories.begin(), m_availableCategories.end(), category) != m_availableCategories.end());
            }

            void SearchServiceBase::ExecuteQueryPerformedCallbacks(const SearchQuery& query)
            {
                m_queryPerformedCallbacks.ExecuteCallbacks(query);
            }

            void SearchServiceBase::ExecuteQueryResponseReceivedCallbacks(const SearchQuery& query,
                    const std::vector<SearchResultModel>& results)
            {
                m_queryResponseReceivedCallbacks.ExecuteCallbacks(query, results);
            }

            void SearchServiceBase::InsertOnPerformedQueryCallback(Eegeo::Helpers::ICallback1<const SearchQuery&>& callback)
            {
                m_queryPerformedCallbacks.AddCallback(callback);
            }

            void SearchServiceBase::RemoveOnPerformedQueryCallback(Eegeo::Helpers::ICallback1<const SearchQuery&>& callback)
            {
                m_queryPerformedCallbacks.RemoveCallback(callback);
            }

            void SearchServiceBase::InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const SearchQuery&,
                    const std::vector<SearchResultModel>& >& callback)
            {
                m_queryResponseReceivedCallbacks.AddCallback(callback);
            }

            void SearchServiceBase::RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const SearchQuery&,
                    const std::vector<SearchResultModel>& >& callback)
            {
                m_queryResponseReceivedCallbacks.RemoveCallback(callback);
            }
        }
    }
}

