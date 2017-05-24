// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchServiceBase.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchServiceBase::SearchServiceBase(const std::vector<std::string>& handledTags, bool canHandleCustomTags)
            : m_handledTags(handledTags)
            , m_canHandleCustomTags(canHandleCustomTags)
            {

            }

            SearchServiceBase::~SearchServiceBase()
            {

            }
            
            bool SearchServiceBase::CanHandleTag(const std::string& tag) const
            {
                return m_canHandleCustomTags || (std::find(m_handledTags.begin(), m_handledTags.end(), tag) != m_handledTags.end());
            }

            void SearchServiceBase::ExecuteQueryPerformedCallbacks(const SearchQuery& query)
            {
                m_queryPerformedCallbacks.ExecuteCallbacks(query);
            }

            void SearchServiceBase::ExecutQueryResponseReceivedCallbacks(const SearchQuery& query,
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

