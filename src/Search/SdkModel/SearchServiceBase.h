// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ISearchService.h"
#include "CallbackCollection.h"
#include "SearchTags.h"

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
                SearchServiceBase(const std::shared_ptr<Search::SdkModel::SearchTagRepository>& searchTags);

                ~SearchServiceBase();

                void ExecuteQueryPerformedCallbacks(const SearchQuery& query);

                void ExecutQueryResponseReceivedCallbacks(const SearchQuery& query, const std::vector<SearchResultModel>& results);
                
                const std::shared_ptr<const Search::SdkModel::SearchTagRepository> m_searchTags;

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

