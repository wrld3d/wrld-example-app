// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Search.h"
#include "Space.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Search
    {
        class ISearchService
        {
        public:
            virtual ~ISearchService() { }
            
            virtual void CancelInFlightQueries() = 0;
            
            virtual void PerformLocationQuerySearch(const SearchQuery& query) = 0;
            
            virtual void InsertOnPerformedQueryCallback(Eegeo::Helpers::ICallback1<const SearchQuery&>& callback) = 0;
            
            virtual void RemoveOnPerformedQueryCallback(Eegeo::Helpers::ICallback1<const SearchQuery&>& callback) = 0;
            
            virtual void InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const SearchQuery&, const std::vector<SearchResultModel>& >& callback) = 0;
            
            virtual void RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const SearchQuery&, const std::vector<SearchResultModel>& >& callback) = 0;
        };
    }
}
