// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "SearchQuery.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        class SearchQueryResponseReceivedMessage
        {
        private:
            const bool m_didSucceed;
            const SdkModel::SearchQuery m_query;
            const std::vector<SdkModel::SearchResultModel> m_results;

        public:
            SearchQueryResponseReceivedMessage(const bool didSucceed,
                                               const SdkModel::SearchQuery& query,
                                               const std::vector<SdkModel::SearchResultModel>& results);

            const bool DidSucceed() const;
            
            const SdkModel::SearchQuery GetQuery() const;

            const std::vector<SdkModel::SearchResultModel>& GetResults() const;
        };
    }
}
