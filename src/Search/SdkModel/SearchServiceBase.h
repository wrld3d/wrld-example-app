// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ISearchService.h"
#include "CallbackCollection.h"

#include <vector>

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class SearchServiceBase : public ISearchService
            {
                Eegeo::Helpers::CallbackCollection1<const SearchQuery&> m_queryPerformedCallbacks;
                Eegeo::Helpers::CallbackCollection2<const SearchQuery&, const std::vector<SearchResultModel>& > m_queryResponseReceivedCallbacks;

            protected:
                SearchServiceBase(const std::vector<std::string>& handledTags, bool canHandleCustomTags = false);

                ~SearchServiceBase();

                void ExecuteQueryPerformedCallbacks(const SearchQuery& query);

                void ExecutQueryResponseReceivedCallbacks(const SearchQuery& query, const std::vector<SearchResultModel>& results);
                
                std::vector<std::string> m_handledTags;
                bool m_canHandleCustomTags;

            public:
                
                virtual bool CanHandleTag(const std::string& tag) const;
                
                virtual bool CanHandleIndoor() const { return false; }
                
                void InsertOnPerformedQueryCallback(Eegeo::Helpers::ICallback1<const SearchQuery&>& callback);

                void RemoveOnPerformedQueryCallback(Eegeo::Helpers::ICallback1<const SearchQuery&>& callback);

                void InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const SearchQuery&, const std::vector<SearchResultModel>& >& callback);

                void RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const SearchQuery&, const std::vector<SearchResultModel>& >& callback);
            };
        }
    }
}

